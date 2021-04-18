#pragma once

#include <core/location.h>

namespace visualizer_app {
    class Player {
    public:
        
        Player(size_t dimension);
        
        void MoveLeft();
        
        void MoveRight();
        
        void MoveUp();
        
        void MoveDown();
        
    private:

        Location location_();
        size_t dimension_;
        
    };
}