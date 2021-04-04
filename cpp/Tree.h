#ifndef _TREE_NODE_
#define _TREE_NODE_

#include <iostream>
using namespace std;

class TreeNode
{
private:
    string character;
    int count;
    TreeNode *left = NULL;
    TreeNode *right = NULL;

public:
    TreeNode(string character);
    TreeNode(char character);
    ~TreeNode();

    void increaseCount();

    // get/set methods
    int getCount();
    void setCount(int newCount);
    string getChar();
    void setChar(string newChar);
    TreeNode *getLeft();
    void setLeft(TreeNode *newLeft);
    TreeNode *getRight();
    void setRight(TreeNode *newRight);
};

#endif

#ifndef _BINARY_SEARCH_TREE_
#define _BINARY_SEARCH_TREE_
#include <string>

class BinarySearchTree
{
public:
    TreeNode *root = NULL;
    void insert(TreeNode *node);   // TODO: insert a node, if the "character" of "node" does exist, then increase the "count"
    void remove(string character); // TODO: remove/delete a node having the same "character"
    int search(string character);  // TODO: return "count"
    void print();                  // TODO: print out the whole tree on the console
};

#endif