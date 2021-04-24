#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"


namespace visualizer_app {

    class Node {

    public:
        /**
         * Normal node that user can walk on
         * @param node_color color of a 'walkable' node
         */
        Node(ci::Color node_color);
        
        void SetNodeColor(const cinder::Color &nodeColor);

        const cinder::Color &GetNodeColor() const;

    private:
        ci::Color node_color_;
    };

    class StartingNode : public Node {
    public:
        /**
         * Starting node where the game begins
         * @param nodeColor of starting node 
         */
        StartingNode(ci::Color nodeColor);
    };

    class EndingNode : public Node {
    public:
        /**
         * Ending node where the game ends
         * @param nodeColor  of ending node
         */
        EndingNode(ci::Color nodeColor);
    };

    class ObstacleNode : public Node {
    public:
        /**
         * Obstacle node where user cannot walk on
         * @param nodeColor of obstacle node
         */
        ObstacleNode(ci::Color nodeColor);
    };
    
    class MonsterNode : public Node {
    public:
        
        MonsterNode(ci::Color nodeColor);
    };

}