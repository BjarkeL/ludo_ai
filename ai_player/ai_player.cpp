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

    if ((*sorted_chromosomes.begin()).first >= best_chromosome.first) {
        best_chromosome = *sorted_chromosomes.begin();
        std::cout << "Best so far! " << best_chromosome.first << " wins." << std::endl;
    }

    data_out << (*sorted_chromosomes.begin()).first << ","; // Prints the amount of wins.
    // for (auto i : (*sorted_chromosomes.begin()).second) {
    //     data_out << i << ",";
    // }
    data_out << std::endl;

    std::multimap<int, std::array<float,C_SIZE>>::iterator sorted_iter1 = sorted_chromosomes.begin();
    std::multimap<int, std::array<float,C_SIZE>>::iterator sorted_iter2 = sorted_chromosomes.begin();
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

    // First get the input vector.
    int input_index = 0;
    for (int i = 0; i < 8; i++) {
        std::array<bool, 4> tmp_status = moves[i]();
        for (int j = 0; j < 4; j++) {
            input_values[input_index++] = tmp_status[j];
        }
    }

    // Temporary inputs splitting the input to individual pieces.
    std::array<float, INPUTS> tmp_input1;
    std::array<float, INPUTS> tmp_input2;
    std::array<float, INPUTS> tmp_input3;
    std::array<float, INPUTS> tmp_input4;
    int index = 0;
    for (int j = 0; j < INPUTS-1; j++) {
        tmp_input1[j] = input_values[index];
        tmp_input2[j] = input_values[index+1];
        tmp_input3[j] = input_values[index+2];
        tmp_input4[j] = input_values[index+3];
    }
    tmp_input1[8] = dist_to_goal2(0);
    tmp_input2[8] = dist_to_goal2(1);
    tmp_input3[8] = dist_to_goal2(2);
    tmp_input4[8] = dist_to_goal2(3);
    
    std::array<float, INPUTS*4> ordered_input;
    index = 0;
    for (int i = 0; i < INPUTS; i++) {
        ordered_input[index++] = tmp_input1[i];
    }
    for (int i = 0; i < INPUTS; i++) {
        ordered_input[index++] = tmp_input2[i];
    }
    for (int i = 0; i < INPUTS; i++) {
        ordered_input[index++] = tmp_input3[i];
    }
    for (int i = 0; i < INPUTS; i++) {
        ordered_input[index++] = tmp_input4[i];
    }

    // for (int i = 0; i < 4; i++) {
    //     input_values[input_index++] = dist_to_goal2(i);
    // }
    // for (int i = 0; i < 4; i++) {
    //     std::array<bool, 6> tmp_status = dist_to_goal(i);
    //     for (int j = 0; j < 6; j++) {
    //         input_values[input_index++] = tmp_status[j];
    //     }
    // }

    // Then calculate the output

    int chromosome_index = 0;
    input_index = 0;
    if (learning) {

        // Go through the options to index on output values.
        for (auto op : options) {
            for (int j = 0; j < C_SIZE; j++) {
                output_values[op] += chromosomes[current_chromosome][j]*ordered_input[input_index++];
            }
        }

        // Input to hidden layer.
        // for (int i = 0; i < OUTPUTS; i++) {
        //     for (int j = 0; j < INPUTS; j++) {
        //         output_values[i] += chromosomes[current_chromosome][chromosome_index++]*input_values[j];
        //     }
        // }
    } else {

        for (auto op : options) {
            for (int j = 0; j < C_SIZE; j++) {
                output_values[op] += best_chromosome.second[j]*ordered_input[input_index++];
            }
        }

        // Input to output.
        // for (int i = 0; i < OUTPUTS; i++) {
        //     for (int j = 0; j < INPUTS; j++) {
        //         output_values[i] += best_chromosome.second[chromosome_index++]*input_values[j];
        //     }
        // }
    }
    // for (auto i : output_values)
    //     std::cout << i << ", ";
    // std::cout << std::endl;

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
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> dist(1,c1.size()-1);

    int crossover_point = dist(generator);

    std::array<float,C_SIZE> tmp_c1;
    std::array<float,C_SIZE> tmp_c2;
    for (int i = 0; i < c1.size(); i++) {
        if (i < crossover_point) {
            tmp_c1[i] = c1[i];
            tmp_c2[i] = c2[i];
        } else {
            tmp_c1[i] = c2[i];
            tmp_c2[i] = c1[i];
        }
    }

    new_generation.push_back(c1);
    // new_generation.push_back(c2);
    new_generation.push_back(tmp_c1);
    new_generation.push_back(tmp_c2);
    
}

void AiPlayer::mutate(std::array<float,C_SIZE>& c) {
    // Alter 10% of the genes randomly.
    int n_mutations = std::ceil(c.size()*0.2); // 0.1
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> dist1(0,C_SIZE-1);
    std::uniform_real_distribution<> dist2(0.05,0.5); // 0.1 - 0.5
    // Generate n indices
    std::vector<int> indices(n_mutations);
    std::generate(indices.begin(),indices.end(),[dist1, generator] () mutable { return dist1(generator); });

    for (auto i : indices) {
        // std::cout << i << ", " << (*c)[i] << ", " << (*c)[i]*dist2(generator) << std::endl;
        // (*c)[i] *= dist2(generator);
        float random_val = dist2(generator);
        c[i] = c[i]+random_val < 1.0 ? c[i]+random_val : c[i]-random_val;
    }
}

