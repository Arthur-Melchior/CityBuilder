//
// Created by Kalle on 15.07.2026.
//

#include "start_menu.h"

#include "graphics/renderer.h"

void StartMenu::Render() {
  sf::RenderWindow window(sf::VideoMode({800, 800}), "city builder",
                          sf::Style::Default, sf::State::Windowed);
  sf::Texture tile_sheet;
  if (!tile_sheet.loadFromFile("_assets/tile_sheets/complete_tile_sheet.png")) {
    return;
  }

  tile_sheet.setSmooth(false);

  sf::Font font;
  if (!font.openFromFile("_assets/arial.ttf")) {
    return;
  }
  sf::RectangleShape new_game_button({300, 150});
  new_game_button.setPosition(
      sf::Vector2f(window.getSize().x / 2, window.getSize().y / 3) -
      sf::Vector2f(new_game_button.getSize().x / 2,
                   new_game_button.getSize().y));
  sf::Text new_game_text(font, sf::String{"new game"}, 20);
  new_game_text.setOrigin(new_game_button.getOrigin());
  new_game_text.setPosition(
      new_game_button.getPosition() +
      sf::Vector2f{new_game_button.getSize().x / 2 -
                       new_game_text.getGlobalBounds().size.x / 2,
                   new_game_button.getSize().y / 2 -
                       new_game_text.getGlobalBounds().size.y / 2});
  new_game_text.setFillColor(sf::Color::Black);

  sf::RectangleShape load_game_button({300, 150});
  load_game_button.setPosition(sf::Vector2f(
      new_game_button.getPosition().x, new_game_button.getPosition().y + 300));
  sf::Text load_game_text(font, sf::String{"load game"}, 20);
  load_game_text.setOrigin(new_game_button.getOrigin());
  load_game_text.setPosition(
      load_game_button.getPosition() +
      sf::Vector2f{load_game_button.getSize().x / 2 -
                       load_game_text.getGlobalBounds().size.x / 2,
                   load_game_button.getSize().y / 2 -
                       load_game_text.getGlobalBounds().size.y / 2});
  load_game_text.setFillColor(sf::Color::Black);

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        exit(0);
      }

      if (new_game_button.getGlobalBounds().contains(
              sf::Vector2<float>(sf::Mouse::getPosition(window)))) {
        new_game_button.setFillColor(sf::Color::Blue);

        if (event->is<sf::Event::MouseButtonPressed>()) {
          window.close();
          citybuilder::game::Game game{200, 200};
          game.StartGame();
        }
      } else {
        new_game_button.setFillColor(sf::Color::White);
      }

      if (load_game_button.getGlobalBounds().contains(
              sf::Vector2<float>(sf::Mouse::getPosition(window)))) {
        load_game_button.setFillColor(sf::Color::Blue);
        if (event->is<sf::Event::MouseButtonPressed>()) {
          window.close();
          citybuilder::game::Game game{200, 200};
          game.StartGame();
        }
      } else {
        load_game_button.setFillColor(sf::Color::White);
      }
    }

    window.clear();
    window.draw(new_game_button);
    window.draw(new_game_text);
    window.draw(load_game_button);
    window.draw(load_game_text);
    window.display();
  }
}
