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
                           const std::span<game::Resource> resources,
                           const std::span<DisplayBox> ui_elements) {
  if (!tile_sheet_.loadFromFile(
          "_assets/tile_sheets/complete_tile_sheet.png")) {
    return;
  }

  tile_sheet_.setSmooth(false);

  if (!font_.openFromFile("_assets/arial.ttf")) {
    return;
  }

  hologram_.push_back(sf::Vertex{
      {0, 0}, {sf::Color::White}, {8 * texture_size_.x, 10 * texture_size_.y}});
  hologram_.push_back(sf::Vertex{{1000, 0},
                                 {sf::Color::White},
                                 {9 * texture_size_.x, 10 * texture_size_.y}});
  hologram_.push_back(sf::Vertex{{1000, 1000},
                                 {sf::Color::White},
                                 {9 * texture_size_.x, 11 * texture_size_.y}});
  hologram_.push_back(sf::Vertex{
      {0, 0}, {sf::Color::White}, {8 * texture_size_.x, 10 * texture_size_.y}});
  hologram_.push_back(sf::Vertex{{0, 1000},
                                 {sf::Color::White},
                                 {8 * texture_size_.x, 11 * texture_size_.y}});
  hologram_.push_back(sf::Vertex{{1000, 1000},
                                 {sf::Color::White},
                                 {9 * texture_size_.x, 11 * texture_size_.y}});

  bt_ = background;
  re_ = resources;

  background_tiles_ = GenerateVertices(background);
  foreground_tiles_ = GenerateVertices(buildings);
  resources_ = GenerateVertices(resources);
  for (auto& ui_element : ui_elements) {
    const float left = ui_element.position.x;
    const float top = ui_element.position.y;
    const float right = left + ui_element.size.x;
    const float bottom = top + ui_element.size.y;

    const auto tex_left = ui_element.texture_coords.x * texture_size_.x + 0.5f;
    const auto tex_right = tex_left + texture_size_.x - 1.0f;
    const auto tex_top = ui_element.texture_coords.y * texture_size_.y + 0.5f;
    const auto tex_bottom = tex_top + texture_size_.y - 1.0f;

    const sf::Vertex top_left_vertex{
        {left, top}, sf::Color::White, {tex_left, tex_top}};
    const sf::Vertex top_right_vertex{
        {right, top}, sf::Color::White, {tex_right, tex_top}};
    const sf::Vertex bottom_right_vertex{
        {right, bottom}, sf::Color::White, {tex_right, tex_bottom}};
    const sf::Vertex bottom_left_vertex{
        {left, bottom}, sf::Color::White, {tex_left, tex_bottom}};

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
    const Vector2f pos = {static_cast<float>(ui_element.position.x),
                          static_cast<float>(ui_element.position.y)};
    const Vector2f size = {static_cast<float>(ui_element.size.x),
                           static_cast<float>(ui_element.size.y)};
    RendererDisplayBox rdb{pos,
                           size,
                           ui_element.texture_coords,
                           text,
                           ui_element.is_button,
                           ui_element.action};
    rdb.vertices.push_back(top_left_vertex);
    rdb.vertices.push_back(top_right_vertex);
    rdb.vertices.push_back(bottom_right_vertex);
    rdb.vertices.push_back(top_left_vertex);
    rdb.vertices.push_back(bottom_left_vertex);
    rdb.vertices.push_back(bottom_right_vertex);
    display_boxes_.push_back(rdb);
  }

  states_.texture = &tile_sheet_;
  world_view_ = sf::View({1500, 1500}, view_port_size_);
  ui_view_ =
      sf::View(sf::FloatRect{{0.f, 0.f}, sf::Vector2f(window_.getSize())});
}

