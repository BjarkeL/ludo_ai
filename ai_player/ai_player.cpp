#include "ai_player.h"

AiPlayer::AiPlayer() {

}

/******************** GA External ********************/

void AiPlayer::init_chromosomes(int x) {

    moves.push_back([this](void){return this->move_out();});
    moves.push_back([this](void){return this->move_in();});
    moves.push_back([this](void){return this->move_to_goal();});
    moves.push_back([this](void){return this->move_to_globe();});
    moves.push_back([this](void){return this->move_to_star();});
    moves.push_back([this](void){return this->stack_piece();});
    moves.push_back([this](void){return this->beat_opponent_piece();});
    moves.push_back([this](void){return this->threat_behind();});
    moves.push_back([this](void){return this->dist_to_goal();});

    std::mt19937 generator(rd());
    std::uniform_real_distribution<> dist(0.0,1.0);

    // x different chromosomes.
    while (chromosomes.size() < x) {
        std::array<float,C_SIZE> tmp_chromosome;
        for (int i = 0; i < C_SIZE; i++) {
            tmp_chromosome[i] = dist(generator);
            // std::cout << tmp_chromosome[i] << std::endl;
        }
        // Very unlikely 52*4 values are the same when random between 0 and 1.
        // if (std::find(chromosomes.begin(), chromosomes.end(), tmp_chromosome) == chromosomes.end()) {
        //     chromosomes.push_back(tmp_chromosome);
        //     scores.push_back(0);
        // }
        chromosomes.push_back(tmp_chromosome);
        scores.push_back(0);
    }

    std::fill(hidden_values.begin(), hidden_values.end(), 0);

    best_chromosome = std::pair<int, std::array<float,C_SIZE>>(0, chromosomes[0]);

    // Open filestream
    // data_out.open("chromosome.txt");
    
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
    sorted_chromosomes.clear();
    for (int i = 0; i < chromosomes.size(); i++) {
        sorted_chromosomes.insert(std::pair<int, std::array<float,C_SIZE>>(scores[i], chromosomes[i]));
    }

    std::cout << std::string(15,'*') << std::endl;
    if ((*sorted_chromosomes.begin()).first >= best_chromosome.first) {
        best_chromosome = *sorted_chromosomes.begin();
        std::cout << "Best so far! " << best_chromosome.first << " wins." << std::endl;
    } else {
        std::cout << "Not best but " << (*sorted_chromosomes.begin()).first << " wins!" << std::endl;
    }

    // data_out << (*sorted_chromosomes.begin()).first << std::endl; // Prints the amount of wins.

    std::multimap<int, std::array<float,C_SIZE>>::iterator sorted_iter1 = sorted_chromosomes.begin();
    std::multimap<int, std::array<float,C_SIZE>>::iterator sorted_iter2 = sorted_chromosomes.begin();
    // while (new_generation.size() < chromosomes.size()) {
    //     // std::cout << "New gen size: " << new_generation.size() << std::endl;
    //     ++sorted_iter2;
    //     crossover((*sorted_iter1).second, (*sorted_iter2).second);
    //     ++sorted_iter1;
    // }

    new_generation.push_back((*sorted_iter1).second); // Add the best parent first to avoid adding it multiple times.
    int tmp1 = 1;
    for (int i = 1; i < 10; i++) {
        int tmp2 = 0;
        ++sorted_iter2;
        while (tmp2++ < tmp1) {
            // std::cout << tmp2 << ", ";
            crossover((*sorted_iter1).second, (*sorted_iter2).second);
            ++sorted_iter1;
            if (new_generation.size() >= chromosomes.size()) {
                break;
            }
        }
        if (new_generation.size() >= chromosomes.size()) {
            break;
        }
        // std::cout << std::endl;
        tmp1++;
    }

    // Pick a random one to mutate
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> dist(0,chromosomes.size()-1);
    int m = dist(generator);
    while (m%3 == 0) {
        m = dist(generator);
    }
    // Replace chromosomes with the new generation.
    for (int i = 0; i < chromosomes.size(); i++) {
        if (i == m) {
            mutate(new_generation[i]);
        }
        chromosomes[i] = new_generation[i];
    }

    // std::uniform_real_distribution<> bias_dist(-0.05, 0.05);
    // bias += bias_dist(generator);
    // std::cout << bias << std::endl;

    // Reset for new generation.
    current_chromosome = 0;
    std::fill(scores.begin(), scores.end(), 0);
    new_generation.clear();
}

