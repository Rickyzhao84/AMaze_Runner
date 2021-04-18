#pragma once

#include <core/location.h>

namespace visualizer_app {
    class Player {
    public:
        
        Player();
        
        void MoveLeft();
        
        void MoveRight(size_t dimension);
        
        void MoveUp();
        
        void MoveDown(size_t dimension);
        
    private:

        Location location_;
        size_t dimension_;
        
    };
}