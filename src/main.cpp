#include <SFML/Graphics.hpp>

int main() {
  auto window = sf::RenderWindow({1200u, 700u}, "CMake SFML Project");
  window.setFramerateLimit(75);

  sf::CircleShape circle(50.f);
  circle.setFillColor(sf::Color::Green);
  circle.setPosition(600.f, 350.f);

  sf::ConvexShape triangle(3);
  triangle.setPoint(0, {100.f, 100.f});
  triangle.setPoint(1, {200.f, 100.f});
  triangle.setPoint(2, {150.f, 200.f});
  triangle.setFillColor(sf::Color::Magenta);

  while (window.isOpen()) {
    for (auto event = sf::Event(); window.pollEvent(event);) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear();
    window.draw(circle);
    window.draw(triangle);
    window.display();


    
  }
}
