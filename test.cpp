#include "myBST.h"

void generateTree(BST<int>* &p, int lo, int hi) {
  if(lo == hi - 1) {
    p->insert((lo+hi)/2);
    return;
  }
  p->insert((lo+hi)/2);
  p->printDetailedTree();
  generateTree(p, lo, (lo+hi)/2);
  generateTree(p, (lo+hi)/2, hi);
}
int main() {
  BST<int> *myBST = new BST<int>;
  generateTree(myBST, 0, 15);
  myBST->printDetailedTree();
  myBST->remove(4);
  myBST->printDetailedTree();
  myBST->remove(5);
  myBST->printDetailedTree();
  myBST->remove(6);
  myBST->printDetailedTree();
  myBST->remove(15);
  myBST->printDetailedTree();
  myBST->remove(14);
  myBST->printDetailedTree();
  for (int i = 0; i < 15; i++) {
    myBST->printDetailedTree();
    myBST->remove(i);
  }
  return 0;
}