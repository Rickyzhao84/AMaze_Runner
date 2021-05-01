#include <catch2/catch.hpp>

#include "cinder/app/App.h"
#include <visualizer/visualizer_app.h>
#include <core/Location.h>
#include <core/player.h>
#include <visualizer/game_map.h>
#include <visualizer/visualizer_app.h>

using glm::vec2;
using std::vector;

TEST_CASE("Map generates same amount of nodes as required") {
    visualizer_app::GameMap map_one(vec2(1,1), 25, 100);
    map_one.CreateMapModel();
    SECTION("Generates kNumOfObstaclesNodes obstacle nodes") {
        size_t count = 0;
        for (size_t row = 0; row < 25; row++) {
            for (size_t column = 0; column < 25; column++) {
                if (map_one.map_model_[row][column] == visualizer_app::NodeLabel::ObstacleNode) {
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
                if (map_one.map_model_[row][column] == visualizer_app::NodeLabel::StartingNode) {
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
                if (map_one.map_model_[row][column] == visualizer_app::NodeLabel::EndingNode) {
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
    map_one.CreateMapModel();
    map_two.CreateMapModel();
    vec2 starting_pixel_one = vec2(map_one.location_.GetXCoord(),map_one.location_.GetYCoord());
    vec2 starting_pixel_two = vec2(map_two.location_.GetXCoord(), map_two.location_.GetYCoord());
    REQUIRE(starting_pixel_one != starting_pixel_two);
}

TEST_CASE("Monster move closer to player") {
    visualizer_app::GameMap game_map(vec2(1, 1), 3, 5);
    vector<vector<visualizer_app::NodeLabel>> vector
            {
                    {visualizer_app::NodeLabel::MonsterNode, visualizer_app::NodeLabel::RegularNode, visualizer_app::NodeLabel::RegularNode},
                    {visualizer_app::NodeLabel::RegularNode, visualizer_app::NodeLabel::RegularNode, visualizer_app::NodeLabel::RegularNode},
                    {visualizer_app::NodeLabel::RegularNode, visualizer_app::NodeLabel::RegularNode, visualizer_app::NodeLabel::StartingNode}
            };
    game_map.map_model_ = vector;
    SECTION("Monster moves right first") {
        game_map.location_.SetXCoord(2);
        game_map.location_.SetYCoord(2);
        REQUIRE(game_map.map_model_[1][0] == visualizer_app::NodeLabel::RegularNode);
        game_map.MoveMonsters();
        REQUIRE(game_map.map_model_[1][0] == visualizer_app::NodeLabel::MonsterNode);
    }
    SECTION("Monster moves down when player is below") {
        game_map.location_.SetXCoord(0);
        game_map.location_.SetYCoord(2);
        REQUIRE(game_map.map_model_[0][1] == visualizer_app::NodeLabel::RegularNode);
        game_map.MoveMonsters();
        REQUIRE(game_map.map_model_[0][1] == visualizer_app::NodeLabel::MonsterNode);
    }
    SECTION("Monster doesn't move to player location_ if player is already at location_") {
        game_map.map_model_ =
                {
                        {visualizer_app::NodeLabel::MonsterNode, visualizer_app::NodeLabel::RegularNode, visualizer_app::NodeLabel::RegularNode},
                        {visualizer_app::NodeLabel::StartingNode, visualizer_app::NodeLabel::RegularNode, visualizer_app::NodeLabel::RegularNode},
                        {visualizer_app::NodeLabel::RegularNode, visualizer_app::NodeLabel::RegularNode, visualizer_app::NodeLabel::RegularNode}
                };
        game_map.location_.SetXCoord(0);
        game_map.location_.SetYCoord(1);
        REQUIRE(game_map.map_model_[0][0] == visualizer_app::NodeLabel::MonsterNode);
        game_map.MoveMonsters();
        REQUIRE(game_map.map_model_[0][0] == visualizer_app::NodeLabel::MonsterNode);
    }
    SECTION("Monster chooses to go another route if the previous is blocked by an obstacle") {
        game_map.map_model_ = 
                {
                        {visualizer_app::NodeLabel::MonsterNode, visualizer_app::NodeLabel::RegularNode, visualizer_app::NodeLabel::RegularNode},
                        {visualizer_app::NodeLabel::ObstacleNode, visualizer_app::NodeLabel::RegularNode, visualizer_app::NodeLabel::RegularNode},
                        {visualizer_app::NodeLabel::RegularNode, visualizer_app::NodeLabel::RegularNode, visualizer_app::NodeLabel::StartingNode}
                };
        game_map.location_.SetXCoord(1);
        game_map.location_.SetYCoord(2);
        REQUIRE(game_map.map_model_[0][1] == visualizer_app::NodeLabel::RegularNode);
        game_map.MoveMonsters();
        REQUIRE(game_map.map_model_[0][1] == visualizer_app::NodeLabel::MonsterNode);
    }
}