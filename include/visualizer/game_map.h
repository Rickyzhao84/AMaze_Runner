#pragma once

#include "cinder/gl/gl.h"

namespace visualizer_app {
    
    
    class GameMap {
        
    public:
        
        GameMap(const glm::vec2& top_left_corner, size_t dimension,
                double map_size);
        
        void Draw() const;
        
        size_t GenerateColorNumber();
        
        const static size_t kTotalColorNumbers = 256;
        
    private:
        
        glm::vec2 top_left_corner_;
        size_t dimension_;
        double map_size_;
    };
    
    
}