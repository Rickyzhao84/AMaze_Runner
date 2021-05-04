#pragma once

#include <visualizer/game_map.h>

namespace visualizer_app {

    class EndGame {

    public:

        /**
         * Creates the image of end game scenario
         * @param top_left_corner is the top left corner of end game image
         */
        EndGame(double top_left_corner);

        EndGame();

        /**
         * Draw the image
         */
        void Draw() const;

        std::string kGameOverImage = "../../../gameover.jpg";

        const static size_t kFrameDifference = 1000;

    private:
        double top_left_corner_;
        GameMap game_map_;
    };
}