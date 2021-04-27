#include <glm/glm.hpp>
#include "visualizer/button.h"

namespace visualizer_app {
    
    using glm::vec2;
    
    Button::Button(vec2 top_left_corner, vec2 bottom_right_corner) {
        top_left_corner_ = top_left_corner;
        bottom_right_corner_ = bottom_right_corner;
    }
    
    void Button::Draw() const {
        ci::Rectf button(top_left_corner_, bottom_right_corner_);
        ci::gl::drawSolidRect(button);
        ci::gl::drawStrokedRect(button);
        ci::gl::color(ci::Color("green"));
    }

    Button::Button() {
        top_left_corner_ = vec2(1100, 10);
        bottom_right_corner_ = vec2(1150, 40);
    }


}
