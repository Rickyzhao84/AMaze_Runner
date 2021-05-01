#include <glm/glm.hpp>
#include <visualizer/visualizer_app.h>
#include "visualizer/button.h"

namespace visualizer_app {
    
    using glm::vec2;

    Button::Button() {
        top_left_corner_ = kButtonTopLeft;
        bottom_right_corner_ = kButtonBottomRight;
    }
    
    void Button::Draw() const {
        ci::Rectf button(top_left_corner_, bottom_right_corner_);
        ci::gl::drawSolidRect(button);
        ci::gl::drawStrokedRect(button);
        ci::gl::color(ci::Color("green"));
    }

    void Button::SetTopLeftCorner(const vec2 &topLeftCorner) {
        top_left_corner_ = topLeftCorner;
    }

}
