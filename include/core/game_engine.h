#pragma once

#include "player.h"

namespace visualizer_app {

    class GameEngine {

    public:
        /**
         * Empty constructor for creating object
         */
        GameEngine();

        /**
         * Handle each turn of when arrow key is registered
         * @param direction_num arbitrary number representing the 4 directions
         * @param player object reference
         * @param map game map reference
         */
        void HandleTurn(size_t direction_num, Player &player, GameMap &map);

        /**
         * Reset the map when player clicks restart and create a new map
         * @param player object reference
         * @param map game map reference
         */
        void ResetMap(Player &player, GameMap &map);
    };


}
