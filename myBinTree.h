#ifndef BINTREE_H
#define BINTREE_H
#include "myBinTreeNode.h"

template <class T>
class BinTree {
 protected:
  int _size;
  TreeNode<T>* _root;
  virtual int updateHeight(TreeNode<T>* p) {                    // update the height of this node
    if (p->hasBothChild()) {
      return p->height = 1 + ((p->left->height > p->right->height)
                             ? p->left->height
                             : p->right->height);
    } else if (p->hasLeft()) {
      return p->height = 1 + p->left->height;
    } else if (p->hasRight()) {
      return p->height = 1 + p->right->height;
    } else {
      return p->height = 0;
    }
  }
  void updateHeightAbove(TreeNode<T>* p) {
    while (p) {
      int oldHeight = p->height;
      updateHeight(p);
      if (p->height == oldHeight) return;                       // if the height of this node doesn't change, the ancestors of it doesn't change
      p = p->parent;
    }
  }
  TreeNode<T>* copyNodes(TreeNode<T>* old) {                    // copy nodes from the other tree
    if(!old) return nullptr;
    TreeNode<T>* p = new TreeNode<T>(old->data, 0, 0, 0, old->height, old->npl, old->color);
    p->left = copyNodes(old->left);
    if(p->left) p->left->parent = p;
    p->right = copyNodes(old->right);
    if(p->right) p->right->parent = p;
    return p;
  }

 public:
  BinTree() : _size(0), _root(0) {}
  BinTree(BinTree<T> *p) {
    _size = p->_size;
    _root = copyNodes(p->_root);
  }
  ~BinTree() {
    if (0 < _size) remove(_root);
  }
  int size() const { return _size; }
  bool empty() const { return !_root; }
  TreeNode<T>* root() const { return _root; }
  TreeNode<T>* insertAsRoot(T const& e) {          // always use this as the first method when you get a new tree
    _size = 1;
    _root = new TreeNode<T>(e);
    return _root;
  }
  TreeNode<T>* insertAsLeft(TreeNode<T>* p, const T& e) {
    _size++;
    p->insertAsLeft(e);
    updateHeightAbove(p);
    return p->left;
  }
  TreeNode<T>* insertAsRight(TreeNode<T>* p, const T& e) {
    _size++;
    p->insertAsRight(e);
    updateHeightAbove(p);
    return p->right;
  }
  TreeNode<T>* insertAsLeft(TreeNode<T>* p, BinTree<T>* Tr) {
    _size += Tr->size();
    p->left = Tr->root();
    p->left->parent = p;
    updateHeightAbove(p);
    Tr->_root = 0;
    Tr->_size = 0;
    return p;
  }
  TreeNode<T>* insertAsRight(TreeNode<T>* p, BinTree<T>* Tr) {
    _size += Tr->size();
    p->right = Tr->root();
    p->right->parent = p;
    updateHeightAbove(p);
    Tr->_root = 0;
    Tr->_size = 0;
    return p;
  }
  int remove(
      TreeNode<T>* p) {                                         // delete p and its subtree, return the number of deleted nodes
    bool deleteRoot = p == _root;
    TreeNode<T>* temp = p->parent;
    TreeNode<T>* toThis = 0;
    if(!deleteRoot) toThis = p->parentToThis();
    int n = removeHelper(p);
    toThis = 0;
    if(!deleteRoot) updateHeightAbove(temp);
    return n;
  }
protected:
  int removeHelper(TreeNode<T>* p) {
    if (!p) return 0;
    int nL = removeHelper(p->left);
    int nR = removeHelper(p->right);
    delete p;
    return nL + nR + 1;
  }
public:
  BinTree<T>* secede(
      TreeNode<T>* p) {                                           // delete p and its subtree, then return as a new tree, if the return value is not stored, memory leak happens
  p->parentToThis() = 0;
    TreeNode<T>* parentNode = p->parent;
    p->parent = 0;
    updateHeightAbove(parentNode);
    BinTree<T>* tree = new BinTree;
    tree->_root = p;
    tree->_size = p->size();
    this->_size -= tree->_size;
    return tree;
  }

  template <class functor>
  void travLevel(functor& f) {
    if (root()) _root->travLevel(f);
  }
  template <class functor>
  void travPre(functor& f) {
    if (root()) _root->travPre(f);
  }
  template <class functor>
  void travIn(functor& f) {
    if (root()) _root->travIn(f);
  }
  template <class functor>
  void travPost(functor& f) {
    if (root()) _root->travPost(f);
  }
  void printTree() const {
    _root->printTree();
  }
  void printDetailedTree() const {
    _root->printDetailedTree();
  }
};

#endif