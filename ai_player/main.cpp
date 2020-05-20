#include <iostream>
#include "game.h"
#include "test_game.h"
#include "iplayer.h"
#include "player_random.h"
#include "ai_player.h"
#include <chrono>

// using namespace std;

void thread_player(AiPlayer &agent, int population, int games_per_gen) {
    player_random player_1;
    player_random player_2;
    player_random player_3;

    game g(&agent, &player_1, &player_2, &player_3);

    for (int i = 0; i < population*games_per_gen; i++)
    {
        g.reset();
        g.set_first(i%4); //alternate who starts the game
        g.play_game();

        // Add one to the score for the chromosome if it wins.
        if (g.get_winner() == 0)
            agent.add_point();
        // Increment the current chromosome being tested every n games.
        if (i != 0 && i%games_per_gen == 0) {
            agent.inc_current_chromosome();
        }
    }
    // Update the generation based on the points.
    agent.evolve_generation();
}

int main()
{
    //Run the unit tests
    // test_game tester;
    // tester.run_all_tests();

    //Create players
    AiPlayer player_0;
    AiPlayer helper_0;
    AiPlayer helper_1;
    // player_random player_0;
    // AiPlayer player_1;
    player_random player_1;
    player_random player_2;
    player_random player_3;

    int population = 30; // 30
    int games_per_generation = 100; // 100
    int n_generations = 500; // 1000

    player_0.init_chromosomes(population);
    helper_0.init_chromosomes(population);
    helper_1.init_chromosomes(population);
    
    //Play a game of Ludo
    game g(&player_0, &player_1, &player_2, &player_3);
    // g.play_game();
    // cout << "Player " << g.get_winner() << " won the game!" << endl << endl;

    //Play many games of Ludo
    // int wins[] = {0, 0, 0, 0};
    for (int j = 0; j < n_generations; j++) {

        auto start = std::chrono::high_resolution_clock::now();

        // Start the additional thread to run along the main player 0.

        for (int i = 0; i < population*games_per_generation; i++)
        {
            g.reset();
            g.set_first(i%4); //alternate who starts the game
            g.play_game();

            // Add one to the score for the chromosome if it wins.
            if (g.get_winner() == 0)
                player_0.add_point();
            // Increment the current chromosome being tested every n games.
            if (i != 0 && i%games_per_generation == 0) {
                player_0.inc_current_chromosome();
            }
        }
        auto stop1 = std::chrono::high_resolution_clock::now();
        // Update the generation based on the points.
        player_0.evolve_generation();

        // Get the evolved generations:

        // Merge the evolved generations:

        // Share the best of all the generations:


        auto stop2 = std::chrono::high_resolution_clock::now();
        // player_1.evolve_generation();
        std::cout << "Generation number: " << j+1 << " / " << n_generations << "." << std::endl;
        auto games_duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop1-start);
        auto evolution_duration = std::chrono::duration_cast<std::chrono::microseconds>(stop2-stop1);
        std::cout << "Games played: " << population*games_per_generation << " in " << games_duration.count() << " milliseconds." << std::endl;
        std::cout << "Evolved in " << evolution_duration.count() << " microseconds." << std::endl;
        std::cout << std::string(15,'*') << std::endl;
    }

    int trial_games = 50000;
    
    int wins_1 = 0;
    int wins_2 = 0;
    for (int i = 0; i < trial_games; i++) {
        g.reset();
        g.set_first(i%4); //alternate who starts the game
        g.play_game();
        
        if (g.get_winner() == 0) {
            wins_1++;
        }
        // if (g.get_winner() == 1) {
        //     wins_2++;
        // }
    }

    std::cout << "The last gen AI player 0 won " << wins_1 << " times." << std::endl;
    std::cout << "Equal to " << (float)wins_1/trial_games*100 << "% winrate." << std::endl << std::endl;

    // std::cout << "The last gen AI player 1 won " << wins_2 << " times." << std::endl;
    // std::cout << "Equal to " << (float)wins_2/trial_games*100 << "% winrate." << std::endl;

    // player_0.set_learning(false);

    // wins_1 = 0;
    // for (int i = 0; i < trial_games; i++) {
    //     g.reset();
    //     g.set_first(i%4); //alternate who starts the game
    //     g.play_game();
        
    //     if (g.get_winner() == 0) {
    //         wins_1++;
    //     }
    // }

    // std::cout << "The best AI won " << wins_1 << " times." << std::endl;
    // std::cout << "Equal to " << (float)wins_1/trial_games*100 << "% winrate." << std::endl;

    // for(int i = 0; i < 4; i++)
    //     cout << "Player " << i << " won " << wins[i] << " games." << endl;


    std::cout << "End of main" << std::endl;
    return 0;
}


