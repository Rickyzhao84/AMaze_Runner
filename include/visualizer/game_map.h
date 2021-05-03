#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "core/location.h"

namespace visualizer_app {

    enum class NodeLabel {
        StartingNode,
        EndingNode,
        ObstacleNode,
        MonsterNode,
        RegularNode
    };
    
    enum class NextImage {
        LookUp,
        LookDown,
        LookLeft,
        LookRight
    };

        class GameMap {

        public:

            /**
             * Constructor of a game map
             * @param top_left_corner of game map
             * @param dimension number of rows and columns of pixels in the map
             * @param map_size is size of map
             */
            GameMap(const glm::vec2 &top_left_corner, size_t dimension,
                    double map_size);
            
            GameMap();

            /**
             * Draw obstacles and their colors on the map
             */
            void Draw() const;
            
            /**
             * Draw the different nodes for the GameMap on to the screen
             * @param row x coord
             * @param column y coord
             */
            NodeLabel DrawNodes(size_t row, size_t column) const;
            
            /**
             * Draw an image on to the screen based on the coordinates given and filepath
             * @param top_left x coordinate
             * @param bottom_right y coordinate
             * @param path is the image file
             */
            void DrawImage(glm::vec2 top_left, glm::vec2 bottom_right, std::string path) const;
            
            /**
             * Move monsters every step when player is moved
             */
            void MoveMonsters();
            
            void TakeTurn(ci::app::KeyEvent);
            
            void SetNextMonstersLocation(float prev_x, float prev_y, float next_x, float next_y);
            
            /**
             * Find the next direction where player is heading and draw character image facing that direction
             * @param pixel_side_length is side length of a pixel
             */
            void FindNextDirection(double pixel_side_length) const;
            
            /**
             * Create the 2d vector map model that represents the map
             */
            void CreateMapModel();
            
            void CreateEndPoint();
            
            /**
             * Create monster locations every frame
             */
            void CreateMonsterLocations();
            
            /**
             * Set pixel color, new user location_, and next character image
             * @param row x coord
             * @param column y coord
             */
            void UpdateToNewLocation(size_t row, size_t column, NextImage next_image);

            /**
             * Check if the pixel user wants to move to is an obstacle node or monster node
             * @param row x coord
             * @param column y coord
             * @return true if it's an obstacle, false if it's not
             */
            bool IsPixelAnObstacle(size_t row, size_t column);
            
            /**
             * Clear map and its related nodes
             */
            void Clear();

            const static size_t kDistanceThreshold = 15;
            
            const static size_t kNumOfObstacleNodes = 50;
            
            const static size_t kNumOfMonsterNodes = 10;
            
            const ci::Color kObstacleColor = "red";
            
            const ci::Color kEndingNodeColor = "green";
            
            const ci::Color kStartingNodeColor = "yellow";
            
            const ci::Color kMonsterNodeColor = "white";
            
            const ci::Color KRegularNodeColor = "black";
            
            std::string kMonsterImage = "../../../monster.jpg";
            
            std::string kLookDownImage = "../../../looking_down.jpg";
            
            std::string kLookUpImage = "../../../looking_up.jpg";
            
            std::string kLookLeftImage = "../../../looking_left.jpg";
            
            std::string kLookRightImage = "../../../looking_right.jpg";
            
            NextImage determine_next_image = NextImage::LookUp;

            std::vector<std::vector<NodeLabel>> map_model_;

            std::vector<glm::vec2> monster_locations_;
            
            Location location_;
            
            
        private:
            
            glm::vec2 top_left_corner_;
            size_t dimension_;
            double map_size_;
            std::vector<glm::vec2> obstacle_pixels_;
            std::vector<glm::vec2> monster_pixels_;
        };

    
}