//
// Created by Kalle on 07.05.2026.
//

#include "../../include/graphics/renderer.h"

#include <placeables/placeable.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <optional>
#include <vector>

#include "../../include/graphics/renderer_display_box.h"

namespace citybuilder::graphics {

void Renderer::FirstRender(const std::span<game::Tile> background,
                           const std::span<game::Building> buildings,
                           std::span<DisplayBox> ui_elements) {
  if (!tile_sheet_.loadFromFile(
          "_assets/tile_sheets/complete_tile_sheet.png")) {
    return;
  }

  tile_sheet_.setSmooth(false);

  if (!font_.openFromFile("_assets/arial.ttf")) {
    return;
  }

  bt_ = background;

  background_tiles_ = GenerateVertices(background);
  foreground_tiles_ = GenerateVertices(buildings);
  for (auto& ui_element : ui_elements) {
    sf::RectangleShape shape{{static_cast<float>(ui_element.size.x),
                              static_cast<float>(ui_element.size.y)}};
    shape.setPosition(
        sf::Vector2f(ui_element.position.x, ui_element.position.y));
    shape.setFillColor(sf::Color::White);

    sf::Text text{font_, ui_element.text, ui_element.font_size};

    const auto text_bounds = text.getLocalBounds();
    text.setOrigin({
        text_bounds.position.x + text_bounds.size.x / 2.f,
        text_bounds.position.y + text_bounds.size.y / 2.f,
    });
    text.setPosition({
        ui_element.position.x + ui_element.size.x / 2.f,
        ui_element.position.y + ui_element.size.y / 2.f,
    });

    text.setFillColor(sf::Color::Black);
    display_boxes_.emplace_back(shape, text, ui_element.is_button);
  }

  states_.texture = &tile_sheet_;
  world_view_ = sf::View({0, 0}, view_port_size_);
  ui_view_ = sf::View(
      sf::FloatRect{{0.f, 0.f}, sf::Vector2f(window_.getSize())});
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

    for (auto& display_box : display_boxes_) {
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

  background_tiles_ = GenerateVertices(bt_);

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
std::vector<sf::Vertex> Renderer::GenerateVertices(std::span<T> placeables) {
  std::vector<sf::Vertex> vertex_vector;

  for (const auto& obj : placeables) {
    const auto obj_position = obj.position;
    const auto texture_coords = obj.texture_coords;

    const float left = obj_position.x * obj.size.x * pixel_per_size_unit_;
    const float top = obj_position.y * obj.size.y * pixel_per_size_unit_;
    const float right = left + obj.size.x * pixel_per_size_unit_;
    const float bottom = top + obj.size.y * pixel_per_size_unit_;

    const auto tex_left = texture_coords.x * texture_size_.x + 0.5f;
    const auto tex_right = tex_left + texture_size_.x - 1.0f;
    const auto tex_top = texture_coords.y * texture_size_.y + 0.5f;
    const auto tex_bottom = tex_top + texture_size_.y - 1.0f;

    const sf::Vertex top_left_vertex{
        {left, top}, sf::Color::White, {tex_left, tex_top}};
    const sf::Vertex top_right_vertex{
        {right, top}, sf::Color::White, {tex_right, tex_top}};
    const sf::Vertex bottom_right_vertex{
        {right, bottom}, sf::Color::White, {tex_right, tex_bottom}};
    const sf::Vertex bottom_left_vertex{
        {left, bottom}, sf::Color::White, {tex_left, tex_bottom}};

    vertex_vector.push_back(top_left_vertex);
    vertex_vector.push_back(top_right_vertex);
    vertex_vector.push_back(bottom_right_vertex);
    vertex_vector.push_back(top_left_vertex);
    vertex_vector.push_back(bottom_left_vertex);
    vertex_vector.push_back(bottom_right_vertex);
  }

  return vertex_vector;
}

}  // namespace citybuilder::graphics