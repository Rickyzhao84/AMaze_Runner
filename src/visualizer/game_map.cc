#include <visualizer/game_map.h>

namespace visualizer_app {
    

        using glm::vec2;
        using std::vector;
        using std::string;

        GameMap::GameMap(const glm::vec2 &top_left_corner, size_t dimension, double map_size)
                : starting_node_(cinder::Color()), ending_node_(cinder::Color()) {
            top_left_corner_ = top_left_corner;
            dimension_ = dimension;
            map_model_ = vector<vector<size_t>>(dimension_, vector<size_t>(dimension_, 0));
            map_size_ = map_size;
        }

        void GameMap::Draw() const {
            for (size_t row = 0; row < dimension_; row++) {
                for (size_t column = 0; column < dimension_; column++) {
                    double pixel_side_length = map_size_ / dimension_;
                    //Find the top left of pixel map from top left of window
                    vec2 pixel_top_left = top_left_corner_ + vec2(column * pixel_side_length,
                                                                  row * pixel_side_length);
                    
                    vec2 bottom_right_corner = pixel_top_left + vec2(pixel_side_length, pixel_side_length);
                    //Draw the big grid which is the size of the square
                    ci::Rectf grid(pixel_top_left, bottom_right_corner);
                    
                    DrawNodes(row, column);
                    
                    //Draw the small pixel grid
                    ci::gl::drawSolidRect(grid);
                    ci::gl::color(ci::Color("white"));
                    
                    ci::gl::drawStrokedRect(grid);
                }
            }
            
            double pixel_side_length = map_size_ / dimension_;
            vec2 pixel_top_left = top_left_corner_ + vec2(current_location_y_ * pixel_side_length,
                                                          current_location_x_ * pixel_side_length);
            vec2 bottom_right = pixel_top_left + vec2(pixel_side_length, pixel_side_length);
            DrawImage(pixel_top_left, bottom_right, kCharacterImage);
        }
        
        void GameMap::DrawNodes(size_t row, size_t column) const {
            //If the node at the pixel is starting node or a walked node
            if (map_model_[row][column] == 1) {
                ci::gl::color(starting_node_.GetNodeColor());

            } else if (map_model_[row][column] == 2) {
                //If the node at the pixel is ending node
                ci::gl::color(ending_node_.GetNodeColor());
            } else if (map_model_[row][column] == 3) {
                //If the node at the pixel is an obstacle node
                ci::gl::color(kObstacleColor);
            } else {
                ci::gl::color(ci::Color("black"));
            }
        }
        
        void GameMap::DrawImage(vec2 top_left, vec2 bottom_right, string path) const {
            ci::gl::TextureRef texture = ci::gl::Texture::create(
                    ci::loadImage(path));
            ci::Rectf object(top_left, bottom_right);
            
            ci::gl::draw(texture, object);
            //map_model_[current_location_x_][current_location_y_];
        }
        
        void GameMap::CreateMapModel() {

            srand(static_cast<unsigned>(time(0)));
            
            size_t random_point_x_coord = rand() % (dimension_);
            size_t random_point_y_coord = rand() % (dimension_);
            //starting_node represented by 1
            map_model_[random_point_x_coord][random_point_y_coord] = 1;
            current_location_x_ = random_point_x_coord;
            current_location_y_ = random_point_y_coord;
            
            random_point_x_coord = rand() % (dimension_);
            random_point_y_coord = rand() % (dimension_);
            if (map_model_[random_point_x_coord][random_point_y_coord] != 1) {
                //ending_node represented by 2
                map_model_[random_point_x_coord][random_point_y_coord] = 2;
            }
            
            while (!obstacle_nodes_.empty()) {
                size_t random_point_x_coord = rand() % (dimension_);
                size_t random_point_y_coord = rand() % (dimension_);
                
                if (map_model_[random_point_x_coord][random_point_y_coord] != 1 &&
                    map_model_[random_point_x_coord][random_point_y_coord] != 2) {
                    //obstacle_node represented by 3
                    obstacle_pixels_.push_back(vec2(random_point_x_coord, random_point_y_coord));
                    map_model_[random_point_x_coord][random_point_y_coord] = 3;
                    obstacle_nodes_.pop_back();
                }
            }
        }
        
        void GameMap::CreateNodes() {
            //Set color to nodes
            starting_node_.SetNodeColor(kStartingNodeColor);
            ending_node_.SetNodeColor(kEndingNodeColor);
            
            for (size_t i = 0; i < kNumOfObstacleNodes; i++) {
                //Create kNumOfObstacleNodes ObstacleNodes and set color to them 
                ObstacleNode new_obstacle(kObstacleColor);
                obstacle_nodes_.push_back(new_obstacle);
            }
        }

        void GameMap::CreateAnimation() {
            //Yet to be implemented
        }
        
        bool GameMap::IsPixelAnObstacle(size_t row, size_t column) {
            //Check if the x and y matches the obstacle pixels
            for (size_t i = 0; i < obstacle_pixels_.size(); i++) {
                if (obstacle_pixels_[i].y == row && obstacle_pixels_[i].x == column) {
                    return true;
                }
            }
            return false;
        }

        void GameMap::UpdateMapPixelColor(size_t row, size_t column) {
            //Change the pixel to a walked pixel
            map_model_[row][column] = 1;
            current_location_y_ = column;
            current_location_x_ = row;
        }

        size_t GameMap::GenerateColorNumber() {
            return rand() % kTotalColorNumbers;
        }

    size_t GameMap::GetCurrentLocationX() const {
        return current_location_x_;
    }

    size_t GameMap::GetCurrentLocationY() const {
        return current_location_y_;
    }

}