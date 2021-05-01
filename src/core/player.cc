#include <core/player.h>
#include <core/location.h>
#include <visualizer/game_map.h>
#include <cinder/Cinder.h>

namespace visualizer_app {

    Player::Player() : location_(0, 0) {
    }

    bool Player::MoveLeft(GameMap &game_map) {
        size_t original_x_coord = location_.GetXCoord();
        //Check if the left node is out of bounds, an obstacle, or a monster
        if (original_x_coord != 0 &&
            !game_map.IsPixelAnObstacle(original_x_coord - 1, location_.GetYCoord())) {
            
            //Update the color of current node and image and move all monsters as well
            location_.SetXCoord(original_x_coord - 1);
            game_map.UpdateToNewLocation(location_.GetYCoord(), location_.GetXCoord(), NextImage::LookLeft);
            return true;
        }

        return false;
    }

    bool Player::MoveRight(size_t dimension, GameMap &game_map) {
        size_t original_x_coord = location_.GetXCoord();
        //Check if the right node is out of bounds, an obstacle, or a monster
        if (original_x_coord != dimension - 1 &&
            !game_map.IsPixelAnObstacle(original_x_coord + 1, location_.GetYCoord())) {
            
            location_.SetXCoord(original_x_coord + 1);
            game_map.UpdateToNewLocation(location_.GetYCoord(), location_.GetXCoord(), NextImage::LookRight);
            return true;
        }

        return false;
    }

    bool Player::MoveDown(size_t dimension, GameMap &game_map) {
        size_t original_y_coord = location_.GetYCoord();
        //Check if the node below is out of bounds, an obstacle, or a monster
        if (original_y_coord != dimension - 1 &&
            !game_map.IsPixelAnObstacle(location_.GetXCoord(), original_y_coord + 1)) {
            
            location_.SetYCoord(original_y_coord + 1);
            game_map.UpdateToNewLocation(location_.GetYCoord(), location_.GetXCoord(), NextImage::LookDown);
            return true;
        }

        return false;
    }

    bool Player::MoveUp(GameMap &game_map) {
        size_t original_y_coord = location_.GetYCoord();
        //Check if the node above is out of bounds, an obstacle, or a monster
        if (original_y_coord != 0 &&
            !game_map.IsPixelAnObstacle(location_.GetXCoord(), original_y_coord - 1)) {
            
            location_.SetYCoord(original_y_coord - 1);
            game_map.UpdateToNewLocation(location_.GetYCoord(), location_.GetXCoord(), NextImage::LookUp);
            return true;
        }
        
        return false;
    }

}