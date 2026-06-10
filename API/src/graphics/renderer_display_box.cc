//
// Created by Arthur on 28.05.2026.
//

#include "../../include/graphics/renderer_display_box.h"

#include <SFML/Window/Event.hpp>

void RendererDisplayBox::HandleEvents(std::optional<sf::Event> event,
                                      const sf::RenderWindow& window,
                                      const sf::View& view) {
  if (const auto mouse_position =  window.mapCoordsToPixel(sf::Vector2f(sf::Mouse::getPosition(window)), view);
      shape.getGlobalBounds().contains(sf::Vector2f(mouse_position))) {
    shape.setFillColor(sf::Color::Red);
  }
}