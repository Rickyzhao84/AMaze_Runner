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

    StartingNode::StartingNode(ci::Color nodeColor) : Node(nodeColor) {
        
    }
    
    EndingNode::EndingNode(ci::Color nodeColor) : Node(nodeColor) {
        
    }
    
    ObstacleNode::ObstacleNode(ci::Color nodeColor) : Node(nodeColor) {
        
    }
    
    MonsterNode::MonsterNode(ci::Color nodeColor) : Node(nodeColor) {
        
    }
}