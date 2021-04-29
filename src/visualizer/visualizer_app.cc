#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Log.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include <visualizer/visualizer_app.h>
#include <visualizer/game_map.h>
#include <core/Location.h>
#include "cinder/app/AppBase.h"

namespace visualizer_app {


    using ci::gl::TextureRef;
    using ci::Surface;
    using ci::gl::Texture;
    using std::vector;
    using glm::vec2;


    VisualizerApp::VisualizerApp()
            : game_map_(glm::vec2(kTopLeftCornerCoordinate, kTopLeftCornerCoordinate),
                        kDimension, kWindowSize) {
        ci::app::setWindowSize((int) kWindowSize + 250, (int) kWindowSize);
        game_map_.CreateNodes();
        game_map_.CreateMapModel();
        //Set starting_location_ same as the one in map_model_
        for (size_t i = 0; i < kDimension; i++) {
            for (size_t j = 0; j < kDimension; j++) {
                if (game_map_.map_model_[i][j] == NodeLabel::StartingNode) {
                    player_.location.SetXCoord(j);
                    player_.location.SetYCoord(i);
                }
            }
        }
        
    }

    void VisualizerApp::draw() {
        ci::Color8u color("turquoise");
        ci::gl::clear(color);
        button_.Draw();
        if (game_map_.map_model_[game_map_.location_.GetXCoord()][game_map_.location_.GetYCoord()] ==
            NodeLabel::EndingNode) {
            end_game_screen_.Draw();
            return;
        }
        game_map_.Draw();

    }

    void VisualizerApp::keyDown(ci::app::KeyEvent event) {
        switch (event.getCode()) {
            case ci::app::KeyEvent::KEY_LEFT: {
                player_.MoveLeft(game_map_);

                break;
            }
            case ci::app::KeyEvent::KEY_RIGHT: {
                player_.MoveRight(kDimension, game_map_);

                break;
            }
            case ci::app::KeyEvent::KEY_DOWN: {
                player_.MoveDown(kDimension, game_map_);

                break;
            }
            case ci::app::KeyEvent::KEY_UP: {
                player_.MoveUp(game_map_);

                break;
            }
        }
    }
}
