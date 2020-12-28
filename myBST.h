#ifndef MYBST_H
#define MYBST_H
#include "myBinTree.h"
#include <algorithm>
// key is element, same value is not allowed

template <class T>
class BST : public BinTree<T> {
protected:
  TreeNode<T>* _hot;

public:
  virtual TreeNode<T>*& search(const T& e) {
    return searchIn(this->_root, e, _hot = 0);
  }
  TreeNode<T>*& searchIn(TreeNode<T>*& p, const T& e, TreeNode<T>* &hot) {
    if(!p || e == p->data) return p;
    _hot = p;
    return searchIn(e < p->data ? p->left : p->right, e, hot);
  }
  virtual TreeNode<T>* insert(const T& e) {
    if(this->_size == 0) {
      return this->insertAsRoot(e);
    }
    TreeNode<T>* &p = search(e);
    if(p) return p;
    p = new TreeNode<T>(e, _hot);
    this->_size++;
    this->updateHeightAbove(_hot);
    return p;
  }
  virtual bool remove(const T& e) {
    TreeNode<T>* &p = search(e);
    if(!p) return false;
    removeAt(p, _hot);
    this->_size--;
    this->updateHeightAbove(_hot);
    return true;
  }

  static TreeNode<T>* removeAt(TreeNode<T>* &p, TreeNode<T>* &hot) {   // return the node at deleted position
    TreeNode<T> *w = p;                                                // set hot to deleted item's parent
    TreeNode<T> *toReturn = 0;
    if(!p->hasLeft()) {
      p = p->right;
      toReturn = p;
    } else if(!p->hasRight()) {
      p = p->left;
      toReturn = p;
    } else {
      w = w->succ();
      std::swap(w->data, p->data);
      TreeNode<T>* u = w->parent;
      if(u == p) {
        u->right = w->right;
        toReturn = u->right;
      } else {
        u->left = w->right;
        toReturn = u->left;
      }
    }
    hot = w->parent;
    if(toReturn) toReturn->parent = hot;
    delete w;
    return toReturn;
  }
};
#endif