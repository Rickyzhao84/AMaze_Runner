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
            
            void ChangeKeyUp();
            
            void ChangeKeyDown();
            
            void ChangeKeyLeft();
            
            void ChangeKeyRight();

            const size_t kDimension = 25;
            const double kTopLeftCornerCoordinate = 10;
            const double kWindowSize = 1000;
            Location starting_location_;

        private:
            GameMap game_map_;
            Player player_;
        };


    
}