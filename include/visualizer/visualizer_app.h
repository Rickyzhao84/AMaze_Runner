#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "game_map.h"
#include "end_game_screen.h"
#include "button.h"
#include <core/Location.h>
#include <core/player.h>


namespace visualizer_app {
    
    const static glm::vec2 kButtonTopLeft(1100, 10);
    const static glm::vec2 kButtonBottomRight(1150, 40);


        class VisualizerApp : public ci::app::App {
        public:
            
            /**
             * Constructor of the app
             */
            VisualizerApp();
            
            /**
             * Draw the application and related items on the screen
             */
            void draw() override;

            /**
             * When user clicks down on a key
             * @param event 
             */
            void keyDown(ci::app::KeyEvent event) override;
            
            void mouseDown(ci::app::MouseEvent event);

            const size_t kDimension = 35;
            const double kTopLeftCornerCoordinate = 10;
            const double kWindowSize = 1000;

        private:
            GameMap game_map_;
            Button button_;
            Player player_;
            EndGame end_game_screen_;
        };


    
}