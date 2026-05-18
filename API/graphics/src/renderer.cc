//
// Created by Kalle on 07.05.2026.
//

#include "renderer.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
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

    constexpr float tile_size = 512.0f;

    const float x = static_cast<float>(tile_position[0]) * tile_size;
    const float y = static_cast<float>(tile_position[1]) * tile_size;

    const auto tex_x = static_cast<float>(texture_coords[0]);
    const auto tex_y = static_cast<float>(texture_coords[1]);

    background_tiles_.push_back(
        sf::Vertex{{x, y}, sf::Color::White, {tex_x, tex_y}});

    background_tiles_.push_back(sf::Vertex{
        {x + tile_size, y}, sf::Color::White, {tex_x + tile_size, tex_y}});

    background_tiles_.push_back(sf::Vertex{
        {x, y + tile_size}, sf::Color::White, {tex_x, tex_y + tile_size}});

    background_tiles_.push_back(sf::Vertex{
        {x + tile_size, y}, sf::Color::White, {tex_x + tile_size, tex_y}});

    background_tiles_.push_back(
        sf::Vertex{{x + tile_size, y + tile_size},
                   sf::Color::White,
                   {tex_x + tile_size, tex_y + tile_size}});

    background_tiles_.push_back(sf::Vertex{
        {x, y + tile_size}, sf::Color::White, {tex_x, tex_y + tile_size}});
  }

  Render();
}
void Renderer::Render() {
  sf::RenderStates states;
  states.texture = &background_texture_;

  while (window_.isOpen()) {
    while (const std::optional event = window_.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window_.close();
      }
    }

    window_.clear();
    window_.draw(background_tiles_.data(), background_tiles_.size(),
                 sf::PrimitiveType::Triangles, states);
  }
}

}  // namespace citybuilder::graphics