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
        ci::gl::TextureRef texture = ci::gl::Texture::create(
                ci::loadImage(kButtonImage));
        ci::Rectf object(top_left_corner_, bottom_right_corner_);

        ci::gl::draw(texture, object);
    }

}
