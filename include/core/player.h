#pragma once

#include <core/location.h>
#include <visualizer/game_map.h>

namespace visualizer_app {
    class Player {
    public:

        Player();

        /**
         * Move to the pixel left of current location
         * @param game_map is the game_map player is playing on
         */
        void MoveLeft(GameMap &game_map);

        /**
         * Move to the pixel right of current location
         * @param dimension is the side length of map
         * @param game_map is the game_map player is playing on
         */
        void MoveRight(size_t dimension, GameMap &game_map);

        /**
         * Move to the pixel on top of current location
         * @param game_map is the game_map player is playing on
         */
        void MoveUp(GameMap &game_map);

        /**
         * Move to the pixel below current location
         * @param dimension is the side length of map
         * @param game_map is the game_map player is playing on
         */
        void MoveDown(size_t dimension, GameMap &game_map);

        Location location;

    private:
    };
}