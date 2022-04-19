#include <iostream>

using namespace std;

struct nodeBST
{
	nodeBST* left;
	nodeBST* right;
	nodeBST* parent;
	int value;
	int level;

};

int wysokosc=0;

void insertBST(nodeBST*& root, int valueToAdd)
{
	nodeBST* nodeToAdd = new nodeBST;
	nodeToAdd->value = valueToAdd;
	nodeToAdd->parent = NULL;
	nodeToAdd->left = NULL;
	nodeToAdd->right = NULL;

	nodeBST* pom;
	if (!root) 
	{
		root = nodeToAdd;
	}
	else
	{
		pom = root;
		while (1)
		{
			if (nodeToAdd->value < pom->value) 
				if (!pom->left) 
				{
					pom->left = nodeToAdd;
					break;
				}
				else
					pom = pom->left; 

			else 
			{
				if (!pom->right) 
				{
					pom->right = nodeToAdd;
					break;
				}
				else
					pom = pom->right; 
			}
		}
		nodeToAdd->parent = pom;
	}
}
void maxBTS(nodeBST* root)
{
	if (root)
	{
		if (root->left)
		{
			root->left->level = root->level + 1;
		}

		if (root->right)
		{
			root->right->level = root->level + 1;
		}

		wysokosc = root->level;
	
		maxBTS(root->left);
		maxBTS(root->right);
	}
}
/*int maxBTS(nodeBST* root)
{
	if (root == NULL)
		return 0;
	else
	{
		int lewo = maxBTS(root->left);
		int prawo = maxBTS(root->right);
		if (lewo > prawo)
			return(lewo + 1);
		else return(prawo + 1);
	}
}*/

int main()
{
	nodeBST* root = NULL;
	nodeBST* pom;

	int n;
	cin >> n;
	for (int i = 0; i < n; i++) 
	{
		int liczba;
		cin >> liczba;
		insertBST(root, liczba);
	}
	maxBTS(root);
	cout<< wysokosc;
}