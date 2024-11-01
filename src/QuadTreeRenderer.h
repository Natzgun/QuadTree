#ifndef QUADTREE_RENDER_H
#define QUADTREE_RENDER_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <vector>

#include "PointQuadTree.h"
template <typename T>
class QuadTreeRenderer {
 public:
  QuadTreeRenderer(int width, int height)
      : window(sf::VideoMode(width, height), "PointQuadTree") {}
  void render(PointQuadTree<T>& tree) {
    window.setFramerateLimit(75);

    /* sf::CircleShape circle(50.f);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(600.f, 350.f);

    sf::ConvexShape triangle(3);
    triangle.setPoint(0, {100.f, 100.f});
    triangle.setPoint(1, {200.f, 100.f});
    triangle.setPoint(2, {150.f, 200.f});
    triangle.setFillColor(sf::Color::Magenta); */

    while (window.isOpen()) {
      for (auto event = sf::Event(); window.pollEvent(event);) {
        if (event.type == sf::Event::Closed) {
          window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {
          sf::Vector2i mousePos = sf::Mouse::getPosition(window);
          drawPoint(mousePos.x, mousePos.y);

          cout << mousePos.x << " - " << mousePos.y << endl;
        }
      }

      window.clear();
      // window.draw(circle);
      // window.draw(triangle);
      
      for (auto& point : points) {
        window.draw(point);
      }
      window.display();
    }
  }

 private:
  sf::RenderWindow window;
  Q_point<int>* topLeft;
  Q_point<int>* botRight;
  vector<sf::CircleShape> points;

  void drawTree(sf::RenderWindow window, PointQuadTree<T>& tree);

  void drawPoint(float x, float y) {
    sf::CircleShape circle(10.f);
    circle.setFillColor(sf::Color::White);
    circle.setPosition(x, y);
    points.push_back(circle);
  }
};

#endif  // QUADTREE_RENDER_H
