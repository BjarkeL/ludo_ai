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
    void crossover(std::vector<int> c1, std::vector<int> c2);

    /**
     * Swap two random genes in a chromosome.
     * */
    void swap_genes(std::vector<int>* c);

    /**
     * Returns the piece to move if it's possible to move out of home.
     * Returns -1 otherwise.
     * */
    int move_out();

    /**
     * Returns the piece to move if it's possible to move into base.
     * Returns -1 otherwise.
     * */
    int move_in();

    /**
     * Returns the piece to move if it's possible to move into goal.
     * Returns -1 otherwise.
     * */
    int move_to_goal();

    /**
     * Returns the first piece that can move to a globe.
     * Returns -1 otherwise.
     * */
    int move_to_globe();

    /**
     * Returns the first piece that can move to a star.
     * Returns -1 otherwise.
     * */
    int move_to_star();

    /**
     * Returns the first piece that can move onto another of it's own.
     * Returns -1 otherwise.
     * */
    int stack_piece();

    /**
     * Returns the first piece to move that can beat an opponent piece.
     * Returns -1 otherwise.
     * */
    int beat_opponent_piece();


    std::vector<int> options;
    std::vector<int> position_vector;

    std::vector<int> globe_positions = {8, 21, 34, 47};
    std::vector<int> star_positions = {5, 11, 18, 24, 31, 37, 44, 50};

    std::random_device rd;
    std::vector<std::vector<int>> chromosomes;
    std::vector<std::vector<int>> new_generation;
    std::vector<std::vector<int>> parents;
    std::vector<std::vector<int>> children;
    std::vector<int> scores;

    std::vector<std::function<int(void)>> moves;

    int current_chromosome = 0;

    std::ofstream data_out;
};

#endif // AI_PLAYER_H