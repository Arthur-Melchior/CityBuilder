//
// Created by Arthur on 28.05.2026.
//

#ifndef CITYBUILDER_RENDERER_DISPLAY_BOX_H
#define CITYBUILDER_RENDERER_DISPLAY_BOX_H
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

struct RendererDisplayBox {
  RendererDisplayBox(const sf::RectangleShape &shape, const sf::Text &text)
      : shape(shape), text(text) {}

  sf::RectangleShape shape;
  sf::Text text;
  void HandleEvents(std::optional<sf::Event>, const sf::RenderWindow&,
                    const sf::View &view);
};

#endif  // CITYBUILDER_RENDERER_DISPLAY_BOX_H
