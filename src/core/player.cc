#include <core/player.h>
#include <core/location.h>

namespace visualizer_app {
    
    Player::Player() {
    }
    
    void Player::MoveLeft(Location location_) {
        size_t original_x_coord = location_.GetYCoord();
        if (original_x_coord != 0) {
            location_.SetYCoord(original_x_coord - 1);
        }
    }
    
    void Player::MoveRight(size_t dimension, Location location_) {
        size_t original_x_coord = location_.GetYCoord();
        if (original_x_coord != dimension - 1) {
            location_.SetYCoord(original_x_coord + 1);
        }
    }
    
    void Player::MoveDown(size_t dimension, Location location_) {
        size_t original_y_coord = location_.GetXCoord();
        if (original_y_coord != dimension - 1) {
            location_.SetXCoord(original_y_coord + 1);
        }
    }
    
    void Player::MoveUp(Location location_) {
        size_t original_y_coord = location_.GetXCoord();
        if (original_y_coord != 0) {
            location_.SetXCoord(original_y_coord - 1);
        }
    }
    
}