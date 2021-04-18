#pragma once

#include <core/location.h>

namespace visualizer_app {
    class Player {
    public:
        
        Player();
        
        void MoveLeft(Location location_);
        
        void MoveRight(size_t dimension, Location location_);
        
        void MoveUp(Location location_);
        
        void MoveDown(size_t dimension, Location location_);
        
    private:

        size_t dimension_;
        
    };
}