void AiPlayer::set_learning(bool learn) {
    learning = learn;
}

/******************** Automatic action for each turn ********************/

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

    // If there are more than one valid move use the network to determine next move.
    // std::cout << "Dice: " << dice << std::endl;
    for (auto op : options) {
        current_square = position[op];
        // std::cout << "Option: " << op << ", pos: " << current_square << ", func val: ";

        int chromosome_index = 0;
        for (auto func : moves) {
            for (int i = 0; i < HIDDEN; i++) {
                hidden_values[i] += chromosomes[current_chromosome][chromosome_index++]*func();
            }
        }
        // Adds the hidden bias.
        for (int i = 0; i < HIDDEN; i++) {
            hidden_values[i] += chromosomes[current_chromosome][chromosome_index++]*bias;
        }
        for (int i = 0; i < HIDDEN; i++) {
            output_values[op] += chromosomes[current_chromosome][chromosome_index++]*sigmoid(hidden_values[i]);
        }
        // float avg_hidden = 0;
        // for (auto h : hidden_values) {
        //     avg_hidden += sigmoid(h)/hidden_values.size();
        // }
        // std::cout << "Average hidden: " << avg_hidden << std::endl;
        // std::cout << "Hidden:" << std::endl;
        // for (auto x : hidden_values) {
        //     std::cout << sigmoid(x) << ", " << x << ", ";
        // }
        // std::cout << std::endl;
        std::fill(hidden_values.begin(), hidden_values.end(), 0);
    }
    
    // std::cout << "Output." << std::endl;
    // for (auto out : output_values) {
    //     std::cout << out << ", ";
    // }
    // std::cout << std::endl << std::endl;


    int move = options[0];
    float val = output_values[move];
    for (int i : options) {
        if (output_values[i] > val) {
            val = output_values[i];
            move = i;
        }
    }
    
    // threat_behind();
    // dist_to_goal2(0);

    std::fill(output_values.begin(), output_values.end(), 0);
    
    return move;
}

/******************** GA Internal ********************/

void AiPlayer::crossover(std::array<float,C_SIZE> c1, std::array<float, C_SIZE> c2) {
    
    // Merge together every n bits.
    std::array<float,C_SIZE> tmp_c1;
    std::array<float,C_SIZE> tmp_c2;
    bool flip = false;
    for (int i = 0; i < c1.size(); i++) {
        if (i%3 == 0) {
            flip = !flip;
        }
        if (flip) {
            // std::cout << "Hej " << i << std::endl;
            tmp_c1[i] = c1[i];
            tmp_c2[i] = c2[i];
        } else {
            // std::cout << "Hello " << i << std::endl;
            tmp_c1[i] = c2[i];
            tmp_c2[i] = c1[i];
        }
    }
    
    
    // std::mt19937 generator(rd());
    // std::uniform_int_distribution<int> dist(1,c1.size()-1);

    // int crossover_point = dist(generator);

    // for (int i = 0; i < c1.size(); i++) {
    //     if (i < crossover_point) {
    //         tmp_c1[i] = c1[i];
    //         tmp_c2[i] = c2[i];
    //     } else {
    //         tmp_c1[i] = c2[i];
    //         tmp_c2[i] = c1[i];
    //     }
    // }

    new_generation.push_back(c2); // Adds the second parent since the first repeats multiple times.
    new_generation.push_back(tmp_c1);
    new_generation.push_back(tmp_c2);
    
}

