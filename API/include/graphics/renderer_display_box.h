//
// Created by Arthur on 28.05.2026.
//

#ifndef CITYBUILDER_RENDERER_DISPLAY_BOX_H
#define CITYBUILDER_RENDERER_DISPLAY_BOX_H
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <functional>
#include <utility>

#include "utils/vector2.h"

struct RendererDisplayBox {
  RendererDisplayBox(const Vector2f position, const Vector2f size,
                     const Vector2i text_coords, sf::Text text,
                     const bool is_button, std::function<void()> action)
      : position(position),
        size(size),
        text_coords(text_coords),
        text(std::move(text)),
        is_button(is_button),
        action(std::move(action)) {}

  Vector2f position;
  Vector2f size;
  Vector2i text_coords;
  std::vector<sf::Vertex> vertices;
  sf::Text text;
  std::function<void()> action;
  bool is_button = false;
  bool InBounds(float x, float y) const;
  void ChangeColor(sf::Color color);
  void HandleEvents(const std::optional<sf::Event>&, const sf::RenderWindow&,
                    const sf::View& view);
};

#endif  // CITYBUILDER_RENDERER_DISPLAY_BOX_H
