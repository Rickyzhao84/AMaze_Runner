#include <core/player.h>
#include <core/location.h>

namespace visualizer_app {
    
    Player::Player() {
    }
    
    void Player::MoveLeft(Location location) {
        size_t original_x_coord = location.GetXCoord();
        if (original_x_coord != 0) {
            location.SetXCoord(original_x_coord - 1);
        }
    }
    
    void Player::MoveRight(size_t dimension, Location location) {
        size_t original_x_coord = location.GetXCoord();
        if (original_x_coord != dimension - 1) {
            location.SetXCoord(original_x_coord + 1);
        }
    }
    
    void Player::MoveDown(size_t dimension, Location location) {
        size_t original_y_coord = location.GetYCoord();
        if (original_y_coord != dimension - 1) {
            location.SetYCoord(original_y_coord + 1);
        }
    }
    
    void Player::MoveUp(Location location) {
        size_t original_y_coord = location.GetYCoord();
        if (original_y_coord != 0) {
            location.SetYCoord(original_y_coord - 1);
        }
    }
    
}