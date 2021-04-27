#include <catch2/catch.hpp>

#include "cinder/app/App.h"
#include <visualizer/visualizer_app.h>
#include <core/Location.h>
#include <core/player.h>
#include <visualizer/game_map.h>
#include <visualizer/visualizer_app.h>

using std::vector;
using glm::vec2;

TEST_CASE("Player can move using the arrow keys") {
    visualizer_app::Player player;
    visualizer_app::GameMap game_map(vec2(0,0), 3, 5);
    vector<vector<visualizer_app::NodeLabel>> vector
            {
                    {visualizer_app::NodeLabel::StartingNode, visualizer_app::NodeLabel::RegularNode, visualizer_app::NodeLabel::RegularNode},
                    {visualizer_app::NodeLabel::RegularNode, visualizer_app::NodeLabel::RegularNode, visualizer_app::NodeLabel::RegularNode},
                    {visualizer_app::NodeLabel::RegularNode, visualizer_app::NodeLabel::RegularNode, visualizer_app::NodeLabel::RegularNode}
            };
    game_map.map_model_ = vector;
    
    SECTION("Move right") {
        REQUIRE(player.location.GetXCoord() == 0);
        REQUIRE(player.location.GetYCoord() == 0);
        player.MoveRight(3, game_map);
        REQUIRE(player.location.GetXCoord() == 1);
        REQUIRE(player.location.GetYCoord() == 0);
    }
    SECTION("Move up") {
        player.location.SetXCoord(1);
        player.location.SetYCoord(1);
        player.MoveUp(game_map);
        REQUIRE(player.location.GetXCoord() == 1);
        REQUIRE(player.location.GetYCoord() == 0);

    }
    SECTION("Move down") {
        REQUIRE(player.location.GetXCoord() == 0);
        REQUIRE(player.location.GetYCoord() == 0);
        player.MoveDown(3, game_map);
        REQUIRE(player.location.GetXCoord() == 0);
        REQUIRE(player.location.GetYCoord() == 1);

    }
    SECTION("Move left") {
        player.location.SetXCoord(1);
        player.location.SetYCoord(1);
        player.MoveLeft(game_map);
        REQUIRE(player.location.GetXCoord() == 0);
        REQUIRE(player.location.GetYCoord() == 1);
    }
}

TEST_CASE("Obstacles and monsters should block player from moving to that direction") {
    visualizer_app::Player player;
    visualizer_app::GameMap game_map(vec2(0,0), 3, 5);
    vector<vector<visualizer_app::NodeLabel>> vector
            {
                    {visualizer_app::NodeLabel::MonsterNode, visualizer_app::NodeLabel::ObstacleNode, visualizer_app::NodeLabel::RegularNode},
                    {visualizer_app::NodeLabel::MonsterNode, visualizer_app::NodeLabel::RegularNode, visualizer_app::NodeLabel::ObstacleNode},
                    {visualizer_app::NodeLabel::RegularNode, visualizer_app::NodeLabel::ObstacleNode, visualizer_app::NodeLabel::RegularNode}
            };
    game_map.map_model_ = vector;

    SECTION("Attempt to move right to obstacle should fail") {
        player.MoveRight(3, game_map);
        REQUIRE(player.location.GetXCoord() == 1);
        REQUIRE(player.location.GetYCoord() == 0);
    }
    SECTION("Attempt to move down to monster should fail") {
        player.MoveDown(3, game_map);
        REQUIRE(player.location.GetXCoord() == 0);
        REQUIRE(player.location.GetYCoord() == 1);

    }
}

TEST_CASE("Player shouldn't go out of bounds") {
    visualizer_app::Player player;
    visualizer_app::GameMap game_map(vec2(0,0), 3, 5);
    vector<vector<visualizer_app::NodeLabel>> vector
            {
                    {visualizer_app::NodeLabel::StartingNode, visualizer_app::NodeLabel::RegularNode, visualizer_app::NodeLabel::RegularNode},
                    {visualizer_app::NodeLabel::RegularNode, visualizer_app::NodeLabel::RegularNode, visualizer_app::NodeLabel::RegularNode},
                    {visualizer_app::NodeLabel::RegularNode, visualizer_app::NodeLabel::RegularNode, visualizer_app::NodeLabel::RegularNode}
            };
    game_map.map_model_ = vector;
    
    SECTION("Cannot move left") {
        player.MoveLeft(game_map);
        REQUIRE(player.location.GetXCoord() == 0);
        REQUIRE(player.location.GetYCoord() == 0);
    }
    SECTION("Cannot move up") {
        player.MoveUp(game_map);
        REQUIRE(player.location.GetXCoord() == 0);
        REQUIRE(player.location.GetYCoord() == 0);
    }
}