#include <core/player.h>
#include <core/location.h>
#include <visualizer/game_map.h>
#include <cinder/Cinder.h>

namespace visualizer_app {

    Player::Player() : location(0, 0) {
    }

    void Player::MoveLeft(GameMap &game_map) {
        size_t original_x_coord = location.GetXCoord();
        //Check if the left node is out of bounds, an obstacle, or a monster
        if (original_x_coord != 0 &&
            !game_map.IsPixelAnObstacle(original_x_coord - 1, location.GetYCoord())) {
            
            //Update the color of current node and image and move all monsters as well
            location.SetXCoord(original_x_coord - 1);
            game_map.UpdateMapPixel(location.GetYCoord(), location.GetXCoord(), NextImage::LookLeft);
            game_map.MoveMonsters();
        }

    }

    void Player::MoveRight(size_t dimension, GameMap &game_map) {
        size_t original_x_coord = location.GetXCoord();
        //Check if the right node is out of bounds, an obstacle, or a monster
        if (original_x_coord != dimension - 1 &&
            !game_map.IsPixelAnObstacle(original_x_coord + 1, location.GetYCoord())) {
            
            location.SetXCoord(original_x_coord + 1);
            game_map.UpdateMapPixel(location.GetYCoord(), location.GetXCoord(), NextImage::LookRight);
            game_map.MoveMonsters();
        }

    }

    void Player::MoveDown(size_t dimension, GameMap &game_map) {
        size_t original_y_coord = location.GetYCoord();
        //Check if the node below is out of bounds, an obstacle, or a monster
        if (original_y_coord != dimension - 1 &&
            !game_map.IsPixelAnObstacle(location.GetXCoord(), original_y_coord + 1)) {
            
            location.SetYCoord(original_y_coord + 1);
            game_map.UpdateMapPixel(location.GetYCoord(), location.GetXCoord(), NextImage::LookDown);
            game_map.MoveMonsters();
        }

    }

    void Player::MoveUp(GameMap &game_map) {
        size_t original_y_coord = location.GetYCoord();
        //Check if the node above is out of bounds, an obstacle, or a monster
        if (original_y_coord != 0 &&
            !game_map.IsPixelAnObstacle(location.GetXCoord(), original_y_coord - 1)) {
            
            location.SetYCoord(original_y_coord - 1);
            game_map.UpdateMapPixel(location.GetYCoord(), location.GetXCoord(), NextImage::LookUp);
            game_map.MoveMonsters();
        }

    }

}