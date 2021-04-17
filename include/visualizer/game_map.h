#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"


namespace visualizer_app {
    
    namespace visualizer {

        class GameMap {

        public:

            GameMap(const glm::vec2 &top_left_corner, size_t dimension,
                    double map_size);
            

            void Draw() const;

            void CreateAnimation();

            size_t GenerateColorNumber();

            const static size_t kTotalColorNumbers = 256;

            //const static size_t kNumOfObstacleNodes = kDimension;

        private:

            glm::vec2 top_left_corner_;
            size_t dimension_;
            double map_size_;
        };

    }
}