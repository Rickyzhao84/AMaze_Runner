#pragma once

#include <core/location.h>
#include <visualizer/game_map.h>

namespace visualizer_app {
    class Player {
    public:

        Player();

        /**
         * Move to the pixel left of current location_
         * @param game_map is the game_map player is playing on
         * @return true with player has moved left, false if not
         */
        bool MoveLeft(GameMap &game_map);

        /**
         * Move to the pixel right of current location_
         * @param dimension is the side length of map
         * @param game_map is the game_map player is playing on
         * @return true with player has moved right, false if not
         */
        bool MoveRight(size_t dimension, GameMap &game_map);

        /**
         * Move to the pixel on top of current location_
         * @param game_map is the game_map player is playing on
         * @return true with player has moved up, false if not
         */
        bool MoveUp(GameMap &game_map);

        /**
         * Move to the pixel below current location_
         * @param dimension is the side length of map
         * @param game_map is the game_map player is playing on
         * @return true with player has moved down, false if not
         */
        bool MoveDown(size_t dimension, GameMap &game_map);

        Location location_;
    };
}