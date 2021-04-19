#pragma once

#include <cstddef>

namespace visualizer_app {
    
    class Location {
        
    public:
        
        Location(size_t row, size_t column);
        
        Location();

        const size_t GetYCoord() const;

        void SetYCoord(const size_t &yCoord);

        const size_t GetXCoord() const;

        void SetXCoord(const size_t &xCoord);

    private:
        
        size_t x_coord_;
        size_t y_coord_;
        
    };
    
}