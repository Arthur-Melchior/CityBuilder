//
// Created by Kalle on 07.05.2026.
//

#include "renderer.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <optional>
#include <vector>

namespace citybuilder::graphics {

void Renderer::FirstRender(const std::vector<game::Tile>& tiles) {
  if (!background_texture_.loadFromFile("_assets/tile_sheets/background.png")) {
    return;
  }

  background_tiles_.clear();

  for (auto tile : tiles) {
    const auto tile_position = tile.GetPosition();
    const auto texture_coords = tile.GetTextureCoords();

    const float x = static_cast<float>(tile_position[0]) * tile_size_;
    const float y = static_cast<float>(tile_position[1]) * tile_size_;

    const auto tex_x_1 = static_cast<float>(texture_coords[0]) * texture_size_;
    const auto tex_x_2 = (texture_coords[0] + 1) * texture_size_;
    const auto tex_y_1 = static_cast<float>(texture_coords[1]) * texture_size_;
    const auto tex_y_2 = (texture_coords[1] + 1) * texture_size_;


    background_tiles_.push_back(
        sf::Vertex{{x, y}, sf::Color::White, {tex_x_1, tex_y_1}});
    background_tiles_.push_back(
        sf::Vertex{{x + tile_size_, y}, sf::Color::White, {tex_x_2, tex_y_1}});
    background_tiles_.push_back(sf::Vertex{
        {x + tile_size_, y + tile_size_}, sf::Color::White, {tex_x_2, tex_y_2}});
    background_tiles_.push_back(
        sf::Vertex{{x, y}, sf::Color::White, {tex_x_1, tex_y_1}});
    background_tiles_.push_back(
        sf::Vertex{{x, y + tile_size_}, sf::Color::White, {tex_x_1, tex_y_2}});
    background_tiles_.push_back(sf::Vertex{
        {x + tile_size_, y + tile_size_}, sf::Color::White, {tex_x_2, tex_y_2}});
  }

  Render();
}
void Renderer::Render() {
  sf::RenderStates states;
  sf::View view({32 * 200.f, 32 * 200.f}, {300.f, 200.f});
  states.texture = &background_texture_;

  while (window_.isOpen()) {
    while (const std::optional event = window_.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window_.close();
      }

      // to stop the view from snapping between two drags
      if (const auto* mouseButtonPressed =
              event->getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseButtonPressed->button == sf::Mouse::Button::Middle) {
          previous_mouse_position_ = sf::Mouse::getPosition(window_);
        }
      }

      // to zoom on mouse wheel
      if (const auto* mouseWheelScrolled =
              event->getIf<sf::Event::MouseWheelScrolled>()) {
        const auto zoom = mouseWheelScrolled->delta / zoom_interval_;
        current_zoom_ += zoom;

        if (current_zoom_ >= min_zoom_ && current_zoom_ <= max_zoom_) {
          view.zoom(1 + zoom);
        }

        current_zoom_ = std::clamp(current_zoom_, min_zoom_, max_zoom_);
      }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle)) {
      auto position = sf::Mouse::getPosition(window_);
      current_mouse_position_ = {position.x, position.y};
      auto diff =
          sf::Vector2f(previous_mouse_position_ - current_mouse_position_);
      diff = {diff.x * current_zoom_, diff.y * current_zoom_};
      view.move(diff);

      previous_mouse_position_ = current_mouse_position_;
    }

    window_.setView(view);
    window_.clear(sf::Color::Black);
    window_.draw(background_tiles_.data(), background_tiles_.size(),
                 sf::PrimitiveType::Triangles, states);
    window_.display();
  }
}

}  // namespace citybuilder::graphics