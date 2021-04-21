#pragma once

#include <core/location.h>

namespace visualizer_app {
    class Player {
    public:
        
        Player();
        
        /**
         * Move to the pixel left of current location
         * @param location_ 
         */
        void MoveLeft(Location location_);
        
        /**
         * Move to the pixel right of current location
         * @param dimension 
         * @param location_ 
         */
        void MoveRight(size_t dimension, Location location_);
        
        /**
         * Move to the pixel on top of current location
         * @param location_ 
         */
        void MoveUp(Location location_);
        
        /**
         * Move to the pixel below current location
         * @param dimension 
         * @param location_ 
         */
        void MoveDown(size_t dimension, Location location_);

        Location location_;
        
    private:
        size_t dimension_;
        
    };
}