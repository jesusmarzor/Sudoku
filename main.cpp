/**
 * @file main.cpp
 * @brief Inicializa la ventana y controla los eventos del juego
 * @author Jesús Martín
 * @date 04/06/2019
*/
#include "Sudoku.h"
#include <SFML/Graphics.hpp>

using namespace sf;

int main(void) {
  sf::RenderWindow window(sf::VideoMode(450,500), "Tablero");
  int size=50;
  Board board(9, 9, size);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (event.type == sf::Event::KeyPressed) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
          window.close();
        }
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
					board.derecha();
				}
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
					board.izquierda();
				}
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
					board.arriba();
				}
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
					board.abajo();
				}

      }else if (event.type == sf::Event::MouseButtonReleased) {
        board.action(event.mouseButton.x, event.mouseButton.y);
      }
    }
    window.clear();
    board.draw(window);
		window.display();
  }

  return 0;
}
