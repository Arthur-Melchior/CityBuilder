//
// Created by Kalle on 07.05.2026.
//

#ifndef CITYBUILDER_RENDERER_H
#define CITYBUILDER_RENDERER_H

#include <tile.h>

#include <SFML/Graphics.hpp>

namespace citybuilder::graphics {

class Renderer {
 public:
  Renderer(unsigned int width, unsigned int height, const std::string& name)
      : window_(sf::VideoMode ({width, height}), name) {}

  void FirstRender(const std::vector<game::Tile>& tiles);
  void Render();

 private:
  //references
  sf::RenderWindow window_;
  sf::Texture background_texture_;

  //tile stuff
  float tile_size_ = 32;
  float texture_size_ = 512;
  std::vector<sf::Vertex> background_tiles_;

  //mouse stuff
  sf::Vector2<int> previous_mouse_position_ = {0,0};
  sf::Vector2<int> current_mouse_position_ = {0,0};

  //zoom stuff
  float current_zoom_ = 1;
  float zoom_interval_ = 10;
  float min_zoom_ = 0.3f;
  float max_zoom_ = 3.f;
};

// open window
// poll events / handle events
// divide visuals into vertex arrays

}  // namespace citybuilder::graphics

#endif  // CITYBUILDER_RENDERER_H