void AiPlayer::mutate(std::array<float,C_SIZE>& c) {


    // Replace every n genes with newly generated ones.
    std::mt19937 generator(rd());
    std::uniform_real_distribution<> dist(0.0,1.0);
    for (int i = 0; i < c.size(); i+=2) { // Replace every other.
        c[i] = dist(generator);
    }


    // // Alter 10% of the genes randomly.
    // int n_mutations = std::ceil(c.size()*0.3); // 0.1
    // std::mt19937 generator(rd());
    // std::uniform_int_distribution<int> dist1(0,C_SIZE-1);
    // std::uniform_real_distribution<> dist2(0.05,0.5); // 0.1 - 0.5
    // // Generate n indices
    // std::vector<int> indices(n_mutations);
    // std::generate(indices.begin(),indices.end(),[dist1, generator] () mutable { return dist1(generator); });

    // for (auto i : indices) {
    //     float random_val = dist2(generator);
    //     c[i] = c[i]+random_val < 1.0 ? c[i]+random_val : c[i]-random_val;
    // }
}

/******************** Information Collection ********************/

float AiPlayer::move_out() {
    // std::cout << "out" << dice << std::endl;
    if (current_square == -1) {
        return true;
    }
    return false;
}

float AiPlayer::move_in() {
    // std::cout << "in" << std::endl;
    if (current_square <= 50 && current_square + dice > 50) {
        return true;
    }
    return false;
}

float AiPlayer::move_to_goal() {
    // std::cout << "goal" << std::endl;
    if (current_square + dice == 56) {
        return true;
    }
    return false;
}

float AiPlayer::move_to_globe() {
    // std::cout << "globe" << std::endl;
    if (current_square != -1) {
        return on_globus(current_square+dice);
    }
    return true; // Assuming that if possible to move and in home moving out is a globus.
}

float AiPlayer::move_to_star() {
    // std::cout << "star" << std::endl;
    if (current_square != -1) {
        switch (current_square+dice) {
            case 5: return true;
            case 11: return true;
            case 18: return true;
            case 24: return true;
            case 31: return true;
            case 37: return true;
            case 44: return true;
            default: return false;
        }
    }
    return false;
}

float AiPlayer::stack_piece() {
    // std::cout << "stack" << std::endl;

    if (current_square+dice < 51) {
        for (int i = 0; i < 4; i++) {
            if (current_square + dice == position[i]) {
                return true;
            }
        }
    }
    return false;
}

float AiPlayer::beat_opponent_piece() {
    // std::cout << "beat opponent" << std::endl;

    if (current_square != -1) {
        for (int i = 4; i < 16; i++) {
            if (position[i] < 51 && current_square+dice == position[i]) {
                if (count_opponents(current_square+dice) < 2 && !on_globus(current_square+dice)) {
                    return true;
                }
            }
        }
    }
    return false;
}

float AiPlayer::dist_to_goal() {
    if (56-current_square < 0) {
        return 0;
    } else {
        return 1-(56-current_square)/57.;
    }
}

int AiPlayer::count_opponents(int square) {
    int n = 0;
    for (int i = 4; i < 16; i++) {
        if (position[i] == square) {
            n++;
        }
    }
    return n;
}

bool AiPlayer::on_globus(int square) {
    if (square % 13 == 8 || square % 13 == 0) {
        return true;
    } else {
        return false;
    }
}

float AiPlayer::threat_behind() {

    if (current_square != -1) {
        int trail = current_square-6 < 0 ? 51-6+current_square+1 : current_square-6;
        for (int i = 0; i < 16; i++) {
            if (trail < position[i] && position[i] < current_square) {
                return true;
            }
            if (trail < position[i] && position[i] <= 51) {
                return true;
            }
            if (position[i] >= 0 && position[i] < current_square) {
                return true;
            }
        }
    }
    
    return false;
}

float AiPlayer::sigmoid(float x) {
    return 1 / (1 + std::exp(-x));
}