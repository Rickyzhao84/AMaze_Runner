#pragma once
#include <visualizer/game_map.h>

namespace visualizer_app {
    
    class EndGame {
        
    public:
        
        EndGame(double top_left_corner);
        
        EndGame();
        
        void Draw() const;

        std::string kGameOverImage = "../../../gameover.jpg";
        
    private:
        double top_left_corner_;
        GameMap game_map_;
    };
}