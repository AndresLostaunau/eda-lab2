#pragma once

#include "SpatialBase.h"

namespace utec {
namespace spatial {
/**
 * RangeBST node
 */
template <typename Point>
struct NodeBT {
    Point data;
    NodeBT* left;
    NodeBT* right;
    NodeBT() : left(nullptr), right(nullptr) {}
    NodeBT(Point value) : data(value), left(nullptr), right(nullptr) {}
};



/**
 * RangeBST implementation
 */
template <typename Point>
class RangeBST : public SpatialBase<Point> {
 private:
  NodeBT<Point>* root;
 public:
  RangeBST(){
    root = nullptr;
  };
  
  //RangeBST(): root(nullptr){}

  void insert(const Point& new_point) override {
    insert(this->root, new_point);
  }

  // El punto de referencia no necesariamente es parte del dataset
  Point nearest_neighbor(const Point& reference) override { return Point({0}); }
  
  
  std::vector<Point> range(const Point& min, const Point& max) override {
    std::vector<Point> results;
      rangebst(this->root,min,max,results);
      // for(int i=0; i< results.size(); i++){
      //   cout<< results[i]<< "  ";
      // }
    return results;
  };

  private:
    void insert(NodeBT<Point>* &node, Point value){
      if(node == nullptr) {
        node = new NodeBT<Point>(value);
      }
      else if(value < node->data)
          insert(node->left, value);
      else
          insert(node->right, value);
    };


    void rangebst(NodeBT<Point>* root, Point min, Point max, std::vector<Point> &results){
      if(root == nullptr) return;

      if(min < root->data){
        rangebst(root->left, min, max,results);
      }
      if ((min < root->data || min == root->data) && (root->data < max || root->data == max) ){
        results.push_back(root->data);
      }
      if(root->data < max){
        rangebst(root->right, min, max,results);
      }
    }
  };




}  // namespace spatial
}  // namespace utec
