//
// Created by Arthur on 28.05.2026.
//

#include "../../include/graphics/renderer_display_box.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

void RendererDisplayBox::HandleEvents(std::optional<sf::Event> event,
                                      const sf::RenderWindow& window,
                                      const sf::View& view) {
  const auto mouse_position =
      window.mapPixelToCoords(sf::Mouse::getPosition(window), view);

  if (is_button) {
    if (shape.getGlobalBounds().contains(mouse_position)) {
      shape.setFillColor(sf::Color{180, 180, 180});
    } else {
      shape.setFillColor(sf::Color::White);
    }
  }
}