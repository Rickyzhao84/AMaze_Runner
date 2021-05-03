#include <core/game_engine.h>
#include <core/player.h>
#include <visualizer/game_map.h>

namespace visualizer_app {
    
    GameEngine::GameEngine() {
        
    }

    void GameEngine::HandleTurn(size_t direction_num, Player &player, GameMap &map) {
        if (direction_num == 1 && player.MoveLeft(map)) {
            map.MoveMonsters();
        } else if (direction_num == 2 && player.MoveRight(map.dimension_, map)) {
            map.MoveMonsters();
        } else if (direction_num == 3 && player.MoveDown(map.dimension_, map)) {
            map.MoveMonsters();
        } else if (direction_num == 4 && player.MoveUp(map)) {
            map.MoveMonsters();
        }
    }
    
}
