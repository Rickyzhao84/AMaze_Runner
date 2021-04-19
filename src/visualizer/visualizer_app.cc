#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Log.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include <visualizer/visualizer_app.h>
#include <core/Location.h>

namespace visualizer_app {

    namespace visualizer {
        
        using ci::gl::TextureRef;
        using ci::Surface;
        using ci::gl::Texture;

        VisualizerApp::VisualizerApp()
                : game_map_(glm::vec2(kTopLeftCornerCoordinate, kTopLeftCornerCoordinate),
                            kDimension, kWindowSize) {
            ci::app::setWindowSize((int) kWindowSize + 200, (int) kWindowSize);
            game_map_.CreateNodes();
            game_map_.CreateMapModel();
            for (size_t i = 0; i < kDimension; i++) {
                for (size_t j = 0; j < kDimension; j++) {
                    if (game_map_.map_model_[i][j] == 1) {
                        location_.SetYCoord(i);
                        location_.SetXCoord(j);
                    }
                }
            }
        }

        void VisualizerApp::draw() {
            ci::Color8u color("turquoise");
            ci::gl::clear(color);
            game_map_.Draw();

            
        }

        void VisualizerApp::keyDown(ci::app::KeyEvent event) {
            switch (event.getCode()) {
                case ci::app::KeyEvent::KEY_LEFT: {
                    size_t original_x_coord = location_.GetXCoord();
                    if (original_x_coord != 0) {
                        location_.SetXCoord(original_x_coord - 1);
                        game_map_.UpdateMapPixelColor(location_.GetYCoord(), location_.GetXCoord());
                    }
                    
                    break;
                }
                case ci::app::KeyEvent::KEY_RIGHT: {
                    size_t original_x_coord = location_.GetXCoord();
                    if (original_x_coord != kDimension - 1) {
                        location_.SetXCoord(original_x_coord + 1);
                        game_map_.UpdateMapPixelColor(location_.GetYCoord(), location_.GetXCoord());
                    }
                    
                    break;
                }
                case ci::app::KeyEvent::KEY_DOWN: {
                    size_t original_y_coord = location_.GetYCoord();
                    if (original_y_coord != kDimension - 1) {
                        location_.SetYCoord(original_y_coord + 1);
                        game_map_.UpdateMapPixelColor(location_.GetYCoord(), location_.GetXCoord());
                    }
                    
                    break;
                }
                case ci::app::KeyEvent::KEY_UP: {
                    size_t original_y_coord = location_.GetYCoord();
                    if (original_y_coord != 0) {
                        location_.SetYCoord(original_y_coord - 1);
                        game_map_.UpdateMapPixelColor(location_.GetYCoord(), location_.GetXCoord());
                    }
                    
                    break;
                }
                
            }
            
        }

    }
}
