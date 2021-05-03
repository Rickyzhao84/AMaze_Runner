#include <visualizer/game_map.h>

namespace visualizer_app {


    using glm::vec2;
    using std::vector;
    using std::string;

    GameMap::GameMap(const glm::vec2 &top_left_corner, size_t dimension, double map_size) {
        top_left_corner_ = top_left_corner;
        dimension_ = dimension;
        map_model_ = vector<vector<NodeLabel>>(dimension_, vector<NodeLabel>(dimension_, NodeLabel::RegularNode));
        map_size_ = map_size;
    }

    GameMap::GameMap() {}

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
        //Find the direction player is currently heading toward to draw next character image
        FindNextDirection(pixel_side_length);

    }

    void GameMap::MoveMonsters() {
        
        for (size_t i = 0; i < monster_locations_.size(); i++) {
            //Compare monster locations with player location_ and move monster location_ closer to player
            //Only move if the next node is a regular node because monsters are also blocked from obstacles
            
            if (monster_locations_[i].x < location_.GetXCoord() &&
                map_model_[(size_t) monster_locations_[i].x + 1][(size_t) monster_locations_[i].y] ==
                NodeLabel::RegularNode) {
                
                SetNextMonstersLocation(monster_locations_[i].x, monster_locations_[i].y, 
                                        monster_locations_[i].x + 1, monster_locations_[i].y);

                monster_locations_[i].x++;
            } else if (monster_locations_[i].x > location_.GetXCoord() &&
                       map_model_[(size_t) monster_locations_[i].x - 1][(size_t) monster_locations_[i].y] ==
                       NodeLabel::RegularNode) {

                SetNextMonstersLocation(monster_locations_[i].x, monster_locations_[i].y,
                                        monster_locations_[i].x - 1, monster_locations_[i].y);
                
                monster_locations_[i].x--;
            } else if (monster_locations_[i].y > location_.GetYCoord() &&
                       map_model_[(size_t) monster_locations_[i].x][(size_t) monster_locations_[i].y - 1] ==
                       NodeLabel::RegularNode) {

                SetNextMonstersLocation(monster_locations_[i].x, monster_locations_[i].y,
                                        monster_locations_[i].x, monster_locations_[i].y - 1);

                monster_locations_[i].y--;
            } else if (monster_locations_[i].y < location_.GetYCoord() &&
                       map_model_[(size_t) monster_locations_[i].x][(size_t) monster_locations_[i].y + 1] ==
                       NodeLabel::RegularNode) {

                SetNextMonstersLocation(monster_locations_[i].x, monster_locations_[i].y,
                                        monster_locations_[i].x, monster_locations_[i].y + 1);

                monster_locations_[i].y++;
            }
        }
    }

    void GameMap::SetNextMonstersLocation(float prev_x, float prev_y, float next_x, float next_y) {
        map_model_[(size_t)prev_x][(size_t)prev_y] = NodeLabel::RegularNode;
        map_model_[(size_t)next_x][(size_t)next_y] = NodeLabel::MonsterNode;
    }
    
    void GameMap::FindNextDirection(double pixel_side_length) const {
        //Find top left corner of pixel given the top left corner of map
        vec2 pixel_top_left = top_left_corner_ + vec2(location_.GetYCoord() * pixel_side_length,
                                                      location_.GetXCoord() * pixel_side_length);
        
        vec2 bottom_right = pixel_top_left + vec2(pixel_side_length, pixel_side_length);
        if (determine_next_image == NextImage::LookUp) {
            DrawImage(pixel_top_left, bottom_right, kLookUpImage);
        } else if (determine_next_image == NextImage::LookDown) {
            DrawImage(pixel_top_left, bottom_right, kLookDownImage);
        } else if (determine_next_image == NextImage::LookLeft) {
            DrawImage(pixel_top_left, bottom_right, kLookLeftImage);
        } else if (determine_next_image == NextImage::LookRight) {
            DrawImage(pixel_top_left, bottom_right, kLookRightImage);
        }
    }

    NodeLabel GameMap::DrawNodes(size_t row, size_t column) const {
        //If the node at the pixel is starting node or a walked node
        if (map_model_[row][column] == NodeLabel::StartingNode) {
            ci::gl::color(kStartingNodeColor);
            return NodeLabel::StartingNode;
        } else if (map_model_[row][column] == NodeLabel::EndingNode) {
            //If the node at the pixel is ending node
            ci::gl::color(kEndingNodeColor);
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

        map_model_[random_point_x_coord][random_point_y_coord] = NodeLabel::StartingNode;
        location_.SetXCoord(random_point_x_coord);
        location_.SetYCoord(random_point_y_coord);

        CreateEndPoint();

        for (size_t i = 0; i < kNumOfObstacleNodes; i++) {
            size_t random_point_x_coord = rand() % (dimension_);
            size_t random_point_y_coord = rand() % (dimension_);

            if (map_model_[random_point_x_coord][random_point_y_coord] != NodeLabel::StartingNode &&
                map_model_[random_point_x_coord][random_point_y_coord] != NodeLabel::EndingNode) {
                
                obstacle_pixels_.push_back(vec2(random_point_x_coord, random_point_y_coord));
                map_model_[random_point_x_coord][random_point_y_coord] = NodeLabel::ObstacleNode;
            }
        }

        for (size_t i = 0; i < kNumOfMonsterNodes; i++) {
            
            size_t random_point_x_coord = rand() % (dimension_);
            size_t random_point_y_coord = rand() % (dimension_);

            if (map_model_[random_point_x_coord][random_point_y_coord] != NodeLabel::StartingNode &&
                map_model_[random_point_x_coord][random_point_y_coord] != NodeLabel::EndingNode &&
                map_model_[random_point_x_coord][random_point_y_coord] != NodeLabel::ObstacleNode) {

                monster_pixels_.push_back(vec2(random_point_x_coord, random_point_y_coord));
                map_model_[random_point_x_coord][random_point_y_coord] = NodeLabel::MonsterNode;
            }
        }
        
        CreateMonsterLocations();
    }
    
    void GameMap::CreateEndPoint() {
        bool is_end_far_from_start = false;
        while (!is_end_far_from_start) {
            size_t random_point_x_coord = rand() % (dimension_);
            size_t random_point_y_coord = rand() % (dimension_);

            if (map_model_[random_point_x_coord][random_point_y_coord] != NodeLabel::StartingNode &&
                    (std::abs((int) (random_point_x_coord - location_.GetXCoord())) > kDistanceThreshold ||
                     std::abs((int) (random_point_y_coord - location_.GetYCoord())) > kDistanceThreshold)) {
                
                map_model_[random_point_x_coord][random_point_y_coord] = NodeLabel::EndingNode;
                is_end_far_from_start = true;
            }
        }
    }
    
    void GameMap::CreateMonsterLocations() {
        for (size_t i = 0; i < dimension_; i++) {
            for (size_t j = 0; j < dimension_; j++) {
                if (map_model_[i][j] == NodeLabel::MonsterNode) {
                    monster_locations_.push_back(vec2(i, j));
                }
            }
        }
    }

    bool GameMap::IsPixelAnObstacle(size_t row, size_t column) {
        //Check if the x and y matches the obstacle pixels
        for (size_t i = 0; i < obstacle_pixels_.size(); i++) {
            if (obstacle_pixels_[i].y == row && obstacle_pixels_[i].x == column) {
                return true;
            }
        }
        //Check if the x and y matches the monsters pixels
        for (size_t i = 0; i < monster_locations_.size(); i++) {
            if (monster_locations_[i].y == row && monster_locations_[i].x == column) {
                return true;
            }
        }
        return false;
    }
    
    void GameMap::Clear() {
        monster_pixels_.clear();
        obstacle_pixels_.clear();
        monster_locations_.clear();
        map_model_.clear();
    }

    void GameMap::UpdateToNewLocation(size_t row, size_t column, NextImage next_image) {
        //Change the pixel to a walked pixel
        if (map_model_[row][column] != NodeLabel::EndingNode) {
            map_model_[row][column] = NodeLabel::StartingNode;
        }
        location_.SetYCoord(column);
        location_.SetXCoord(row);
        determine_next_image = next_image;
    }

}