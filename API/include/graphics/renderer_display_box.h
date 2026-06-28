//
// Created by Arthur on 28.05.2026.
//

#ifndef CITYBUILDER_RENDERER_DISPLAY_BOX_H
#define CITYBUILDER_RENDERER_DISPLAY_BOX_H
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <utility>

struct RendererDisplayBox {
  RendererDisplayBox(sf::RectangleShape shape, sf::Text text,
                     const bool is_button)
      : shape(std::move(shape)), text(std::move(text)), is_button(is_button) {}

  sf::RectangleShape shape;
  sf::Text text;
  bool is_button = false;
  void HandleEvents(std::optional<sf::Event>, const sf::RenderWindow&,
                    const sf::View &view);
};

#endif  // CITYBUILDER_RENDERER_DISPLAY_BOX_H
