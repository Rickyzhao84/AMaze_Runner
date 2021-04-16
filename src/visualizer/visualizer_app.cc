#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include <visualizer/visualizer_app.h>

namespace visualizer_app {
    
VisualizerApp::VisualizerApp(): game_map_(glm::vec2(kTopLeftCornerCoordinate, kTopLeftCornerCoordinate),
                                          kDimension, kWindowSize) {
    ci::app::setWindowSize((int)kWindowSize, (int)kWindowSize);
}

void VisualizerApp::draw() {
    game_map_.Draw();
}

void VisualizerApp::keyDown(ci::app::KeyEvent event) {
    
}
    
}
