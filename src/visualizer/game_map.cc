#include <visualizer/game_map.h>

namespace visualizer_app {
    

        using glm::vec2;
        using std::vector;
        using std::string;

        GameMap::GameMap(const glm::vec2 &top_left_corner, size_t dimension, double map_size)
                : starting_node_(cinder::Color()), ending_node_(cinder::Color()) {
            top_left_corner_ = top_left_corner;
            dimension_ = dimension;
            map_model_ = vector<vector<NodeLabel>>(dimension_, vector<NodeLabel>(dimension_, NodeLabel::RegularNode));
            map_size_ = map_size;
        }

        void GameMap::Draw() const {
            double pixel_side_length = map_size_ / dimension_;
            for (size_t row = 0; row < dimension_; row++) {
                for (size_t column = 0; column < dimension_; column++) {
                    
                    //Find the top left of pixel map from top left of window
                    vec2 pixel_top_left = top_left_corner_ + vec2(column * pixel_side_length,
                                                                  row * pixel_side_length);
                    
                    vec2 bottom_right_corner = pixel_top_left + vec2(pixel_side_length, pixel_side_length);
                    //Draw the big grid which is the size of the square
                    ci::Rectf grid(pixel_top_left, bottom_right_corner);
                    
                    NodeLabel label = DrawNodes(row, column);
                    
                    //Draw the small pixel grid
                    ci::gl::drawSolidRect(grid);
                    ci::gl::color(ci::Color("white"));
                    
                    ci::gl::drawStrokedRect(grid);
                    if (label == NodeLabel::MonsterNode) {
                        DrawImage(pixel_top_left, bottom_right_corner, kMonsterImage);
                    }
                }
            }
            FindNextDirection(pixel_side_length);
            
        }
        //Method check using for loops row[i] < row[j] same for column
        //for every mike given location update mikes location to next location given what it currently is
        //Comparing x and y coords and put mike 
        
        void GameMap::MoveMonsters() {
            for (size_t i = 0; i < dimension_; i++) {
                for (size_t j = 0; j < dimension_; j++) {
                    if (map_model_[i][j] == NodeLabel::MonsterNode) {
                        monster_locations_.push_back(vec2(i,j));
                    }
                }
            }
            for (vec2 location: monster_locations_) {
                if (location.x < current_location_x_ &&
                    map_model_[(size_t)location.x + 1][(size_t)location.y] == NodeLabel::RegularNode) {
                    map_model_[(size_t)location.x][(size_t)location.y] = NodeLabel::RegularNode;
                    map_model_[(size_t)location.x + 1][(size_t)location.y] = NodeLabel::MonsterNode;
                    location.x++;
                } else if (location.x > current_location_x_ &&
                    map_model_[(size_t)location.x - 1][(size_t)location.y] == NodeLabel::RegularNode) {
                    map_model_[(size_t)location.x][(size_t)location.y] = NodeLabel::RegularNode;
                    map_model_[(size_t)location.x - 1][(size_t)location.y] = NodeLabel::MonsterNode;
                    location.x--;
                } else if (location.y > current_location_y_ &&
                    map_model_[(size_t)location.x][(size_t)location.y - 1] == NodeLabel::RegularNode) {
                    map_model_[(size_t)location.x][(size_t)location.y] = NodeLabel::RegularNode;
                    map_model_[(size_t)location.x][(size_t)location.y - 1] = NodeLabel::MonsterNode;
                    location.y--;
                } else if (location.y < current_location_x_ &&
                    map_model_[(size_t)location.x][(size_t)location.y + 1] == NodeLabel::RegularNode) {
                    map_model_[(size_t)location.x][(size_t)location.y] = NodeLabel::RegularNode;
                    map_model_[(size_t)location.x][(size_t)location.y + 1] = NodeLabel::MonsterNode;
                    location.y++;
                }
            }
        }
        
        void GameMap::FindNextDirection(double pixel_side_length) const {
            vec2 pixel_top_left = top_left_corner_ + vec2(current_location_y_ * pixel_side_length,
                                                          current_location_x_ * pixel_side_length);
            vec2 bottom_right = pixel_top_left + vec2(pixel_side_length, pixel_side_length);
            if (determine_next_image == 1) {
                DrawImage(pixel_top_left, bottom_right, kLookUpImage);
            } else if (determine_next_image == 2) {
                DrawImage(pixel_top_left, bottom_right, kLookDownImage);
            } else if (determine_next_image == 3) {
                DrawImage(pixel_top_left, bottom_right, kLookLeftImage);
            } else if (determine_next_image == 4) {
                DrawImage(pixel_top_left, bottom_right, kLookRightImage);
            }
        }
        
