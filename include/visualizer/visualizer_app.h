#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "game_map.h"
#include <core/Location.h>
#include <core/player.h>


namespace visualizer_app {


        class VisualizerApp : public ci::app::App {
        public:
            VisualizerApp();

            void draw() override;

            void keyDown(ci::app::KeyEvent event) override;

            const size_t kDimension = 25;
            const double kTopLeftCornerCoordinate = 50;
            const double kWindowSize = 1000;
            Location starting_location_;

        private:
            GameMap game_map_;
            Player player_;
        };


    
}