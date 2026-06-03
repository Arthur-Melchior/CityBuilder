//
// Created by Arthur on 07.05.2026.
//

#ifndef CITYBUILDER_RENDERER_H
#define CITYBUILDER_RENDERER_H

#include <building.h>
#include <tile.h>

#include <SFML/Graphics.hpp>
#include <span>

#include "display_box.h"
#include "game.h"
#include "renderer_display_box.h"

namespace citybuilder::graphics {

class Renderer {
 public:
  Renderer(unsigned int width, unsigned int height, const std::string& name)
      : window_(sf::VideoMode({width, height}), name) {}

  void FirstRender(std::span<game::Tile> background,
                   std::span<game::Building> buildings,
                   std::span<DisplayBox> ui_elements);
  void Render();

  template <Placeable T>
  std::vector<sf::Vertex> GenerateVertices(std::span<T>);

 private:
  // references
  sf::RenderWindow window_;
  sf::Texture tile_sheet_;
  sf::Font font_;

  // tile stuff
  sf::Vector2f tile_size_ = {32, 32};
  sf::Vector2f texture_size_ = {512, 512};
  std::vector<sf::Vertex> background_tiles_;
  std::vector<sf::Vertex> foreground_tiles_;
  std::vector<RendererDisplayBox> display_boxes_;

  // mouse stuff
  sf::Vector2<int> previous_mouse_position_ = {0, 0};
  sf::Vector2<int> current_mouse_position_ = {0, 0};

  // zoom stuff
  sf::Vector2f view_port_size_{300,200};
  float current_zoom_ = 1;
  float zoom_interval_ = 10;
  float min_zoom_ = 0.3f;
  float max_zoom_ = 5.f;
};

// open window
// poll events / handle events
// divide visuals into vertex arrays

}  // namespace citybuilder::graphics

#endif  // CITYBUILDER_RENDERER_H