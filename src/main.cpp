#include <SFML/Graphics.hpp>
#include "PointQuadTree.h"
#include "QuadTreeRenderer.h"

int main() {

  PointQuadTree<int> tree;
  QuadTreeRenderer<int> renderQTree(800,800);
  renderQTree.render(tree);

}
