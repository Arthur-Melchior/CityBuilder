//
// Created by Kalle on 07.05.2026.
//

#ifndef CITYBUILDER_RENDERER_H
#define CITYBUILDER_RENDERER_H

#include <SFML/Graphics.hpp>

namespace citybuilder::graphics {

class Renderer {
public:
  Renderer(unsigned int width, unsigned int height, const sf::String& title);

  [[nodiscard]] bool IsOpen() const;

  void ProcessEvents();
  void Clear(const sf::Color& color = sf::Color::Black);
  void Draw(const sf::Drawable& drawable);
  void RenderFrame();

private:
  sf::RenderWindow window_;
};

void startRender();

}  // namespace citybuilder::graphics

#endif  // CITYBUILDER_RENDERER_H