        NodeLabel GameMap::DrawNodes(size_t row, size_t column) const {
            //If the node at the pixel is starting node or a walked node
            if (map_model_[row][column] == NodeLabel::StartingNode) {
                ci::gl::color(starting_node_.GetNodeColor());
                return NodeLabel::StartingNode;
            } else if (map_model_[row][column] == NodeLabel::EndingNode) {
                //If the node at the pixel is ending node
                ci::gl::color(ending_node_.GetNodeColor());
                return NodeLabel::EndingNode;
            } else if (map_model_[row][column] == NodeLabel::ObstacleNode) {
                //If the node at the pixel is an obstacle node
                ci::gl::color(kObstacleColor);
                return NodeLabel::ObstacleNode;
            } else if (map_model_[row][column] == NodeLabel::MonsterNode) {
                ci::gl::color(ci::Color("black"));
                return NodeLabel::MonsterNode;
            } else {
                ci::gl::color(ci::Color("black"));
                return NodeLabel::RegularNode;
            }
        }
        
        void GameMap::DrawImage(vec2 top_left, vec2 bottom_right, string path) const {
            ci::gl::TextureRef texture = ci::gl::Texture::create(
                    ci::loadImage(path));
            ci::Rectf object(top_left, bottom_right);
            
            ci::gl::draw(texture, object);
        }
        
        void GameMap::CreateMapModel() {

            srand(static_cast<unsigned>(time(0)));
            
            size_t random_point_x_coord = rand() % (dimension_);
            size_t random_point_y_coord = rand() % (dimension_);
            //starting_node represented by 1
            map_model_[random_point_x_coord][random_point_y_coord] = NodeLabel::StartingNode;
            current_location_x_ = random_point_x_coord;
            current_location_y_ = random_point_y_coord;
            
            random_point_x_coord = rand() % (dimension_);
            random_point_y_coord = rand() % (dimension_);
            if (map_model_[random_point_x_coord][random_point_y_coord] != NodeLabel::StartingNode) {
                //ending_node represented by 2
                map_model_[random_point_x_coord][random_point_y_coord] = NodeLabel::EndingNode;
            }
            
            while (!obstacle_nodes_.empty()) {
                size_t random_point_x_coord = rand() % (dimension_);
                size_t random_point_y_coord = rand() % (dimension_);
                
                if (map_model_[random_point_x_coord][random_point_y_coord] != NodeLabel::StartingNode &&
                    map_model_[random_point_x_coord][random_point_y_coord] != NodeLabel::EndingNode) {
                    //obstacle_node represented by 3
                    obstacle_pixels_.push_back(vec2(random_point_x_coord, random_point_y_coord));
                    map_model_[random_point_x_coord][random_point_y_coord] = NodeLabel::ObstacleNode;
                    obstacle_nodes_.pop_back();
                }
            }

            while (!monster_nodes_.empty()) {
                size_t random_point_x_coord = rand() % (dimension_);
                size_t random_point_y_coord = rand() % (dimension_);

                if (map_model_[random_point_x_coord][random_point_y_coord] != NodeLabel::StartingNode &&
                    map_model_[random_point_x_coord][random_point_y_coord] != NodeLabel::EndingNode &&
                    map_model_[random_point_x_coord][random_point_y_coord] != NodeLabel::ObstacleNode) {
                    
                    monster_pixels_.push_back(vec2(random_point_x_coord, random_point_y_coord));
                    map_model_[random_point_x_coord][random_point_y_coord] = NodeLabel::MonsterNode;
                    monster_nodes_.pop_back();
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
            
            for (size_t i = 0; i < kNumOfMonsterNodes; i++) {
                MonsterNode new_monster(KRegularNodeColor);
                monster_nodes_.push_back(new_monster);
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

        void GameMap::UpdateMapPixelColor(size_t row, size_t column, size_t next_image) {
            //Change the pixel to a walked pixel
            map_model_[row][column] = NodeLabel::StartingNode;
            current_location_y_ = column;
            current_location_x_ = row;
            determine_next_image = next_image;
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