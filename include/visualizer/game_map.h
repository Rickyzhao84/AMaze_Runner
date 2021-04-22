#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "core/node.h"


namespace visualizer_app {


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

            /**
             * Draw obstacles and their colors on the map
             */
            void Draw() const;
            
            void DrawCharacter() const;
            
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
            void UpdateMapPixelColor(size_t row, size_t column);

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
            
            const static size_t kNumOfObstacleNodes = 20;
            
            const ci::Color kObstacleColor = "red";
            
            const ci::Color kEndingNodeColor = "green";
            
            const ci::Color kStartingNodeColor = "yellow";

            size_t GetCurrentLocationX() const;

            size_t GetCurrentLocationY() const;

            std::vector<std::vector<size_t>> map_model_;

        private:
            
            glm::vec2 top_left_corner_;
            size_t dimension_;
            double map_size_;
            std::vector<ObstacleNode> obstacle_nodes_;
            StartingNode starting_node_;
            EndingNode ending_node_;
            size_t current_location_x_;
            size_t current_location_y_;
            std::vector<glm::vec2> obstacle_pixels_;
        };

    
}