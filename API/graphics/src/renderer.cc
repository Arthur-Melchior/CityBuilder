//
// Created by Kalle on 07.05.2026.
//

#include "renderer.h"

#include <position_data.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <concepts>
#include <optional>
#include <vector>

namespace citybuilder::graphics {

void Renderer::FirstRender(std::vector<game::Tile>& background,
                           std::vector<game::Building>& buildings,
                           std::vector<DisplayBox>& ui_elements) {
  if (!tile_sheet_.loadFromFile(
          "_assets/tile_sheets/complete_tile_sheet.png")) {
    return;
  }

  if (!font_.openFromFile("_assets/arial.ttf")) {
    return;
  }

  background_tiles_ = GenerateVertices(background);
  foreground_tiles_ = GenerateVertices(buildings);
  ui_elements_ = GenerateVertices(ui_elements);
  for (auto& ui_element : ui_elements) {
    sf::Text text{font_, ui_element.text, ui_element.font_size};
    const auto size = text.getGlobalBounds().size;
    auto x = ui_element.position_data.position.x ;
    auto y = ui_element.position_data.position.y ;
    text.setPosition({x, y});
    text.setFillColor(sf::Color::Black);
    texts_.emplace_back(text);
  }

  Render();
}

void Renderer::Render() {
  sf::RenderStates states;
  states.texture = &tile_sheet_;
  sf::RenderStates text_states;
  text_states.texture = &font_.getTexture(30);

  sf::View world_view({0, 0}, view_port_size_);
  sf::View ui_view({0, 0}, view_port_size_);

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
        const auto zoom = -mouseWheelScrolled->delta / zoom_interval_;
        current_zoom_ += zoom;
        current_zoom_ = std::clamp(current_zoom_, min_zoom_, max_zoom_);
        const auto size = sf::Vector2f(window_.getSize());
        world_view.setSize(size * current_zoom_);
      }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle)) {
      auto position = sf::Mouse::getPosition(window_);
      current_mouse_position_ = {position.x, position.y};
      auto diff =
          sf::Vector2f(previous_mouse_position_ - current_mouse_position_);
      diff = {diff.x * current_zoom_, diff.y * current_zoom_};
      world_view.move(diff);

      previous_mouse_position_ = current_mouse_position_;
    }

    window_.clear(sf::Color::Black);

    window_.setView(world_view);
    window_.draw(background_tiles_.data(), background_tiles_.size(),
                 sf::PrimitiveType::Triangles, states);
    window_.draw(foreground_tiles_.data(), foreground_tiles_.size(),
                 sf::PrimitiveType::Triangles, states);

    window_.setView(ui_view);
    window_.draw(ui_elements_.data(), ui_elements_.size(),
                 sf::PrimitiveType::Triangles, states);
    for (auto& text : texts_) {
      window_.draw(text);
    }
    window_.display();
  }
}

template <HasPosition T>
std::vector<sf::Vertex> Renderer::GenerateVertices(std::vector<T>& data) {
  std::vector<sf::Vertex> vertex_vector;

  if constexpr (std::same_as<T, DisplayBox>) {
    for (const DisplayBox& display_box : data) {
      const auto tile_position = display_box.position_data.position;
      const auto texture_coords = display_box.position_data.texture_coords;

      const float left = tile_position.x * display_box.size.x;
      const float top = tile_position.y * display_box.size.y;
      const float right = left + display_box.size.x;
      const float bottom = top + display_box.size.y;

      const auto tex_left = texture_coords.x * texture_size_.x;
      const auto tex_right = tex_left + texture_size_.x;
      const auto tex_top = texture_coords.y * texture_size_.y;
      const auto tex_bottom = tex_top + texture_size_.y;

      vertex_vector.push_back(
          sf::Vertex{{left, top}, sf::Color::White, {tex_left, tex_top}});
      vertex_vector.push_back(
          sf::Vertex{{right, top}, sf::Color::White, {tex_right, tex_top}});
      vertex_vector.push_back(sf::Vertex{
          {right, bottom}, sf::Color::White, {tex_right, tex_bottom}});
      vertex_vector.push_back(
          sf::Vertex{{left, top}, sf::Color::White, {tex_left, tex_top}});
      vertex_vector.push_back(
          sf::Vertex{{left, bottom}, sf::Color::White, {tex_left, tex_bottom}});
      vertex_vector.push_back(sf::Vertex{
          {right, bottom}, sf::Color::White, {tex_right, tex_bottom}});
    }
  } else {
    for (const auto& tile : data) {
      const auto tile_position = tile.position_data.position;
      const auto texture_coords = tile.position_data.texture_coords;

      const float left = tile_position.x * tile_size_.x;
      const float top = tile_position.y * tile_size_.y;
      const float right = left + tile_size_.x;
      const float bottom = top + tile_size_.y;

      const auto tex_left = texture_coords.x * texture_size_.x;
      const auto tex_right = tex_left + texture_size_.x;
      const auto tex_top = texture_coords.y * texture_size_.y;
      const auto tex_bottom = tex_top + texture_size_.y;

      vertex_vector.push_back(
          sf::Vertex{{left, top}, sf::Color::White, {tex_left, tex_top}});
      vertex_vector.push_back(
          sf::Vertex{{right, top}, sf::Color::White, {tex_right, tex_top}});
      vertex_vector.push_back(sf::Vertex{
          {right, bottom}, sf::Color::White, {tex_right, tex_bottom}});
      vertex_vector.push_back(
          sf::Vertex{{left, top}, sf::Color::White, {tex_left, tex_top}});
      vertex_vector.push_back(
          sf::Vertex{{left, bottom}, sf::Color::White, {tex_left, tex_bottom}});
      vertex_vector.push_back(sf::Vertex{
          {right, bottom}, sf::Color::White, {tex_right, tex_bottom}});
    }
  }

  return vertex_vector;
}

}  // namespace citybuilder::graphics