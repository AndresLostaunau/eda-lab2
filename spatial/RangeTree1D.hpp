#pragma once

#include "SpatialBase.h"

namespace utec {
namespace spatial {

/**
 * RangeTree1D implementation
 */
template <typename Point>
class RangeTree1D : public SpatialBase<Point> {
   private:
      Point content;
      int height;
      RangeTree1D<Point> *left;
      RangeTree1D<Point> *right;
    public:
      RangeTree1D<Point>(){};
      RangeTree1D<Point>(Point c):content(c),height(1),left(nullptr),right(nullptr){};

      void setContent(Point _content){
        content = _content;
      }

      void setHeight(int h){
        height = h;
      }

      void setLeft(RangeTree1D<Point> *l){
        left = l;
      }

      void setRight(RangeTree1D<Point> *r){
        right = r;
      }

      Point getContent(){
        return content;
      }

      int getHeight(){
        return height;
      }

      RangeTree1D<Point> *getLeft(){
        return left;
      }

      RangeTree1D<Point> *getRight(){
        return right;
      }

      void leftRotation(){
        Point aux;
        RangeTree1D<Point> *aux_ptr;
        aux = this->getContent();
        this->setContent(this->getRight()->getContent());
        this->getRight()->setContent(aux);

        aux_ptr = this->getLeft();
        this->setLeft(this->getRight());
        this->setRight(this->getLeft()->getRight());
        this->getLeft()->setRight(this->getLeft()->getLeft());
        this->getLeft()->setLeft(aux_ptr);
      }

      void rightRotation(){
        Point aux;
        RangeTree1D<Point> *aux_ptr;
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

      void insert(const Point& _content) override {
        int l=1, r=1;
        Point aux;
        if(this->content < _content){
          if(this->right == nullptr){
            aux = this->getContent();
            this->setContent(_content);
            this->setLeft(new RangeTree1D<Point>(_content));
            this->setRight(new RangeTree1D<Point>(aux));
            this->setHeight(2);
          }else{
            this->getRight()->insert(_content);
          }
        }else{
            if(this->left == nullptr){
            aux = this->getContent();
            this->setContent(_content);
            this->setLeft(new RangeTree1D<Point>(_content));
            this->setRight(new RangeTree1D<Point>(aux));
            this->setHeight(2);
          }else{
            this->getLeft()->insert(_content);
          }
        }
        if(l > r){
          this->setHeight(this->getLeft()->getHeight()+1);
        }else{
          this->setHeight(this->getRight()->getHeight()+1);
        }
        balance();
      }

  // El punto de referencia no necesariamente es parte del dataset
  Point nearest_neighbor(const Point& reference) override { return Point({0}); }

  void rec_range(std::vector<Point> *ans_vec, RangeTree1D<Point> *it, const Point& min, const Point& max){
    if(it->getLeft()==nullptr){
      if((min < it->getContent() or it->getContent()==min) && (it->getContent() < max or it->getContent()==max) ){
        ans_vec->push_back(it->getContent());
      }
    }

    if(it->getContent() < min){
      rec_range(ans_vec,it->getRight(),min,max);
    }else if(max < it->getContent()){
      rec_range(ans_vec,it->getLeft(),min,max);
    }else{
      rec_range(ans_vec,it->getLeft(),min,max);
      rec_range(ans_vec,it->getRight(),min,max);
    }
  }

  std::vector<Point> range(const Point& min, const Point& max) override {
    std::vector<Point> ans_vec;
    rec_range(&ans_vec,this,min,max);
    return ans_vec;
  };
};

}  // namespace spatial
}  // namespace utec
