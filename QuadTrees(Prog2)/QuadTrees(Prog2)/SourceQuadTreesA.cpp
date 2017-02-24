/*
Egil Shijaku
CIS 350
Program 2a
Prof. Bruce Elenbogen
*/
/*
DESCRIPTION
The purpose of the QuadTree program is to decode an encoded string of characters into a 
64x64 pixel white and black "photo". The string that is going to be the program's input will 
consist of the characters i,w,b only. The string is also expected to be the pre-order of the 
"photo" data that is stored in the tree.
The character i is going to represent an interior node, and the characters w and b are going 
to represent the white and black pixel respectively and also will be leafs of the tree whom 
are going to represent the color of the spatial unit represented.
The program will construct the Quad tree from the pre-ordered input than go through the each 
node given in the tree and output the picture encoded.
*/

#include<string>
#include<iostream>
#include<iomanip>
#include<algorithm>
using namespace std;

//const int IMG_SIZE = 32;
const char BLACK = '@';
const char WHITE = ' ';
const char NODE = 'i';
const char B_LEAF = 'b';
const char W_LEAF = 'w';
struct QuadNode
{
    char type;
    int level;
    QuadNode * quads[4];
    QuadNode(char tp = ' ', int lvl = 0) 
    {/*Purpose: Constructor gives default values
			 to the data of the class when created
			 and sets the 4 pointers to nullptr.*/
	   type = tp;
	   level = lvl;
	   for(int i = 0; i < 4; i++)
		  quads[i] = nullptr;
    }
};

class QuadTree
{
    QuadNode * root;
    int imgSize;
    bool checkQuads = false; /*boolean variable gets true only 
					    when current node is inserted in the 
					    Quad tree. */
    char** picture;
    int numBlackPx = 0;
    QuadNode * largestSubtree = nullptr;

    void frmStr(QuadNode * & ptr, char letter, int lvl)
    {   /*Purpose:	Inserts QuadNode instances in the tree.
				Also it is a helper function so recursive
				calls are performed.*/
	   if (ptr == nullptr)
	   { 
		  ptr = new QuadNode(letter, lvl);  
		  checkQuads = true;
	   }
	   if (ptr != nullptr && ptr->type == NODE)
	   {
		  int count = 0;
		  while (checkQuads == false && count < 4)
		  {
			 if (checkQuadPtr(ptr->quads[count]))
				frmStr(ptr->quads[count], letter, lvl + 1);

			 count++;
		  }
	   }
    }
    bool checkQuadPtr(QuadNode * node)
    {
    	/*Purpose: Checks the availability of node to insert
			 new node*/
	   if (node == nullptr)
		  return true;
	   else
	   {
		  if (node->type == NODE)
			 return true;
		  else
			 return false;
	   }
    }

    void querryTree(int row, int col, QuadNode * ptr ,int rowCheck , int colCheck)
    {
	   int quadRow = rowCheck;
	   int quadCol = colCheck;
	   if (ptr != nullptr)
	   {
		  if (ptr->type != NODE)
		  {
			 if (ptr->type == W_LEAF)
			 {
				picture[row][col] = WHITE;
			 }
			 if (ptr->type == B_LEAF)
			 {
				numBlackPx++;
				picture[row][col] = BLACK;
			 }
		  }
		  else
		  {
			 int quadrantLoc = -1;
			 for (int i = 0; i < 4; i++)
			 {
				if (checkSpatialInfo(row, col, i, ptr->quads[i]->level, quadRow, quadCol))
				{
				    quadrantLoc = i;
				}
			 }
			 if (quadrantLoc != -1)
			 {
				querryTree(row, col, ptr->quads[quadrantLoc], quadRow, quadCol);
			 }
		  }
	   }
    }

    bool checkSpatialInfo(int row, int col, int index, int level, int & checkRow, int & checkCol) 
    {
	   int quadrantResolution = imgSize / (pow(2, level));
	   if (index == 0)
	   {
		  if ((row >= checkRow && row < checkRow + quadrantResolution) &&
			 (col >= checkCol && col < checkCol + quadrantResolution))
		  {
			 return true;
		  }
		  else
			 return false;
	   }
	   if (index == 1)
	   {
		  if ((row >= checkRow + quadrantResolution && row < checkRow + 2 * quadrantResolution)
			 && (col >= checkCol && col < checkCol + quadrantResolution))
		  {
			 checkRow = checkRow + quadrantResolution;
			 return true;
		  }
		  else
			 return false;
	   }
	   if (index == 2)
	   {
		  if ((row >= checkRow + quadrantResolution && row < checkRow + 2 * quadrantResolution)
			 && (col >= checkCol + quadrantResolution && col < checkCol + 2 * quadrantResolution))
		  {
			 checkRow = checkRow + quadrantResolution;
			 checkCol = checkCol + quadrantResolution;
			 return true;
		  }
		  else
			 return false;
	   }
	   if (index == 3)
	   {
		  if ((row >= checkRow && row < checkRow + quadrantResolution)
			 && (col >= checkCol + quadrantResolution && col < checkCol + 2 * quadrantResolution))
		  {
			 checkCol = checkCol + quadrantResolution;
			 return true;
		  }
		  else
			 return false;
	   }
	   else
	   {
		  return false;
	   }
    }

