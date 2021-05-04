#include <core/game_engine.h>
#include <core/player.h>
#include <visualizer/game_map.h>

namespace visualizer_app {
    
    using std::vector;
    
    GameEngine::GameEngine() {
        
    }

    void GameEngine::HandleTurn(size_t direction_num, Player &player, GameMap &map) {
        
        //Only move monster if the player has moved
        if (direction_num == 1 && player.MoveLeft(map)) {
            map.MoveMonsters();
        } else if (direction_num == 2 && player.MoveRight(map.dimension_, map)) {
            map.MoveMonsters();
        } else if (direction_num == 3 && player.MoveDown(map.dimension_, map)) {
            map.MoveMonsters();
        } else if (direction_num == 4 && player.MoveUp(map)) {
            map.MoveMonsters();
        } 
        
        return;
    }
    
    void GameEngine::ResetMap(Player &player, GameMap &map) {
        map.Clear();
        map.map_model_ = vector<vector<NodeLabel>>(map.dimension_, 
                    vector<NodeLabel>(map.dimension_, NodeLabel::RegularNode));
        map.CreateMapModel();
        //Set starting_location_ same as the one in map_model_
        for (size_t i = 0; i < map.dimension_; i++) {
            for (size_t j = 0; j < map.dimension_; j++) {
                if (map.map_model_[i][j] == NodeLabel::StartingNode) {
                    player.location_.SetXCoord(j);
                    player.location_.SetYCoord(i);
                }
            }
        }
    }
    
}
