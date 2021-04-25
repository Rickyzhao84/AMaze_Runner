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
                        starting_location_.SetYCoord(i);
                        starting_location_.SetXCoord(j);
                    }
                }
            }
        }
        
        VisualizerApp::VisualizerApp(GameMap game_map)
                : game_map_(glm::vec2(kTopLeftCornerCoordinate, kTopLeftCornerCoordinate),
                            kDimension, kWindowSize) {
            game_map_.CreateNodes();
            game_map_.CreateMapModel();
            //Set starting_location_ same as the one in map_model_
            for (size_t i = 0; i < kDimension; i++) {
                for (size_t j = 0; j < kDimension; j++) {
                    if (game_map_.map_model_[i][j] == NodeLabel::StartingNode) {
                        starting_location_.SetYCoord(i);
                        starting_location_.SetXCoord(j);
                    }
                }
            }
        }

        void VisualizerApp::draw() {
            ci::Color8u color("turquoise");
            ci::gl::clear(color);

            if (game_map_.map_model_[game_map_.current_location_x_][game_map_.current_location_y_] == NodeLabel::EndingNode) {
                end_game_screen_.Draw();
                return;
            }
            game_map_.Draw();
            
        }

        void VisualizerApp::keyDown(ci::app::KeyEvent event) {
            switch (event.getCode()) {
                case ci::app::KeyEvent::KEY_LEFT: {
                    ChangeKeyLeft();
                    
                    break;
                }
                case ci::app::KeyEvent::KEY_RIGHT: {
                    ChangeKeyRight();
                    
                    break;
                }
                case ci::app::KeyEvent::KEY_DOWN: {
                    ChangeKeyDown();
                    
                    break;
                }
                case ci::app::KeyEvent::KEY_UP: {
                    ChangeKeyUp();
                    
                    break;
                }
            }
        }
        
        void VisualizerApp::ChangeKeyUp() {
            size_t original_y_coord = starting_location_.GetYCoord();
            //Can't move when user is about to go out of bounds
            if (original_y_coord != 0 &&
                !game_map_.IsPixelAnObstacle(starting_location_.GetXCoord(), original_y_coord - 1)) {
                starting_location_.SetYCoord(original_y_coord - 1);
                game_map_.UpdateMapPixelColor(starting_location_.GetYCoord(), starting_location_.GetXCoord(), NextImage::LookUp);
                game_map_.MoveMonsters();
            }
        }
        
        void VisualizerApp::ChangeKeyDown() {
            size_t original_y_coord = starting_location_.GetYCoord();
            //Can't move when user is about to go out of bounds
            if (original_y_coord != kDimension - 1 &&
                !game_map_.IsPixelAnObstacle(starting_location_.GetXCoord(), original_y_coord + 1)) {
                starting_location_.SetYCoord(original_y_coord + 1);
                game_map_.UpdateMapPixelColor(starting_location_.GetYCoord(), starting_location_.GetXCoord(), NextImage::LookDown);
                game_map_.MoveMonsters();
            }
        }
        
        void VisualizerApp::ChangeKeyLeft() {
            size_t original_x_coord = starting_location_.GetXCoord();
            //Can't move when user is about to go out of bounds
            if (original_x_coord != 0 &&
                !game_map_.IsPixelAnObstacle(original_x_coord - 1, starting_location_.GetYCoord())) {
                starting_location_.SetXCoord(original_x_coord - 1);
                game_map_.UpdateMapPixelColor(starting_location_.GetYCoord(), starting_location_.GetXCoord(), NextImage::LookLeft);
                game_map_.MoveMonsters();
            }
        }
        
        void VisualizerApp::ChangeKeyRight() {
            size_t original_x_coord = starting_location_.GetXCoord();
            //Can't move when user is about to go out of bounds
            if (original_x_coord != kDimension - 1 &&
                !game_map_.IsPixelAnObstacle(original_x_coord + 1, starting_location_.GetYCoord())) {
                starting_location_.SetXCoord(original_x_coord + 1);
                game_map_.UpdateMapPixelColor(starting_location_.GetYCoord(), starting_location_.GetXCoord(), NextImage::LookRight);
                game_map_.MoveMonsters();
            }

        }
}
