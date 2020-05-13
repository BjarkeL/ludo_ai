#ifndef AI_PLAYER_H
#define AI_PLAYER_H

#include "iplayer.h"
#include <iostream>
#include <vector>
#include "positions_and_dice.h"
#include <random>

class AiPlayer : public iplayer {
public:
    AiPlayer();

private:
    int make_decision();
};

#endif // AI_PLAYER_H