//
// Created by Kalle on 07.05.2026.
//

#include "renderer.h"

#include <placeable.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <concepts>
#include <optional>
#include <vector>

#include "renderer_display_box.h"

namespace citybuilder::graphics {

void Renderer::FirstRender(const std::span<game::Tile> background,
                           const std::span<game::Building> buildings,
                           std::span<DisplayBox> ui_elements) {
  if (!tile_sheet_.loadFromFile(
          "_assets/tile_sheets/complete_tile_sheet.png")) {
    return;
  }

  if (!font_.openFromFile("_assets/arial.ttf")) {
    return;
  }

  background_tiles_ = GenerateVertices(background);
  foreground_tiles_ = GenerateVertices(buildings);
  for (auto& ui_element : ui_elements) {
    sf::RectangleShape shape{{ui_element.size.x, ui_element.size.y}};
    shape.setPosition(
        sf::Vector2f(ui_element.position.x, ui_element.position.y));
    shape.setFillColor(sf::Color::White);

    sf::Text text{font_, ui_element.text, ui_element.font_size};
    text.setPosition(
        sf::Vector2f(ui_element.position.x, ui_element.position.y));
    text.setFillColor(sf::Color::Black);
    display_boxes_.emplace_back(shape, text);
  }

  states_.texture = &tile_sheet_;
  world_view_ = sf::View({0, 0}, view_port_size_);
  ui_view_ = sf::View({0, 0}, view_port_size_);
}

bool Renderer::Render() {


  while (const std::optional event = window_.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      return false;
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
      const auto zoom = -mouseWheelScrolled->delta / zoom_interval_;
      current_zoom_ += zoom;
      current_zoom_ = std::clamp(current_zoom_, min_zoom_, max_zoom_);
      const auto size = sf::Vector2f(window_.getSize());
      world_view_.setSize(size * current_zoom_);
    }

    for (auto display_box : display_boxes_) {
      display_box.HandleEvents(event, window_, ui_view_);
    }
  }

  // to move the map on middle mouse drag
  if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle)) {
    auto position = sf::Mouse::getPosition(window_);
    current_mouse_position_ = {position.x, position.y};
    const auto diff =
        sf::Vector2f(previous_mouse_position_ - current_mouse_position_) *
        current_zoom_;
    world_view_.move(diff);

    previous_mouse_position_ = current_mouse_position_;
  }

  window_.clear(sf::Color::Black);

  window_.setView(world_view_);
  window_.draw(background_tiles_.data(), background_tiles_.size(),
               sf::PrimitiveType::Triangles, states_);
  window_.draw(foreground_tiles_.data(), foreground_tiles_.size(),
               sf::PrimitiveType::Triangles, states_);

  window_.setView(ui_view_);

  for (auto& display_box : display_boxes_) {
    window_.draw(display_box.shape);
    window_.draw(display_box.text);
  }

  window_.display();
  return true;
}

template <Placeable T>
std::vector<sf::Vertex> Renderer::GenerateVertices(std::span<T> data) {
  std::vector<sf::Vertex> vertex_vector;

  for (const auto& tile : data) {
    const auto tile_position = tile.position;
    const auto texture_coords = tile.texture_coords;

    const float left = tile_position.x * tile.size.x;
    const float top = tile_position.y * tile.size.y;
    const float right = left + tile.size.x;
    const float bottom = top + tile.size.y;

    const auto tex_left = texture_coords.x * texture_size_.x;
    const auto tex_right = tex_left + texture_size_.x;
    const auto tex_top = texture_coords.y * texture_size_.y;
    const auto tex_bottom = tex_top + texture_size_.y;

    vertex_vector.push_back(
        sf::Vertex{{left, top}, sf::Color::White, {tex_left, tex_top}});
    vertex_vector.push_back(
        sf::Vertex{{right, top}, sf::Color::White, {tex_right, tex_top}});
    vertex_vector.push_back(
        sf::Vertex{{right, bottom}, sf::Color::White, {tex_right, tex_bottom}});
    vertex_vector.push_back(
        sf::Vertex{{left, top}, sf::Color::White, {tex_left, tex_top}});
    vertex_vector.push_back(
        sf::Vertex{{left, bottom}, sf::Color::White, {tex_left, tex_bottom}});
    vertex_vector.push_back(
        sf::Vertex{{right, bottom}, sf::Color::White, {tex_right, tex_bottom}});
  }

  return vertex_vector;
}

}  // namespace citybuilder::graphics