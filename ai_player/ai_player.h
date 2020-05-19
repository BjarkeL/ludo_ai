#ifndef AI_PLAYER_H
#define AI_PLAYER_H

#include "iplayer.h"
#include <iostream>
#include <vector>
#include "positions_and_dice.h"
#include <random>
#include <algorithm>
#include <functional>
#include <map>
#include <fstream>
#include <array>
#include <math.h>


#define INPUTS 9
#define OUTPUTS 1
#define HIDDEN 4
#define PIECES 4
#define WEIGHTS1 INPUTS*HIDDEN
#define WEIGHTS2 HIDDEN*OUTPUTS
#define C_SIZE WEIGHTS1+WEIGHTS2 // Size of a chromosome.


struct BinaryVal {
    int size;
    char* bin_val = new char[size];
    BinaryVal() : size(6) {};
    void change_size(int s) { size = s; };
    void set_val(int value) {
        int val = value;
        for (int i = 0; i < size; i++) {
            bin_val[i] = val%2;
            val /= 2;
        }
    }
    bool operator [] (int i) { return bin_val[size-1-i]; };
    void print() {
        for (int i = size-1; i >= 0; i--) { std::cout << (bool)bin_val[i]; }
        std::cout << std::endl;
    }
    void destroy() { delete [] bin_val; };
};

class AiPlayer : public iplayer {
public:
    AiPlayer();

    void init_chromosomes(int x);

    /**
     * Adds a point to the current chromosome.
     * */
    void add_point();

    /**
     * Increments the current chromosome.
     * */
    void inc_current_chromosome();

    /**
     * Evolves a new half from the highest scoring half of the current generation.
     * Also resets to run again for the next generation.
     * */
    void evolve_generation();

    /**
     * Setting learning to false uses the best chromosome found so far.
     * */
    void set_learning(bool learn);

private:
    int make_decision();

    /**
     * Chooses a move based on the order specified in the chromosome.
     * Returns the piece to move.
     * */
    int process_chromosome(std::vector<int> c);

    /**
     * Takes two chromosomes and mixes them into two new offspring.
     * Adds the two new chromosomes to the list of children.
     * */
    void crossover(std::array<float,C_SIZE> c1, std::array<float,C_SIZE> c2);

    /**
     * Swap two random genes in a chromosome.
     * */
    //void swap_genes(std::vector<int>* c);

    /**
     * Mutate a chromosome'
     * */
    void mutate(std::array<float,C_SIZE>& c);

    /**
     * Returns the piece to move if it's possible to move out of home.
     * Returns -1 otherwise.
     * */
    float move_out();

    /**
     * Returns the piece to move if it's possible to move into base.
     * Returns -1 otherwise.
     * */
    float move_in();

    /**
     * Returns the piece to move if it's possible to move into goal.
     * Returns -1 otherwise.
     * */
    float move_to_goal();

    /**
     * Returns the first piece that can move to a globe.
     * Returns -1 otherwise.
     * */
    float move_to_globe();

    /**
     * Returns the first piece that can move to a star.
     * Returns -1 otherwise.
     * */
    float move_to_star();

    /**
     * Returns the first piece that can move onto another of it's own.
     * Returns -1 otherwise.
     * */
    float stack_piece();

    /**
     * Returns the first piece to move that can beat an opponent piece.
     * Returns -1 otherwise.
     * */
    float beat_opponent_piece();

    /**
     * Return the distance to the goal as value between 0 and 1.
     * */
    float dist_to_goal();

    /**
     * Return the number of opponents on a given square.
     * */
    int count_opponents(int square);

    /**
     * Return true if the square is a globus.
     * */
    bool on_globus(int square);

    /**
     * Returns true if there is an enemy within 6 behind you.
     * */
    float threat_behind();

    /**
     * The logistic transfer function.
     * */
    float sigmoid(float x);

    int current_square = 0;
    int current_chromosome = 0;

    std::vector<int> options;

    std::random_device rd;
    std::vector<std::array<float,C_SIZE>> chromosomes;
    std::vector<std::array<float,C_SIZE>> new_generation;
    std::multimap<int, std::array<float,C_SIZE>, std::greater<int>> sorted_chromosomes;
    std::vector<int> scores;

    std::vector<std::function<float(void)>> moves;
    
    // Network:
    std::array<float, PIECES> output_values;
    std::array<float, HIDDEN> hidden_values;


    std::ofstream data_out;


    bool learning = true;
    std::pair<int, std::array<float,C_SIZE>> best_chromosome;
};

#endif // AI_PLAYER_H