#ifndef MYBINTREENODE_H
#define MYBINTREENODE_H
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

typedef enum { RED, BLACK } RBColor;  // For further RB tree

template <class T>
struct TreeNode {
  // member
  T data;
  TreeNode<T>* parent;
  TreeNode<T>* left;
  TreeNode<T>* right;
  int height;
  int npl;        // Null Path Length
  RBColor color;  // For further RB tree

  // ctor
  TreeNode(const T& e = T(), TreeNode<T>* p = 0, TreeNode<T>* le = 0,
           TreeNode<T>* r = 0, int h = 0, int l = 0, RBColor c = RED)
      : data(e), parent(p), left(le), right(r), height(h), npl(l), color(c) {}

  // methods
  int size() const {  // return the size of the tree
    int s = 1;
    if (left) s += left->size();
    if (right) s += right->size();
    return s;
  }

  TreeNode<T>* insertAsLeft(const T& e) { // insert element as left child of this node, return nullptr if it's failed
    return left = new TreeNode(e, this); 
  }
  TreeNode<T>* insertAsRight(const T& e) {  // insert element as right child of this node, return nullptr if it's failed
    return right = new TreeNode(e, this);
  }

  TreeNode<T>* succ() {                 // find the succeesor of this node in inorder traversal, return nullptr if there is no successor
    TreeNode<T>* p = this;
    if (hasRight()) {
      p = p->right;
      while (p->hasLeft()) p = p->left;
      return p;
    } else {
      while (p->isRight()) p = p->parent;
      return p->parent;
    }
  }

  TreeNode<T>* pred() {                  // find the precursor of this node in inorder traversal, return nullptr if there is no precursor
    TreeNode<T>* p = this;
    if (hasLeft()) {
      p = p->left;
      while (p->hasRight()) p = p->right;
      return p;
    } else {
      while (p->isLeft()) p = p->parent;
      return p->parent;
    }
  }

  // traversals
  // levelOrderTraversal
  template <class functor>
  void travLevel(functor& f) {  // ignore the details of each level (class
                                // member "height" can be used to recover)
    std::queue<TreeNode<T>*> q;
    q.push(this);
    while (!q.empty()) {
      TreeNode<T>* p = q.front();
      q.pop();
      f(p->data);
      if (p->left) q.push(p->left);
      if (p->right) q.push(p->right);
    }
  }

  // preOrderTraversal
  template <class functor>
  void travPre(functor& f) {    // the universal interface of each version
    std::srand(std::time(0));
    switch (0) {
      case 1:
        travPre_I1(f);
        break;
      case 2:
        travPre_I2(f);
        break;
      default:
        travPre_R(f);
        break;
    }
  }

  template <class functor>
  void travPre_R(TreeNode<T>* p, functor& f) {  // recursive preorder traversal 
    if (!p) return;
    f(p->data);
    travPre_R(p->left, f);
    travPre_R(p->right, f);
  }

  template <class functor>
  void travPre_R(functor& f) {  // to simplify the interface
    travPre_R(this, f);
  }

  template <class functor>
  void travPre_I1(functor& f) {   // iterative perorder traversal version 1
    TreeNode<T>* p = this;
    std::stack<TreeNode<T>*> s;
    s.push(p);
    while (!s.empty()) {
      TreeNode<T>* p = s.top();
      s.pop();
      f(p->data);
      if (p->right) s.push(p->right);
      if (p->left) s.push(p->left);
    }
  }

  template <class functor>
  void travPre_I2(functor& f) {   //iterative preorder traversal version 2
    TreeNode<T>* p = this;
    std::stack<TreeNode<T>*> s;
    while (1) {
      while (p) {
        f(p->data);
        if (p->right) s.push(p->right);
        p = p->left;
      }
      if (s.empty()) break;
      p = s.top();
      s.pop();
    }
  }

  // inOrderTraversal
  template <class functor>
  void travIn(functor& f) {         // the universal interface of each version
    std::srand(std::time(0));
    switch (std::rand() % 5) {
      case 1:
        travIn_I1(f);
        break;
      case 2:
        travIn_I2(f);
        break;
      case 3:
        travIn_I3(f);
        break;
      case 4:
        travIn_I4(f);
        break;
      default:
        travIn_R(f);
        break;
    }
  }

  template <class functor>
  void travIn_R(TreeNode<T>* p, functor& f) {   // recursive inorder traversal
    if (!p) return;
    travIn_R(p->left, f);
    f(p->data);
    travIn_R(p->right, f);
  }

