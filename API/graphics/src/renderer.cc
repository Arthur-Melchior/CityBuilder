//
// Created by Kalle on 07.05.2026.
//

#include "renderer.h"

#include "tile_map.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <optional>
#include <vector>

namespace citybuilder::graphics {

Renderer::Renderer(const unsigned int width, const unsigned int height, const sf::String& title)
    : window_(sf::VideoMode({width, height}), title) {}

bool Renderer::IsOpen() const {
  return window_.isOpen();
}

void Renderer::ProcessEvents() {
  while (const std::optional event = window_.pollEvent())
  {
    if (event->is<sf::Event::Closed>())
    {
      window_.close();
    }
    else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
    {
      if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
      {
        window_.close();
      }
    }
  }
}

void Renderer::Clear(const sf::Color& color) {
  window_.clear(color);
}

void Renderer::Draw(const sf::Drawable& drawable) {
  window_.draw(drawable);
}

void Renderer::RenderFrame() {
  window_.display();
}

void startRender() {
  Renderer renderer(800, 600, "CityBuilder");

  constexpr unsigned int mapWidth = 25;
  constexpr unsigned int mapHeight = 19;

  std::vector<int> tiles(mapWidth * mapHeight, 0);

  for (unsigned int y = 0; y < mapHeight; ++y)
  {
    for (unsigned int x = 0; x < mapWidth; ++x)
    {
      tiles[x + y * mapWidth] = static_cast<int>((x + y) % 4);
    }
  }

  while (renderer.IsOpen())
  {
    renderer.ProcessEvents();
    renderer.Clear();
    renderer.RenderFrame();
  }
}

}  // namespace citybuilder::graphics