bool Renderer::Render() {
  bool left_mouse_pressed = false;

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

      if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
        left_mouse_pressed = true;
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

  const auto mouse_pixel_pos = sf::Mouse::getPosition(window_);
  const auto mouse_world_pos =
      window_.mapPixelToCoords(mouse_pixel_pos, world_view_);

  const int tile_x =
      static_cast<int>(std::floor(mouse_world_pos.x / pixel_per_size_unit_));
  const int tile_y =
      static_cast<int>(std::floor(mouse_world_pos.y / pixel_per_size_unit_));

  const float snapped_x = tile_x * pixel_per_size_unit_;
  const float snapped_y = tile_y * pixel_per_size_unit_;
  const float tile_size = pixel_per_size_unit_;

  hologram_[0].position = {snapped_x, snapped_y};
  hologram_[1].position = {snapped_x + tile_size, snapped_y};
  hologram_[2].position = {snapped_x + tile_size, snapped_y + tile_size};
  hologram_[3].position = {snapped_x, snapped_y};
  hologram_[4].position = {snapped_x, snapped_y + tile_size};
  hologram_[5].position = {snapped_x + tile_size, snapped_y + tile_size};

  bool is_walkable = false;
  game::Tile* selected_tile = nullptr;

  for (auto& tile : bt_) {
    if (tile.position.x == tile_x && tile.position.y == tile_y) {
      selected_tile = &tile;
      is_walkable = tile.is_walkable;
      break;
    }
  }

  const sf::Color hologram_color =
      is_walkable ? sf::Color{0, 255, 0, 180} : sf::Color{255, 0, 0, 180};

  for (auto& vertex : hologram_) {
    vertex.color = hologram_color;
  }

  if (show_hologram_ && left_mouse_pressed && is_walkable &&
      selected_tile != nullptr) {
    game::Building building{
        {tile_x, tile_y}, hologram_texture_coords_, {1, 1}, hologram_type_};

    auto building_vertices = GenerateVertices(std::span{&building, 1});
    foreground_tiles_.insert(foreground_tiles_.end(), building_vertices.begin(),
                             building_vertices.end());

    selected_tile->is_walkable = false;
  }

  villagers = GenerateVertices(std::span{*NPCManager::GetVillagers()});
  resources_ = GenerateVertices(re_);

  window_.clear(sf::Color::Black);

  window_.setView(world_view_);
  window_.draw(background_tiles_.data(), background_tiles_.size(),
               sf::PrimitiveType::Triangles, states_);
  window_.draw(foreground_tiles_.data(), foreground_tiles_.size(),
               sf::PrimitiveType::Triangles, states_);
  window_.draw(resources_.data(), resources_.size(),
               sf::PrimitiveType::Triangles, states_);
  window_.draw(villagers.data(), villagers.size(), sf::PrimitiveType::Triangles,
               states_);
  if (show_hologram_) {
    window_.draw(hologram_.data(), hologram_.size(),
                 sf::PrimitiveType::Triangles, states_);
  }

  window_.setView(ui_view_);

  for (auto& display_box : display_boxes_) {
    window_.draw(display_box.vertices.data(), display_box.vertices.size(),
                 sf::PrimitiveType::Triangles, states_);
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

void Renderer::ChangeHologramTexture(const Vector2i text_coords) {
  const float tex_pos_x =
      static_cast<float>(text_coords.x) * texture_size_.x - 1.f;
  const float tex_pos_y =
      static_cast<float>(text_coords.y) * texture_size_.y - 1.f;

  hologram_[0].texCoords.x = tex_pos_x;
  hologram_[0].texCoords.y = tex_pos_y;
  hologram_[1].texCoords.x = tex_pos_x + texture_size_.x;
  hologram_[1].texCoords.y = tex_pos_y;
  hologram_[2].texCoords.x = tex_pos_x + texture_size_.x;
  hologram_[2].texCoords.y = tex_pos_y + texture_size_.y;
  hologram_[3].texCoords.x = tex_pos_x;
  hologram_[3].texCoords.y = tex_pos_y;
  hologram_[4].texCoords.x = tex_pos_x;
  hologram_[4].texCoords.y = tex_pos_y + texture_size_.y;
  hologram_[5].texCoords.x = tex_pos_x + texture_size_.x;
  hologram_[5].texCoords.y = tex_pos_y + texture_size_.y;
  hologram_texture_coords_ = text_coords;
}

}  // namespace citybuilder::graphics