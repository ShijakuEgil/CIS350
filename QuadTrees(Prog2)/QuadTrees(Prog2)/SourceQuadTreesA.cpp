/*
Egil Shijaku
CIS 350
Program 2a*/

#include<string>
#include<iostream>
using namespace std;

const int IMG_SIZE = 32;

struct QuadNode
{
    char type;
    int level;
    QuadNode *quads[4];
};
class QuadTree
{
    QuadNode *root;
public:
    QuadTree()
    {

    }
    void frmStr(string encodeString)
    {

    }
    void printTree()
    {

    }
    void printImage()
    {

    }
    char querryTree(int row, int col)
    {

    }
    bool sameTree(QuadNode *ptr1, QuadNode *ptr2)
    {

    }
    int numBlack()
    {

    }
    int largestRepeat()
    {

    }
};