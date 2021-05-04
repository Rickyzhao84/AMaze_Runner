#pragma once

#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "cinder/Log.h"
#include <visualizer/visualizer_app.h>


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
        game_map_.CreateMapModel();

        //Set starting_location_ same as the one in map_model_
        for (size_t i = 0; i < kDimension; i++) {
            for (size_t j = 0; j < kDimension; j++) {
                if (game_map_.map_model_[i][j] == NodeLabel::StartingNode) {
                    player_.location_.SetXCoord(j);
                    player_.location_.SetYCoord(i);
                }
            }
        }
    }

    void VisualizerApp::draw() {
        ci::Color8u color("turquoise");
        ci::gl::clear(color);
        button_.Draw();

        //Check if player is located at the EndingNode, return EndGame drawing if so
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
                game_engine_.HandleTurn(1, player_, game_map_);

                break;
            }
            case ci::app::KeyEvent::KEY_RIGHT: {
                game_engine_.HandleTurn(2, player_, game_map_);

                break;
            }
            case ci::app::KeyEvent::KEY_DOWN: {
                game_engine_.HandleTurn(3, player_, game_map_);

                break;
            }
            case ci::app::KeyEvent::KEY_UP: {
                game_engine_.HandleTurn(4, player_, game_map_);

                break;
            }
        }
    }

    void VisualizerApp::mouseDown(ci::app::MouseEvent event) {
        //Check if the place where user clicked is within the restart button range
        if (event.getX() > kButtonTopLeft.x && event.getX() < kButtonBottomRight.x) {
            if (event.getY() > kButtonTopLeft.y && event.getY() < kButtonBottomRight.y) {
                game_engine_.ResetMap(player_, game_map_);
            }
        }
    }
}