    int largestRepeat(QuadNode * ptr)
    {   
	   if( ptr != nullptr)
	   {
		  if (ptr->type != NODE && ptr->level == 0)
			 return 0;
		 if(ptr->type == NODE)
		 {
			 for(int i = 0; i < 4; i++)
			 {
				 for(int j = i+1; j < 4; j++)
				 {
					 if(sameTree(ptr->quads[i], ptr->quads[j]))
					 {
						return imgSize / pow(2, ptr->quads[i]->level);
					 }
				 }
			  if(ptr->quads[i]-> type == NODE)
			  {
				 return largestRepeat(ptr->quads[i]);
			  }
			 }
		 }
	   }
    }

    void printTree(QuadNode * ptr) const
    {/*Purpose: Also a helper function so recursive 
			 calls can be performed in order to print 
			 all nodes in tree. */
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
    QuadTree(int imageSize)
    {
	   imgSize = imageSize;
	   picture = new char *[imgSize];
	   for (int i =0; i< imgSize; i++)
	   {
		  picture[i] = new char[i];
	   }
	   root = nullptr;// root node initialized to nullptr so no error are thrown
    }

    void frmStr(string encodeString)
    {
	   if (!encodeString.empty())
	   {
		  for (auto letter : encodeString)
		  {
			 checkQuads = false;/* sets checkQuads to false every time a new node with
							   a new letter is inserted to the tree. CheckQuads is 
							   set to true if and only if  new node is inserted into
							   the tree.*/
			 frmStr(root, letter, 0);
		  }
	   }
    }

    void printTree()const
    {
	   printTree(root);
    }
    void printImage()
    {
	   for (int i = 0; i < imgSize; i++)
	   {
		  for (int j = 0; j < imgSize; j++)
		  {
			 cout << picture[j][i];
		  }
		  cout << endl;
	   }
    }

    void querryTree()
    {
	   for (int i = 0; i < imgSize; i++)
	   {
		  for (int j = 0; j < imgSize; j++)
		  {
			 querryTree(j, i, root, 0, 0);
		  }
	   }
    }

    bool sameTree(QuadNode *ptr1, QuadNode *ptr2)
    {

	   if(ptr1->type == ptr2->type && ptr1->type != NODE)
	   {
		  return true;
	   }
	   if (ptr1->type == ptr2->type && ptr1->type == NODE)
	   {
		  bool checkMatch = true;
		  int i = 0;
		  while (checkMatch == true && i < 4)
		  {
			 checkMatch = sameTree(ptr1->quads[i], ptr2->quads[i]);
			 i++;
		  }
		  return checkMatch;
	   }
	   else
		  return false;
	   /*if(ptr1->type == NODE && ptr2->type == NODE)
	   {
		  bool checkMatch = true;
		  int i = 0;
		  while(checkMatch == true && i < 4)
		  {
			 checkMatch = sameTree(ptr1->quads[i], ptr2->quads[i]);
			 i++;
		  }
		  return checkMatch;
	   }
	   if(ptr1->type != NODE && ptr2->type == NODE)
	   {
		 bool checkMatch = true;
		 int i = 0;
		 while(checkMatch ==  true && i < 4)
		 {
			checkMatch = sameTree(ptr1, ptr2->quads[i]);
			i++;
		 }
		 return checkMatch;
	   }
	   if(ptr1->type == NODE && ptr2->type != NODE)
	   {
		  bool checkMatch = true;
		  int i = 0;
		  while (checkMatch == true && i < 4)
		  {
			 checkMatch = sameTree(ptr1->quads[i], ptr2);
			 i++;
		  }
		  return checkMatch;
	   }
	   if(ptr1->type != NODE && ptr2->type != NODE)
	   {
		  if (ptr1->type == ptr2->type)
			 return true;
		  else
			 return false;
	   }*/
    }

    int  numBlack() const
    {
	   return numBlackPx;
    }

    int largestRepeat()
    {
	   return largestRepeat(root);
    }

};

int main()
{
    string input;
    int imgSize;
    cin >> imgSize >> input;
    QuadTree tree(imgSize);
    tree.frmStr(input);  
    //tree.printTree();
    tree.querryTree();
    tree.printImage();
    cout << tree.numBlack()<<" " << tree.largestRepeat()<<endl;
 
    return 0;
}