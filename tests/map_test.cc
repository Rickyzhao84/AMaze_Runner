#include <catch2/catch.hpp>

#include "cinder/app/App.h"
#include <visualizer/visualizer_app.h>
#include <core/Location.h>
#include <visualizer/game_map.h>
#include <visualizer/visualizer_app.h>

using glm::vec2;

TEST_CASE("Map generates same amount of nodes as required") {
    visualizer_app::GameMap map_one(vec2(1,1), 25, 100);
    map_one.CreateNodes();
    map_one.CreateMapModel();
    SECTION("Generates kNumOfObstaclesNodes obstacle nodes") {
        size_t count = 0;
        for (size_t row = 0; row < 25; row++) {
            for (size_t column = 0; column < 25; column++) {
                if (map_one.map_model_[row][column] == 3) {
                    count++;
                }
            }
        }
        REQUIRE(count == map_one.kNumOfObstacleNodes);
    }
    SECTION("Generates 1 starting node") {
        size_t count = 0;
        for (size_t row = 0; row < 25; row++) {
            for (size_t column = 0; column < 25; column++) {
                if (map_one.map_model_[row][column] == 1) {
                    count++;
                }
            }
        }
        REQUIRE(count == 1);
    }
    SECTION("Generates 1 ending node") {
        size_t count = 0;
        for (size_t row = 0; row < 25; row++) {
            for (size_t column = 0; column < 25; column++) {
                if (map_one.map_model_[row][column] == 2) {
                    count++;
                }
            }
        }
        REQUIRE(count == 1);
    }
}

TEST_CASE("Map generates a different starting point each game") {
    visualizer_app::GameMap map_one(vec2(1,1), 25, 100);
    visualizer_app::GameMap map_two(vec2(1,1), 25, 100);
    map_one.CreateNodes();
    map_one.CreateMapModel();
    map_two.CreateNodes();
    map_two.CreateMapModel();
    vec2 starting_pixel_one = vec2(map_one.GetCurrentLocationX(),map_one.GetCurrentLocationY());
    vec2 starting_pixel_two = vec2(map_two.GetCurrentLocationX(), map_two.GetCurrentLocationY());
    REQUIRE(starting_pixel_one != starting_pixel_two);
}

TEST_CASE("Player can move using the arrow keys") {
    SECTION("Move up") {

    }
}