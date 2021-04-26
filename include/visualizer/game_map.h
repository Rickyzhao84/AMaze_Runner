#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "core/node.h"
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
            
            void MoveMonsters();
            
            void FindNextDirection(double pixel_side_length) const;
            
            /**
             * Create different nodes that will be placed on the map
             */
            void CreateNodes();
            
            /**
             * Create the 2d vector map model that represents the map
             */
            void CreateMapModel();
            
            /**
             * Set pixels the user has walked on to the color of starting node
             * @param row x coord
             * @param column y coord
             */
            void UpdateMapPixelColor(size_t row, size_t column, NextImage next_image);

            /**
             * Create animation (yet to be implemented)
             */
            void CreateAnimation();

            /**
             * Check if the pixel user wants to move to is an obstacle node
             * @param row x coord
             * @param column y coord
             * @return true if it's an obstacle, false if it's not
             */
            bool IsPixelAnObstacle(size_t row, size_t column);
            
            /**
             * Generate a random color that will be used to create animations
             * @return random size_t to create colors
             */
            size_t GenerateColorNumber();

            const static size_t kTotalColorNumbers = 256;
            
            const static size_t kNumOfObstacleNodes = 25;
            
            const static size_t kNumOfMonsterNodes = 5;
            
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
            std::vector<ObstacleNode> obstacle_nodes_;
            std::vector<MonsterNode> monster_nodes_;
            StartingNode starting_node_;
            EndingNode ending_node_;
            std::vector<glm::vec2> obstacle_pixels_;
            std::vector<glm::vec2> monster_pixels_;
        };

    
}