  template <class functor>
  void travIn_R(functor& f) {
    travIn_R(this, f);
  }

  template <class functor>
  void travIn_I1(functor& f) {          // version 1
    TreeNode<T>* p = this;
    std::stack<TreeNode<T>*> s;
    while (1) {
      while (p) {
        s.push(p);
        p = p->left;
      }
      if (s.empty()) break;
      p = s.top();
      s.pop();
      f(p->data);
      p = p->right;
    }
  }

  template <class functor>
  void travIn_I2(functor& f) {              //version 2
    TreeNode<T>* p = this;
    std::stack<TreeNode<T>*> s;
    while (1) {
      if (p) {
        s.push(p);
        p = p->left;
      } else if (!s.empty()) {
        p = s.top();
        s.pop();
        f(p->data);
        p = p->right;
      } else {
        break;
      }
    }
  }

  template <class functor>
  void travIn_I3(functor& f) {    // version 3
    TreeNode<T>* p = this;
    bool backtrack = 0;  // backtrace switch, will be 1 if it is just backtraced
    while (1) {
      if (p && !backtrack) {
        while (p->left) {
          p = p->left;
        }
        f(p->data);
        if (p->right) {
          p = p->right;
        } else {
          p = p->succ();
          backtrack = 1;
        }
      } else if (p && backtrack) {
        f(p->data);
        if (p->right) {
          p = p->right;
          backtrack = 0;
        } else {
          p = p->succ();
        }
      } else {
        break;
      }
    }
  }

  template <class functor>
  void travIn_I4(functor& f) {      //version 4
    TreeNode<T>* p = this;
    while (p->left) {
        p = p->left;
    }
    while (p) {
      f(p->data);
      if(p->right) {
        p = p->right;
        while (p->left) {
          p = p->left;
        }
      } else {
        p = p->succ();
      }
    }
  }

  // postOrderTraversal
  template <class functor>
  void travPost(functor& f) {
    std::srand(std::time(0));
    switch (std::rand() % 3) {
      case 1:
        travPost_I1(f);
        break;
      case 2:
        travPost_I2(f);
        break;
      default:
        travPost_R(f);
        break;
    }
  }

  template <class functor>
  void travPost_R(TreeNode<T>* p, functor& f) {
    if (!p) return;
    travPost_R(p->left, f);
    travPost_R(p->right, f);
    f(p->data);
  }

  template <class functor>
  void travPost_R(functor& f) {
    travPost_R(this, f);
  }

  template <class functor>
  void travPost_I1(functor& f) {         //version 1 needs parent pointer, not universal enough
    TreeNode<T>* p = this;
    std::stack<TreeNode<T>*> s;
    s.push(p);
    while (!s.empty()) {
      if (s.top() != p->parent) gotoHLVFL(s);
      p = s.top();
      s.pop();
      f(p->data);
    }
  }

  static void gotoHLVFL(std::stack<TreeNode<T>*>& s) {
    while (TreeNode<T>* p = s.top()) {
      if (p->left) {
        if (p->right) s.push(p->right);
        s.push(p->left);
      } else
        s.push(p->right);
    }
    s.pop();
  }

  template <class functor>
  void travPost_I2(functor& f) {   //good one
    TreeNode<T>* p = this;
    TreeNode<T>* last;
    std::stack<TreeNode<T>*> s;
    while (p) {
      s.push(p);
      p = p->left;
    }
    while (!s.empty()) {
      p = s.top();
      if (p->right == last || !p->right) {
        s.pop();
        f(p->data);
        last = p;
      } else {
        p = p->right;
        while (p) {
          s.push(p);if(p->right) p = p->right;
          p = p->left;
        }
      }
    }
  }

  // magic traversals
  template <class functor>
  void travPre_Morris(functor& f) {
    TreeNode<T>*p, *cur = this;
    while (cur) {
      if (!cur->left) {
        f(cur->data);
        cur = cur->right;
      } else {
        p = cur->left;
        while (p->right && p->right != cur) p = p->right;
        if (!p->right) {
          p->right = cur;
          f(cur->data);
          cur = cur->left;
        } else {
          p->right = nullptr;
          cur = cur->right;
        }
      }
    }
  }

  template <class functor>
  void travIn_Morris(functor& f) {  // using only left and right pointer (no
                                    // parent pointer needed)
    TreeNode<T>*p, *cur = this;
    while (cur) {
      if (!cur->left) {
        f(cur->data);
        cur = cur->right;
      } else {
        p = cur->left;
        while (p->right && p->right != cur) {
          p = p->right;
        }
        if (!p->right) {
          p->right = cur;
          cur = cur->left;
        } else {
          p->right = 0;
          f(cur->data);
          cur = cur->right;
        }
      }
    }
  }

