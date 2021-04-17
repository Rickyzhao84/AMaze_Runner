#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"


namespace visualizer_app {

    class Node {

    public:

        Node(ci::Color node_color);

        void SetNodeColor(const cinder::Color &nodeColor);

        const cinder::Color &GetNodeColor() const;

    private:
        ci::Color node_color_;
    };

    class StartingNode : public Node {
    public:
        StartingNode(ci::Color nodeColor);
    };

    class EndingNode : public Node {
    public:
        EndingNode(ci::Color nodeColor);
    };

    class ObstacleNode : public Node {
    public:
        ObstacleNode(ci::Color nodeColor);
    };

}