#include <catch2/catch.hpp>

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Log.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include <visualizer/visualizer_app.h>
#include <core/Location.h>
#include <visualizer/visualizer_app.h>

using glm::vec2;

TEST_CASE("Map generates a different starting point each game") {
    visualizer_app::VisualizerApp();
    visualizer_app::VisualizerApp second_game();
    vec2 starting_location_one = vec2(first_game().starting_location_.GetXCoord(), 
                                      first_game().starting_location_.GetYCoord());
    vec2 starting_location_two = vec2(second_game().starting_location_.GetXCoord(), 
                                      second_game().starting_location_.GetYCoord());
    
    REQUIRE(starting_location_one != starting_location_two);
}

TEST_CASE("Player can move using the arrow keys") {
    SECTION("Move up") {
        visualizer_app::VisualizerApp game;
        game.starting_location_.SetXCoord(10);
        game.starting_location_.SetYCoord(10);
    }
}