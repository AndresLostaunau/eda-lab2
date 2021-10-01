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
      Point content;
      int height;
      RT1DNode *left;
      RT1DNode *right;
    public:
      RT1DNode(){};
      RT1DNode(Point c):content(c),height(1),left(nullptr),right(nullptr){};

      void setContent(Point _content){
        content = _content;
      }

      void setHeight(int h){
        height = h;
      }

      void setLeft(RT1DNode *l){
        left = l;
      }

      void setRight(RT1DNode *r){
        right = r;
      }

      Point getContent(){
        return content;
      }

      int getHeight(){
        return height;
      }

      RT1DNode *getLeft(){
        return left;
      }

      RT1DNode *getRight(){
        return right;
      }

      void leftRotation(){
        Point aux;
        RT1DNode *aux_ptr;
        aux = this->getContent();
        this->setContent = this->getRight()->getContent();
        this->getRight()->setContent(aux);

        aux_ptr = this->getLeft();
        this->setLeft(this->getRight());
        this->setRight(this->getLeft()->getRight());
        this->getLeft()->setRight(this->getLeft()->getLeft());
        this->getLeft()->setLeft(aux_ptr);
      }

      void rightRotation(){
        Point aux;
        RT1DNode *aux_ptr;
        aux = this->getContent();
        this->setContent(this->getLeft()->getContent());
        this->getLeft()->setContent(aux);

        aux_ptr = this->getRight();
        this->setRight(this->getLeft());
        this->setLeft(this->getRight()->getLeft());
        this->getRight()->setLeft(this->getRight()->getRight());
        this->getRight()->setRight(aux_ptr);
      }

      void LRRotation(){
        this->getLeft()->leftRotation();
        this->rightRotation();
        setHeight(getHeight()-1);
        this->getRight()->setHeight(this->getRight()->getHeight()-1);
      }

      void RLRotation(){
        this->getRight()->rightRotation();
        this->leftRotation();
        setHeight(getHeight()-1);
        this->getLeft()->setHeight(this->getLeft()->getHeight()-1);
      }

      void balance(){
        int lh = 0, rh = 0;
        if(this->getLeft() != nullptr){
          lh = this->getLeft()->getHeight();
        }
        if(this->getRight() != nullptr){
          rh = this->getRight()->getHeight();
        }
        if((lh - rh) > 1){
          if(this->getLeft()->getRight()->getHeight() > this->getLeft()->getLeft()->getHeight()){
            this->LRRotation();
          }else{
            this->leftRotation();
          }
        }else if((lh - rh) < -1){
          if(this->getRight()->getRight()->getHeight() < this->getRight()->getLeft()->getHeight()){
            this->RLRotation();
          }else{
            this->rightRotation();
          }
        }
      }

      // int insert(Point _content){
      //   int l=1, r=1, aux;
      //   if(this->content > _content){
      //     if(this->left == nullptr){
      //       aux = this->getContent();
      //       this->setContent(_content);
      //       this->setLeft(new RT1DNode(_content));
      //       this->setRight(new RT1DNode(aux));
      //       this->setHeight(2);
      //       return 2;
      //     }else{
      //       l = this->getLeft()->insert(_content);
      //     }
      //   }else{
      //     if(this->right == nullptr){
      //       aux = this->getContent();
      //       this->setContent(_content);
      //       this->setLeft(new RT1DNode(_content));
      //       this->setRight(new RT1DNode(aux));
      //       this->setHeight(2);
      //       return 2;
      //     }else{
      //       r = this->getRight()->insert(_content);
      //     }
      //   }
      //   if(l > r){
      //     this->setHeight(l+1);
      //   }else{
      //     this->setHeight(r+1);
      //   }
      //   balance();
      //   return this->height;
      // }
  };

/**
 * RangeTree1D implementation
 */
template <typename Point>
class RangeTree1D : public SpatialBase<Point> {
 private:
  RT1DNode<Point>* root;
 public:
  RangeTree1D(){
    //root = new RT1DNode();
  };

  void insert(const Point& new_point) override {
    //root->insert(new_point);
  }

  // El punto de referencia no necesariamente es parte del dataset
  Point nearest_neighbor(const Point& reference) override { return Point({0}); }
  std::vector<Point> range(const Point& min, const Point& max) override {
    return {};
  };
};

}  // namespace spatial
}  // namespace utec
