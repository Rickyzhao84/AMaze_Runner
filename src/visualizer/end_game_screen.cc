#include <visualizer/end_game_screen.h>

namespace visualizer_app {
    
    using glm::vec2;
    
    EndGame::EndGame(double top_left_corner) {
        top_left_corner_ = top_left_corner;
    }
    
    EndGame::EndGame() {
        top_left_corner_ = 10;
    }
    
    void EndGame::Draw() const {
        game_map_.DrawImage(vec2(top_left_corner_,top_left_corner_), vec2(top_left_corner_ + 500, top_left_corner_ + 500), kGameOverImage);
    }
    
}