/******************** Information Collection ********************/

std::array<bool,4> AiPlayer::move_out() {
    // std::cout << "out" << dice << std::endl;
    std::array<bool,4> status;
    for (int i = 0; i < 4; i++) {
        if (position[i] == -1) {
            status[i] = true;
        } else {
            status[i] = false;
        }
    }
    return status;
}

std::array<bool,4> AiPlayer::move_in() {
    // std::cout << "in" << std::endl;
    std::array<bool,4> status;
    for (int i = 0; i < 4; i++) {
        if (position[i] <= 50 && position[i] + dice > 50) {
            status[i] = true;
        } else {
            status[i] = false;
        }
    }
    return status;
}

std::array<bool,4> AiPlayer::move_to_goal() {
    // std::cout << "goal" << std::endl;
    std::array<bool,4> status;
    for (int i = 0; i < 4; i++) {
        if (position[i] + dice == 56) {
            status[i] = true;
        } else {
            status[i] = false;
        }
    }
    return status;
}

std::array<bool,4> AiPlayer::move_to_globe() {
    // std::cout << "globe" << std::endl;
    std::array<bool,4> status;
    for (int i = 0; i < 4; i++) {
        if (std::find(globe_positions.begin(), globe_positions.end(), position[i] + dice) != globe_positions.end()) {
            status[i] = true;
        } else {
            status[i] = false;
        }
    }
    return status;
}

std::array<bool,4> AiPlayer::move_to_star() {
    // std::cout << "star" << std::endl;
    std::array<bool,4> status;
    for (int i = 0; i < 4; i++) {
        if (position[i] != -1) {
            if (std::find(star_positions.begin(), star_positions.end(), position[i] + dice) != star_positions.end()) {
                status[i] = true;
            } else {
                status[i] = false;
            }
        } else {
            status[i] = false;
        }
    }
    return status;
}

std::array<bool,4> AiPlayer::stack_piece() {
    // std::cout << "stack" << std::endl;
    std::array<bool,4> status;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i != j && position[i] != -1 && position[i] + dice == position[j] && position[i] + dice < 51) {
                status[i] = true;
                break;
            } else {
                status[i] = false;
            }
        }
    }
    return status;
}

std::array<bool,4> AiPlayer::beat_opponent_piece() {
    // std::cout << "beat opponent" << std::endl;

    // Find pieces that can beat an opponent:
    std::array<bool,4> status;
    for (int i = 0; i < 4; i++) {
        for (int j = 4; j < 16; j++) {
            if (position[j] < 51 && position[i] + dice == position[j]) {
                if (count_opponents(position[i]+dice) < 2 && on_globus(position[i]+dice) == false) {
                    status[i] = true;
                } else {
                    status[i] = false;
                }
                break;
            } else {
                status[i] = false;
            }
        }
    }
    // std::cout << "Dice: " << dice << ", Status:" << std::endl;
    // for (int i = 0; i < 4; i++) {
    //     std::cout << status[i];
    // }
    // std::cout << std::endl;
    return status;
}

std::array<bool,6> AiPlayer::dist_to_goal(int piece) {

    BinaryVal distance;

    if (56-position[piece] < 0) {
        distance.set_val(0);
    } else {
        distance.set_val(56-position[piece]);
    }
    
    std::array<bool,6> dist;
    for (int i = 0; i < 6; i++) {
        dist[i] = distance[i];
    }

    distance.destroy();

    return dist;
}

float AiPlayer::dist_to_goal2(int piece) {

    float dist;

    if (56-position[piece] < 0) {
        dist = 0;
    } else {
        dist = (56-position[piece])/57.;
    }
    
    // std::cout << dist << std::endl;

    return dist;
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
    if (std::find(globe_positions.begin(), globe_positions.end(), square) != globe_positions.end()) {
        return true;
    } else {
        return false;
    }
}

std::array<bool,4> AiPlayer::threat_behind() {
    std::array<bool,4> status;

    for (int i = 0; i < 4; i++) {
        if (position[i] != -1) {

            // std::cout << "Piece " << i << ", position: " << position[i];
            int trail = position[i]-6 < 0 ? 51-6+position[i]+1: position[i]-6;
            // std::cout << ", trail: " << trail << std::endl;
            for (int j = 4; j < 16; j++) {
                if (trail < position[i]) {
                    status[i] = position[j] > trail && position[j] < position[i] ? true : false;
                } else {
                    if (position[j] > trail && position[j] <= 51) {
                        status[i] = true;
                        break;
                    } else if (position[j] < position[i] && position[j] >= 0) {
                        status[i] = true;
                        break;
                    } else {
                        status[i] = false;
                    }
                }
            }

        } else {
            status[i] = false;
        }
    }
    // for (auto i : status)
    //     std::cout << i;
    // std::cout << std::endl;

    return status;
}