#include <iostream>
#include "game.h"
#include "test_game.h"
#include "iplayer.h"
#include "player_random.h"
#include "ai_player.h"

// using namespace std;

int main()
{
    //Run the unit tests
    // test_game tester;
    // tester.run_all_tests();

    //Create players
    AiPlayer player_0;
    // player_random player_0;
    // AiPlayer player_1;
    player_random player_1;
    player_random player_2;
    player_random player_3;

    int population = 45; // 30
    int games_per_generation = 100; // 100
    int n_generations = 2000; // 1000

    player_0.init_chromosomes(population);
    // player_1.init_chromosomes(population);
    
    //Play a game of Ludo
    game g(&player_0, &player_1, &player_2, &player_3);
    // g.play_game();
    // cout << "Player " << g.get_winner() << " won the game!" << endl << endl;

    //Play many games of Ludo
    // int wins[] = {0, 0, 0, 0};
    for (int j = 0; j < n_generations; j++) {

        for (int i = 0; i < population*games_per_generation; i++)
        {
            g.reset();
            g.set_first(i%4); //alternate who starts the game
            g.play_game();
            // wins[g.get_winner()]++;

            // Add one to the score for the chromosome if it wins.
            if (g.get_winner() == 0)
                player_0.add_point();
            // if (g.get_winner() == 1)
            //     player_1.add_point();
            // Increment the current chromosome being tested every 100 games.
            if (i != 0 && i%games_per_generation == 0) {
                // std::cout << "Incrementing chromosome" << std::endl;
                player_0.inc_current_chromosome();
                // player_1.inc_current_chromosome();
            }
            // std::cout << "***** New Game *****" << std::endl;
        }
        // Update the generation based on the points.
        player_0.evolve_generation();
        // player_1.evolve_generation();
        std::cout << j << std::endl;
    }

    int trial_games = 100000;
    
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


