#include "ai_player.h"

AiPlayer::AiPlayer() {

}

void AiPlayer::init_chromosomes(int x) {

    moves.push_back([this](void){return this->move_out();});
    moves.push_back([this](void){return this->move_in();});
    moves.push_back([this](void){return this->move_to_goal();});
    moves.push_back([this](void){return this->move_to_globe();});
    moves.push_back([this](void){return this->move_to_star();});
    moves.push_back([this](void){return this->stack_piece();});
    moves.push_back([this](void){return this->beat_opponent_piece();});

    std::mt19937 generator(rd());

    // x different chromosomes.
    std::vector<int> tmp_chromosome;
    while (chromosomes.size() < x) {
        tmp_chromosome.clear();
        for (int j = 0; j < 7; j++) {
            tmp_chromosome.push_back(j);
        }
        std::shuffle(tmp_chromosome.begin(), tmp_chromosome.end(), generator);
        if (std::find(chromosomes.begin(), chromosomes.end(), tmp_chromosome) == chromosomes.end()) {
            chromosomes.push_back(tmp_chromosome);
            scores.push_back(0);
        }
    }

    // Open filestream
    data_out.open("chromosome2.txt");
    
}

void AiPlayer::add_point() {
    scores[current_chromosome]++;
}

void AiPlayer::inc_current_chromosome() {
    current_chromosome++;
}

void AiPlayer::evolve_generation() {
    // Evolve by pairing chromosomes.

    // Sort the chromosomes based on score:
    std::multimap<int, std::vector<int>, std::greater<int>> sorted_chromosomes;
    for (int i = 0; i < chromosomes.size(); i++) {
        sorted_chromosomes.insert(std::pair<int, std::vector<int>>(scores[i], chromosomes[i]));
    }

    data_out << (*sorted_chromosomes.begin()).first << ",";
    for (auto i : (*sorted_chromosomes.begin()).second) {
        data_out << i << ",";
    }
    data_out << std::endl;

    // std::cout << "Sorted chromosomes..." << std::endl;
    int show_n = 10;
    int x = 1;
    for (auto c : sorted_chromosomes) {
        // std::cout << c.first << ", ";
        // for (auto i : c.second) {
        //     std::cout << i;
        // }
        // std::cout << std::endl;
        
        if (x++ == show_n)
            break;
    }

    std::multimap<int, std::vector<int>>::iterator sorted_iter1 = sorted_chromosomes.begin();
    std::multimap<int, std::vector<int>>::iterator sorted_iter2 = sorted_chromosomes.begin();
    while (new_generation.size() < chromosomes.size()) {
        // std::cout << "New gen size: " << new_generation.size() << std::endl;
        ++sorted_iter2;
        crossover((*sorted_iter1).second, (*sorted_iter2).second);
        ++sorted_iter1;
    }
    // std::cout << "Size of new generation: " << new_generation.size() << std::endl;

    // Pick a random one to mutate
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> dist(0,chromosomes.size()-1);
    int mutate = dist(generator);
    // Replace chromosomes with the new generation.
    for (int i = 0; i < chromosomes.size(); i++) {
        if (i == mutate) {
            // std::cout << "Mutating" << std::endl;
            swap_genes(&new_generation[i]);
        }
        chromosomes[i] = new_generation[i];
    }

    // Reset for new generation.
    current_chromosome = 0;
    std::fill(scores.begin(), scores.end(), 0);
    new_generation.clear();
}

int AiPlayer::make_decision() {

    options.clear();

    for (int i = 0; i < 4; i++) {
        if (is_valid_move(i)) {
            options.push_back(i);
        }
    }
    if (options.size() == 0) {
        return -1;
    }
    if (options.size() == 1) {
        return options[0];
    }

    position_vector.clear(); // Makes it possible to make range base for loops.
    for (int i = 0; i < 16; i++) {
        position_vector.push_back(position[i]);
    }

    // If there are more than one valid move perform the strategy dictated by the chromosome.
    // The chromosome shall either dictate whether to perform a move or what order to perform the moves.

    int piece_to_move = process_chromosome(chromosomes[current_chromosome]);

    if (piece_to_move == -1) {
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> dist(0,options.size()-1);
        piece_to_move = options[dist(generator)];
    }
    
    return piece_to_move;
}

int AiPlayer::process_chromosome(std::vector<int> c) {
    
    // std::cout << "Running the functions in the order: " << std::endl;
    // for (int i = 0; i < 7; i++) {
    //     std::cout << c[i];
    // }
    // std::cout << std::endl;
    int move;
    for (auto i : c) {
        move = moves[i]();
        // std::cout << move << std::endl;
        if (move != -1) {
            break;
        }
    }

    return move;
}

