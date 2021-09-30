#pragma once

#include "SpatialBase.h"

namespace utec {
namespace spatial {

  /**
   * RT1DNode
   */

  template<typename Point>
  class RT1DNode:public SpatialBase<Point>{
    private:
      Point *content;
      RT1DNode *left;
      RT1DNode *right;
    public:
      RT1DNode(){};
      RT1DNode(Point *c):content(c),left(nullptr),right(nullptr){};

      void setContent(Point _content){
        *content = _content;
      }

      Point *getContent(){
        return content;
      }

      void insert(Point _content){
        if(content > _content){
          if(left == nullptr){
            left = new RT1DNode(_content);
          }else{
            left->insert(_content);
          }
        }else{
          if(right == nullptr){
            right = new RT1DNode(_content);
          }else{
            right->insert(_content);
          }
        }
      }

      void leftRotation(){
        Point aux;
        aux = *content;
        *content = *(left->content);
        *(left->content) = aux;
      }

      void rightRotation(){
        Point aux;
        aux = *content;
        *content = *(right->content);
        *(right->content) = aux;
      }
  };

/**
 * RangeTree1D implementation
 */
template <typename Point>
class RangeTree1D : public SpatialBase<Point> {
 private:
  RT1DNode *root;
 public:
  RangeTree1D(){
    root = new RT1DNode();
  };

  void insert(const Point& new_point) override {}

  // El punto de referencia no necesariamente es parte del dataset
  Point nearest_neighbor(const Point& reference) override { return Point({0}); }
  std::vector<Point> range(const Point& min, const Point& max) override {
    return {};
  };
};

}  // namespace spatial
}  // namespace utec
