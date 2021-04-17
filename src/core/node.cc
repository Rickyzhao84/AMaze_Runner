#include <core/node.h>

namespace visualizer_app {
    
    Node::Node(ci::Color node_color) {
        node_color_ = node_color;
    }
    
    

    const cinder::Color &Node::GetNodeColor() const {
        return node_color_;
    }

    void Node::SetNodeColor(const cinder::Color &nodeColor) {
        node_color_ = nodeColor;
    }

}