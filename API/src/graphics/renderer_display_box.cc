//
// Created by Arthur on 28.05.2026.
//

#include "../../include/graphics/renderer_display_box.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

void RendererDisplayBox::HandleEvents(const std::optional<sf::Event>& event,
                                      const sf::RenderWindow& window,
                                      const sf::View& view) {
  const auto mouse_position =
      window.mapPixelToCoords(sf::Mouse::getPosition(window), view);

  if (is_button) {
    if (InBounds(mouse_position.x, mouse_position.y)) {
      ChangeColor(sf::Color{180, 180, 180});
      if (event->getIf<sf::Event::MouseButtonPressed>() && action) {
        action();
      }
    } else {
      ChangeColor(sf::Color::White);
    }

  }
}

inline bool RendererDisplayBox::InBounds(const float x, const float y) const {
  return x > position.x && x < position.x + size.x && y > position.y &&
         y < position.y + size.y;
}

void RendererDisplayBox::ChangeColor(const sf::Color color) {
  for (auto& vertex : vertices) {
    vertex.color = color;
  }
}