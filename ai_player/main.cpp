#include <iostream>
#include "game.h"
#include "test_game.h"
#include "iplayer.h"
#include "player_random.h"
#include "ai_player.h"

using namespace std;

int main()
{
    //Run the unit tests
    // test_game tester;
    // tester.run_all_tests();

    //Create players
    AiPlayer player_0;
    // player_random player_0;
    player_random player_1;
    player_random player_2;
    player_random player_3;

    int population = 20;
    int games_per_generation = 500;

    player_0.init_chromosomes(population);
    
    //Play a game of Ludo
    game g(&player_0, &player_1, &player_2, &player_3);
    // g.play_game();
    // cout << "Player " << g.get_winner() << " won the game!" << endl << endl;
    

    //Play many games of Ludo
    int wins[] = {0, 0, 0, 0};
    for (int j = 0; j < 100; j++) {

        for (int i = 0; i < population*games_per_generation; i++)
        {
            g.reset();
            g.set_first(i%4); //alternate who starts the game
            g.play_game();
            // wins[g.get_winner()]++;

            // Add one to the score for the chromosome if it wins.
            if (g.get_winner() == 0)
                player_0.add_point();
            // Increment the current chromosome being tested every 100 games.
            if (i != 0 && i%games_per_generation == 0) {
                // std::cout << "Incrementing chromosome" << std::endl;
                player_0.inc_current_chromosome();
            }
        }
        // Update the generation based on the points.
        player_0.evolve_generation();
        std::cout << j << std::endl;
    }
    for(int i = 0; i < 4; i++)
        cout << "Player " << i << " won " << wins[i] << " games." << endl;


    cout << "End of main" << endl;
    return 0;
}


