#ifndef PQUADTREE_H
#define PQUADTREE_H

#include <iostream>
using namespace std;

template <typename T>
struct Q_point{
  int x, y;
  T data;
  Q_point() : x(0), y(0) {};
  Q_point(int _x, int _y, T _data) : x(_x), y(_y), data(_data) {};
};

template <typename T>
class PointQuadTree {
private:
  Q_point<T>* root;
  PointQuadTree *nw, *ne, *sw, *se;
public:
  PointQuadTree() : root(nullptr), nw(nullptr), ne(nullptr), sw(nullptr), se(nullptr) {};

  ~PointQuadTree() {
    if (nw != nullptr) delete nw;
    if (ne != nullptr) delete ne;
    if (sw != nullptr) delete sw;
    if (se != nullptr) delete se;
  }

  void insert(int x, int y, T data) {
    if (root == nullptr) {
      root = new Q_point<T>(x, y, data);
      return;
    }
    if (x < root->x) {
      if (y < root->y) {
        if (sw == nullptr) sw = new PointQuadTree<T>();
        sw->insert(x, y, data);
      } else {
        if (nw == nullptr) nw = new PointQuadTree<T>();
        nw->insert(x, y, data);
      }
    } else {
      if (y < root->y) {
        if (se == nullptr) se = new PointQuadTree<T>();
        se->insert(x, y, data);
      } else {
        if (ne == nullptr) ne = new PointQuadTree<T>();
        ne->insert(x, y, data);
      }
    }
  }

  Q_point<T> *getRoot() const { return root;}
  PointQuadTree *getNW() const { return nw;}
  PointQuadTree *getNE() const { return ne;}
  PointQuadTree *getSW() const { return sw;}
  PointQuadTree *getSE() const { return se;}


};

#endif // PQUADTREE_H
