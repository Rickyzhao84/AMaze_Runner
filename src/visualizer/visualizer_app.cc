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
        }

        void VisualizerApp::draw() {
            ci::Color8u color("turquoise");
            ci::gl::clear(color);
            game_map_.Draw();

            
        }

        void VisualizerApp::keyDown(ci::app::KeyEvent event) {
            switch (event.getCode()) {
                case ci::app::KeyEvent::KEY_LEFT: {
                }
                case ci::app::KeyEvent::KEY_RIGHT: {
                    
                }
                case ci::app::KeyEvent::KEY_DOWN: {
                    
                }
                case ci::app::KeyEvent::KEY_UP: {

                }
            }
        }

    }
}
