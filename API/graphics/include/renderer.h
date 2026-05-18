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
  sf::RenderWindow window_;
  sf::Texture background_texture_;
  std::vector<sf::Vertex> background_tiles_;
  float tile_size_ = 32;
};

// open window
// poll events / handle events
// divide visuals into vertex arrays

}  // namespace citybuilder::graphics

#endif  // CITYBUILDER_RENDERER_H