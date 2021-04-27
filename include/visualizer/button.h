#pragma once

#include <glm/vec2.hpp>
#include "end_game_screen.h"

namespace visualizer_app {

    class Button {

    public:

        Button(glm::vec2 top_left_corner, glm::vec2 bottom_right_corner);

        /**
         * Draw the button
         */
        void Draw() const;

    private:

        glm::vec2 top_left_corner_;
        glm::vec2 bottom_right_corner_;
        
    };
}
