#pragma once

#include <glm/vec2.hpp>
#include "end_game_screen.h"

namespace visualizer_app {

    class Button {

    public:

        Button();

        /**
         * Draw the button for restart
         */
        void Draw() const;

        std::string kButtonImage = "../../../restart.png";

    private:

        glm::vec2 top_left_corner_;
        glm::vec2 bottom_right_corner_;

    };
}
