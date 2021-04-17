#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "core/node.h"


namespace visualizer_app {
    
    namespace visualizer {

        class GameMap {

        public:

            GameMap(const glm::vec2 &top_left_corner, size_t dimension,
                    double map_size);
            

            void Draw() const;
            
            void CreateNodes();
            
            void CreateMapModel();

            void CreateAnimation();

            size_t GenerateColorNumber();

            const static size_t kTotalColorNumbers = 256;
            
            const static size_t kNumOfObstacleNodes = 20;
            
            const ci::Color kObstacleColor = "black";
            
            const ci::Color kEndingNodeColor = "green";
            
            const ci::Color kStartingNodeColor = "yellow";

        private:

            glm::vec2 top_left_corner_;
            size_t dimension_;
            double map_size_;
            std::vector<ObstacleNode> obstacle_nodes_;
            StartingNode starting_node_;
            EndingNode ending_node_;
            std::vector<std::vector<size_t>> map_model_;
        };

    }
}