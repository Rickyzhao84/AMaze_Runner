#pragma once

#include "player.h"

namespace visualizer_app {
    
    class GameEngine {
        
    public:
        GameEngine();
        
        void HandleTurn(size_t direction_num, Player &player, GameMap &map);
    };
    
    
}