  template <class functor>
  void travPost_Morris(functor& f) {
    std::cout << "Using normal iterative traverse" << std::endl;
    travPost_I2(f);
  }

  // compariosn
  bool operator==(const TreeNode<T>& node) { return data == node.data; }
  bool operator<(const TreeNode<T>& node) { return data < node.data; }
  bool operator>(const TreeNode<T>& node) { return data > node.data; }
  bool operator<=(const TreeNode<T>& node) { return data <= node.data; }
  bool operator>=(const TreeNode<T>& node) { return data >= node.data; }

  // useful inline functions
  bool isRoot() const { return !parent; };
  bool isLeft() const { return !isRoot() && this == parent->left; }
  bool isRight() const { return !isRoot() && this == parent->right; }
  bool hasParent() const { return !isRoot(); }
  bool hasLeft() const { return left; }
  bool hasRight() const { return right; }
  bool hasChild() const { return hasLeft() || hasRight(); }
  bool hasBothChild() const { return hasLeft() && hasRight(); }
  bool isLeaf() const { return !hasBothChild(); }
  TreeNode<T>* sibling() const {
    return isLeft() ? this->parent->right : this->parent->left;
  }
  TreeNode<T>*& parentToThis() const {
    return isLeft() ? this->parent->left : this->parent->right;
  }

  // print the tree using levelOrderTraversal
  void printTree() const {
    std::queue<const TreeNode<T>*> q;
    int maxDepth = this->height;
    int maxWidth = (1 << (maxDepth + 1)) - 1;
    int level = 0;
    q.push(this);
    const TreeNode<T>* p;
    std::vector<const TreeNode<T>*> arr;
    while (level <= maxDepth) {
      int numOfThisLevel = 1 << level;
      int blank;
      blank = 1 << (maxDepth - level + 1);
      for (int i = 0; i < numOfThisLevel; i++) {  // in the level
        p = q.front();
        q.pop();
        arr.push_back(p);
        if (!p) {
          q.push(nullptr);
          q.push(nullptr);
        } else {
          q.push(p->left);
          q.push(p->right);
        }
      }
      for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < blank - 1; j++) std::cout << ' ';
        if (arr[i])
          std::cout << arr[i]->data;
        else
          std::cout << ' ';
        for (int j = 0; j < blank; j++) std::cout << ' ';
      }
      arr.clear();
      level++;
      std::cout << '\n';
    }
  }

  // print with branch, but take more space
  void printDetailedTree() const {
    std::cout << "Attention: Because of alignment issue, this method can only "
                 "print data that takes up one space!!! e.g. 'a' '1' '/' \n";
    std::queue<const TreeNode<T>*> q;
    int maxDepth = this->height;
    int maxWidth = (1 << (maxDepth + 1)) - 1;
    int level = 0;
    q.push(this);
    const TreeNode<T>* p;
    std::vector<const TreeNode<T>*> arr;
    while (level <= maxDepth) {
      int numOfThisLevel = 1 << level;
      int blank;
      blank = 1 << (maxDepth - level + 1);
      for (int i = 0; i < numOfThisLevel; i++) {  // in the level
        p = q.front();
        q.pop();
        arr.push_back(p);
        if (!p) {
          q.push(nullptr);
          q.push(nullptr);
        } else {
          q.push(p->left);
          q.push(p->right);
        }
      }
      for (int i = 0; i < arr.size(); i++) {
        if (!arr[i]) {
          for (int j = 0; j < 2 * blank; j++) std::cout << ' ';
        } else {
          if (arr[i]->left) {
            int j = 0;
            for (j = 0; j < blank / 2; j++) std::cout << ' ';
            for (; j < blank - 1; j++) std::cout << '_';
          } else {
            for (int j = 0; j < blank - 1; j++) std::cout << ' ';
          }
          std::cout << arr[i]->data;
          if (arr[i]->right) {
            int j = 0;
            for (j = 0; j < blank / 2 - 1; j++) std::cout << '_';
            for (; j < blank; j++) std::cout << ' ';
          } else {
            for (int j = 0; j < blank; j++) std::cout << ' ';
          }
        }
      }
      arr.clear();
      level++;
      std::cout << '\n';
    }
  }
};

#endif