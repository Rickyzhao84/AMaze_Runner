#pragma once

#include "cinder/gl/gl.h"

namespace visualizer_app {
    
    
    class GameMap {
        
    public:
        
        GameMap(const glm::vec2& top_left_corner, size_t dimension,
                double map_size);
        
        void Draw() const;
        
    private:
        
        glm::vec2 top_left_corner_;
        size_t dimension_;
        double map_size_;
    };
    
    
}