void AiPlayer::crossover(std::vector<int> c1, std::vector<int> c2) {
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> dist(1,c1.size()-2);

    int crossover_point = dist(generator);

    std::vector<int> tmp_c1;
    std::vector<int> tmp_c2;
    for (int i = 0; i < crossover_point; i++) {
        tmp_c1.push_back(c1[i]);
        tmp_c2.push_back(c2[i]);
    }

    for (auto c : c1) {
        if (std::find(tmp_c2.begin(), tmp_c2.end(), c) == tmp_c2.end())
            tmp_c2.push_back(c);
    }
    for (auto c : c2) {
        if (std::find(tmp_c1.begin(), tmp_c1.end(), c) == tmp_c1.end())
            tmp_c1.push_back(c);
    }

    new_generation.push_back(c1);
    // new_generation.push_back(c2);
    new_generation.push_back(tmp_c1);
    new_generation.push_back(tmp_c2);

    // std::cout << "Crossover point: " << crossover_point << std::endl;
    // std::cout << "c1 -> tmp_c1:" << std::endl << "c1: ";
    // for (auto i : c1)
    //     std::cout << i;
    // std::cout << std::endl << "tmp_c1: ";
    // for (auto i : tmp_c1)
    //     std::cout << i;
    // std::cout << std::endl;

    // std::cout << "c2 -> tmp_c2:" << std::endl << "c2: ";
    // for (auto i : c2)
    //     std::cout << i;
    // std::cout << std::endl << "tmp_c2: ";
    // for (auto i : tmp_c2)
    //     std::cout << i;
    // std::cout << std::endl;
    
}

void AiPlayer::swap_genes(std::vector<int>* c) {
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> dist(0,c->size()-1);

    int gene1 = dist(generator);
    int gene2 = dist(generator);
    while (gene2 == gene1) {
        gene2 = dist(generator);
    }
    // std::cout << "Swaps:" << std::endl << "G1: " << gene1 << ", G2: " << gene2 << std::endl;
    std::iter_swap(c->begin()+gene1, c->begin()+gene2);
}

int AiPlayer::move_out() {
    // std::cout << "out" << dice << std::endl;
    for (int i = 0; i < options.size(); i++) {
        int piece_pos = position[options[i]];
        if (piece_pos == -1) {
            return options[i];
        }
    }
    return -1;
}

int AiPlayer::move_in() {
    // std::cout << "in" << std::endl;
    for (int i = 0; i < options.size(); i++) {
        int piece_pos = position[options[i]];
        if (piece_pos <= 50 && piece_pos + dice > 50) {
            return options[i];
        } 
    }
    return -1;
}

int AiPlayer::move_to_goal() {
    // std::cout << "goal" << std::endl;
    for (int i = 0; i < options.size(); i++) {
        int piece_pos = position[options[i]];
        if (piece_pos + dice == 56) {
            return options[i];
        }
    }
    return -1;
}

int AiPlayer::move_to_globe() {
    // std::cout << "globe" << std::endl;
    for (int i = 0; i < options.size(); i++) {
        int piece_pos = position[options[i]];
        if (std::find(globe_positions.begin(), globe_positions.end(), piece_pos + dice) != globe_positions.end()) {
            return options[i];
        }
    }
    return -1;
}

int AiPlayer::move_to_star() {
    // std::cout << "star" << std::endl;
    for (int i = 0; i < options.size(); i++) {
        int piece_pos = position[options[i]];
        if (std::find(star_positions.begin(), star_positions.end(), piece_pos + dice) != star_positions.end()) {
            return options[i];
        }
    }
    return -1;
}

int AiPlayer::stack_piece() {
    // std::cout << "stack" << std::endl;
    for (int i = 0; i < options.size(); i++) {
        int piece_pos = position[options[i]];
        for (int j = 0; j < options.size(); j++) {
            int other_piece = position[options[j]];
            if (i != j && piece_pos + dice == other_piece) {
                return options[i];
            }
        }
    }
    return -1;
}

int AiPlayer::beat_opponent_piece() {
    // std::cout << "beat opponent" << std::endl;
    for (int i = 0; i < options.size(); i++) {
        int piece_pos = position[options[i]];
        for (auto it = position_vector.begin()+4; it != position_vector.end(); ++it) {
            if (*it < 51 && piece_pos + dice == *it) {
                return options[i];
            }
        }
    }
    return -1;
}