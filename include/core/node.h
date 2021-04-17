#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"


namespace visualizer_app {
    
    class Node {
        
    public:
        
        Node(ci::Color node_color);
        
        void SetColor(ci::Color);
        
    private:
        
        ci::Color node_color_;
    };
    
    class StartingNode: public Node {
        
    };
    
    class EndingNode: public Node {
        
    };
    
    class ObstacleNode: public Node {
        
    };
    
}