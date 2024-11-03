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
      : window(sf::VideoMode(width, height), "PointQuadTree"),
        rootPointDrawn(false) {}
  void render(PointQuadTree<T>& tree) {
    window.setFramerateLimit(75);

    int data = 0;
    while (window.isOpen()) {
      for (auto event = sf::Event(); window.pollEvent(event);) {
        if (event.type == sf::Event::Closed) {
          window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {
          sf::Vector2i mousePos = sf::Mouse::getPosition(window);
          tree.insert(mousePos.x, mousePos.y, data++);
          drawPoint(mousePos.x, mousePos.y);
          drawLines(tree);

          cout << mousePos.x << " - " << mousePos.y << endl;
        }
      }



      window.clear();
      // window.draw(circle);
      // window.draw(triangle);

      for (auto& point : points) {
        window.draw(point);
      }

      for (auto& line : lines) {
        window.draw(line);
      }
      window.display();
    }
  }

 private:
  sf::RenderWindow window;
  vector<sf::CircleShape> points;
  vector<sf::VertexArray> lines;
  bool rootPointDrawn;

  void drawPoint(float x, float y) {
    sf::CircleShape circle(5.f);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(x - 5, y - 5);
    points.push_back(circle);
  }

  void drawLines(PointQuadTree<int>& tree) {
    drawingTwoLines(tree, 0, 0, window.getSize().x, window.getSize().y);
  }

  /*
   * (topX,topY)
   *    -----------------
   *   |                 |
   *   |                 |
   *   |                 |
   *   |                 |
   *   |                 |
   *   ------------------ (botX), botY)
   * */
void drawingTwoLines(PointQuadTree<int>& tree, int xMin, int yMin, int xMax, int yMax) {
    if (!tree.getRoot()) return;

    int rootX = tree.getRoot()->x;
    int rootY = tree.getRoot()->y;

    sf::VertexArray verticalLine(sf::Lines, 2);
    verticalLine[0].position = sf::Vector2f(rootX, yMin);  // Desde la parte superior hasta el límite inferior del cuadrante
    verticalLine[1].position = sf::Vector2f(rootX, yMax);
    verticalLine[0].color = sf::Color::White;
    verticalLine[1].color = sf::Color::White;

    sf::VertexArray horizontalLine(sf::Lines, 2);
    horizontalLine[0].position = sf::Vector2f(xMin, rootY); // Desde el límite izquierdo hasta el derecho en la línea del punto
    horizontalLine[1].position = sf::Vector2f(xMax, rootY);
    horizontalLine[0].color = sf::Color::White;
    horizontalLine[1].color = sf::Color::White;

    lines.push_back(verticalLine);
    lines.push_back(horizontalLine);

    if (tree.getNW()) drawingTwoLines(*tree.getNW(), xMin, rootY, rootX, yMax); // Noroeste
    if (tree.getNE()) drawingTwoLines(*tree.getNE(), rootX, rootY, xMax, yMax); // Noreste
    if (tree.getSW()) drawingTwoLines(*tree.getSW(), xMin, yMin, rootX, rootY); // Suroeste
    if (tree.getSE()) drawingTwoLines(*tree.getSE(), rootX, yMin, xMax, rootY); // Sureste
}
};

#endif  // QUADTREE_RENDER_H
