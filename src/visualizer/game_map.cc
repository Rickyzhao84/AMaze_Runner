#include <visualizer/game_map.h>

namespace visualizer_app {
    
    using glm::vec2;
    
    GameMap::GameMap(const glm::vec2 &top_left_corner, size_t dimension, double map_size) {
        top_left_corner_ = top_left_corner;
        dimension_ = dimension;
        map_size_ = map_size;
    }
    
    void GameMap::Draw() const {
        for (size_t row = 0; row < dimension_; row++) {
            for (size_t column = 0; column < dimension_; column++) {
                double pixel_side_length = map_size_ / dimension_;
                vec2 pixel_top_left = top_left_corner_ + vec2(column * pixel_side_length,
                                                              row * pixel_side_length);
                vec2 bottom_right_corner = pixel_top_left + vec2(pixel_side_length,pixel_side_length);
                ci::Rectf grid(pixel_top_left, bottom_right_corner);
                ci::gl::drawSolidRect(grid);
                ci::gl::color(ci::Color("white"));
                ci::gl::drawStrokedRect(grid);
            }
        }
    }
    
}