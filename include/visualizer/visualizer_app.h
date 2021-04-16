#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "game_map.h"


namespace visualizer_app {

    class VisualizerApp : public ci::app::App {
    public:
        VisualizerApp();
        void draw() override;
        void keyDown(ci::app::KeyEvent event) override;
        
        const double kTopLeftCornerCoordinate = 50;
        const double kWindowSize = 1000;
        const size_t kDimension = 35;
        
    private:
        
        GameMap game_map_;
        
    };


}
