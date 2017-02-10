#include<iostream>
#include<string>
using namespace std;

struct Node
{
    char type;
    int level;
    Node * quad[4];
};
void insert(Node * & root, char item)
{
    if (root == nullptr)
    {

    }
}


int main()
{
    Node * newNode = new Node;

    newNode->type = 'i';
    newNode->level = 0;
    for (auto x : newNode->quad)
    {
	   x = nullptr;
    }

    return 0;
}