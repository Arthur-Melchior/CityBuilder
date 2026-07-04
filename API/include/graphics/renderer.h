//
// Created by Arthur on 07.05.2026.
//

#ifndef CITYBUILDER_RENDERER_H
#define CITYBUILDER_RENDERER_H

#include <SFML/Graphics.hpp>
#include <span>

#include "game.h"
#include "placeables/building.h"
#include "placeables/display_box.h"
#include "placeables/tile.h"
#include "renderer_display_box.h"

namespace citybuilder::graphics {

class Renderer {
 public:
  Renderer(unsigned int width, unsigned int height, const std::string& name,
           const bool hasAntialiasing) {
    sf::ContextSettings settings;
    if (hasAntialiasing) {
      settings.antiAliasingLevel = 8;
    }
    window_ =
        sf::RenderWindow(sf::VideoMode({width, height}), name,
                         sf::Style::Default, sf::State::Windowed, settings);
  }

  void ChangeHologramTexture(Vector2i text_coords);
  void SetHologramVisibility(const bool visible) {
    show_hologram_ = visible;
  }

  void FirstRender(std::span<game::Tile> background,
                   std::span<game::Building> buildings,
                   std::span<game::Resource> resources,
                   std::span<DisplayBox> ui_elements);
  bool Render();

  template <Placeable T>
  std::vector<sf::Vertex> GenerateVertices(std::span<T>);

 private:
  sf::RenderStates states_;

  std::span<game::Tile> bt_;
  std::span<game::Tile> ft_;

  sf::View world_view_;
  sf::View ui_view_;

  // references
  sf::RenderWindow window_;
  sf::Texture tile_sheet_;
  sf::Font font_;

  // tile stuff
  sf::Vector2f texture_size_ = {512, 512};
  float pixel_per_size_unit_ = 32;
  std::vector<sf::Vertex> background_tiles_;
  std::vector<sf::Vertex> foreground_tiles_;
  std::vector<sf::Vertex> villagers;
  std::vector<sf::Vertex> hologram_;
  std::vector<RendererDisplayBox> display_boxes_;
  bool show_hologram_ = false;
  Vector2i hologram_texture_coords_ = {0, 0};

  // mouse stuff
  sf::Vector2<int> previous_mouse_position_ = {0, 0};
  sf::Vector2<int> current_mouse_position_ = {0, 0};

  // zoom stuff
  sf::Vector2f view_port_size_{300, 200};
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