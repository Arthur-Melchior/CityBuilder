//
// Created by Kalle on 07.05.2026.
//

#include "renderer.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
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

  Render();
}

void Renderer::Render() {
  sf::RenderStates states;
  states.texture = &tile_sheet_;
  sf::RenderStates text_states;
  text_states.texture = &font_.getTexture(30);

  sf::View view({tile_size_.x * 100.f, tile_size_.y * 100.f}, {300.f, 200.f});

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
        view.setSize(size * current_zoom_);
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
    window_.draw(foreground_tiles_.data(), foreground_tiles_.size(),
                 sf::PrimitiveType::Triangles, states);
    window_.draw(ui_elements_.data(), ui_elements_.size(),
                 sf::PrimitiveType::Triangles, text_states);
    window_.draw(texts_.data(), texts_.size(), sf::PrimitiveType::Triangles,
                 text_states);
    window_.display();
  }
}

template <HasPosition T>
std::vector<sf::Vertex> Renderer::GenerateVertices(std::vector<T>& data) {
  std::vector<sf::Vertex> vertex_vector;

  if constexpr (std::same_as<T, DisplayBox>) {
    for (DisplayBox& display_box : data) {
      auto x = static_cast<float>(display_box.position_data.position[0]);
      const auto y = static_cast<float>(display_box.position_data.position[1]);

      for (const auto letter : display_box.text) {
        const sf::Glyph& glyph =
            font_.getGlyph(letter, display_box.font_size, false);

        const float left = x + glyph.bounds.position.x;
        const float top = y + glyph.bounds.position.y;
        float right = left + glyph.bounds.size.x;
        float bottom = top + glyph.bounds.size.y;

        auto tex_left = static_cast<float>(glyph.textureRect.position.x);
        auto tex_top = static_cast<float>(glyph.textureRect.position.y);
        float tex_right = tex_left + static_cast<float>(glyph.textureRect.size.x);
        float tex_bottom = tex_top + static_cast<float>(glyph.textureRect.size.y);

        vertex_vector.push_back(
            sf::Vertex({left, top}, sf::Color::White, {tex_left, tex_top}));
        vertex_vector.push_back(
            sf::Vertex({right, top}, sf::Color::White, {tex_right, tex_top}));
        vertex_vector.push_back(sf::Vertex({right, bottom}, sf::Color::White,
                                           {tex_right, tex_bottom}));
        vertex_vector.push_back(
            sf::Vertex({left, top}, sf::Color::White, {tex_left, tex_top}));
        vertex_vector.push_back(sf::Vertex({right, bottom}, sf::Color::White,
                                           {tex_right, tex_bottom}));
        vertex_vector.push_back(sf::Vertex({left, bottom}, sf::Color::White,
                                           {tex_left, tex_bottom}));

        x += glyph.advance;
      }
    }
  } else {
    for (const auto& tile : data) {
      const auto tile_position = tile.position_data.position;
      const auto texture_coords = tile.position_data.texture_coords;

      const float left = static_cast<float>(tile_position[0]) * tile_size_.x;
      const float top = static_cast<float>(tile_position[1]) * tile_size_.y;
      const float right = left + tile_size_.x;
      const float bottom = top + tile_size_.y;

      const auto tex_left =
          static_cast<float>(texture_coords[0]) * texture_size_.x;
      const auto tex_right = tex_left + texture_size_.x;
      const auto tex_top =
          static_cast<float>(texture_coords[1]) * texture_size_.y;
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