#include<iostream>
using namespace std;
struct Node

{

     int data;

     Node * left;

     Node * right;

};

int numleft(Node * root)
{
     if (root != nullptr) {
          if (root->left == nullptr) {
               return 0;
          }
          if (root->left != nullptr) {
               return 1 + numleft(root->left);
          }
     }
     else {
          return 0;
     }
}
int main() {

     return 0;
}