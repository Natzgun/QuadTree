#ifndef PRQUADTREE_H
#define PRQUADTREE_H

struct Q_point{
  int x, y;

  Q_point() : x(0), y(0) {};
  Q_point(int _x, int _y) : x(_x), y(_y) {};
};

class PRQuadTree {
private:
  PRQuadTree* right;
};

#endif // PRQUADTREE_H
