/*
Egil Shijaku
CIS 350
Program 2a*/

#include<string>
#include<iostream>
#include<iomanip>
using namespace std;

const int IMG_SIZE = 64;
struct QuadNode
{
    char type;
    int level;
    QuadNode * quads[4];
    QuadNode(char tp =' ', int lvl = 0) 
    {
	   type = tp;
	   level = lvl;
	   for(int i = 0; i < 4; i++)
		  quads[i] = nullptr;
    }
    void set()
    {
	   for (int i = 0; i < 4; i++)
	   {
		  quads[i] = new QuadNode;
	   }
    }
};

class QuadTree
{
    QuadNode * root;
    bool checkQuads = false;

    void insertIn2Tree(QuadNode * & ptr, char letter, int lvl)
    {   
	   if (ptr == nullptr)
	   { 
		  ptr = new QuadNode(letter, lvl);  
		  checkQuads = true;
	   }
	   if (ptr != nullptr && ptr->type == 'i')
	   {
		  int count = 0;
		  while (checkQuads == false && count < 4)
		  {
			 if (checkQuadPtr(ptr->quads[count]))
				insertIn2Tree(ptr->quads[count], letter, lvl + 1);

			 count++;
		  }
	   }
    }
    bool checkQuadPtr(QuadNode * node)
    {
	   if (node == nullptr)
		  return true;
	   else
	   {
		  if (node->type == 'i')
			 return true;
		  else
			 return false;
	   }
    }
    void printTree(QuadNode * ptr)
    {
	   if (ptr != nullptr)
	   {
		  cout << setw(ptr->level * 5) << ptr->type << " " << ptr->level << endl;

		  for (int i = 3; i >= 0; i--)
		  {
			 printTree(ptr->quads[i]);
		  }
	   }
    }
public:
    QuadTree()
    {
	   root = nullptr;
    }

    void insertIn2Tree(char letter)
    {
	   checkQuads = false;
	   insertIn2Tree(root, letter, 0);
	   
    }

    void frmStr(string encodeString)
    {
	   if (!encodeString.empty())
	   {
		  for (auto letter : encodeString)
		  {
			 //cout << letter << " ";
			 insertIn2Tree(letter);
		  }
	   }
    }

    void printTree()
    {
	   printTree(root);
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

int main()
{
    string input;
    cin >> input;
    QuadTree tree;
    tree.frmStr(input);  
    tree.printTree();
 
    return 0;
}