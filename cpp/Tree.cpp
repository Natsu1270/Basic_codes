#include <iostream>
#include <string>
#include "Tree.h"
using namespace std;

TreeNode::TreeNode(string character)
{
    this->character = character;
    this->count = 1;
}

TreeNode::TreeNode(char character)
{
    this->character = character;
    this->count = 1;
}

TreeNode::~TreeNode()
{
    this->character = "";
    this->count = 0;
    setLeft(NULL);
    setRight(NULL);
}

void TreeNode::increaseCount()
{
    this->count += 1;
}

int TreeNode::getCount()
{
    return this->count;
}

void TreeNode::setCount(int count)
{
    this->count = count;
}

string TreeNode::getChar()
{
    return this->character;
}

void TreeNode::setChar(string newChar)
{
    this->character = newChar;
}

TreeNode *TreeNode::getLeft()
{
    return this->left;
}

TreeNode *TreeNode::getRight()
{
    return this->right;
}

void TreeNode::setLeft(TreeNode *newLeft)
{
    this->left = newLeft;
}

void TreeNode::setRight(TreeNode *newRight)
{
    this->right = newRight;
}

TreeNode *insertBSTRec(TreeNode *root, TreeNode *node)
{
    if (node == NULL)
        return root;
    if (root == NULL)
        return node;

    if (node->getChar().compare(root->getChar()) == 0)
    {
        root->setCount(root->getCount() + 1);
        return root;
    }
    if (node->getChar().compare(root->getChar()) < 0)
    {
        if (root->getLeft() == NULL)
            root->setLeft(node);
        else
        {
            insertBSTRec(root->getLeft(), node);
        }
    }
    if (node->getChar().compare(root->getChar()) > 0)
    {
        if (root->getRight() == NULL)
            root->setRight(node);
        else
        {
            insertBSTRec(root->getRight(), node);
        }
    }
    return root;
}
void BinarySearchTree::insert(TreeNode *node)
{
    this->root = insertBSTRec(this->root, node);
}

TreeNode *findDeadRight(TreeNode *root)
{
    TreeNode *t = root;
    while (t->getRight() != NULL)
    {
        t = t->getRight();
    }
    return t;
}

void removeBSTRec(TreeNode *root, string character)
{
    if (root == NULL)
        return;

    if (root->getChar().compare(character) == 0)
    {
        delete root;
        return;
    }

    if (root->getChar().compare(character) < 0)
    {
        TreeNode *deleteNode = root->getRight();
        if (deleteNode->getChar().compare(character) == 0)
        {
            if (deleteNode->getLeft() == NULL)
            {
                root->setRight(deleteNode->getRight());
                delete deleteNode;
                return;
            }
            if (deleteNode->getRight() == NULL)
            {
                root->setRight(deleteNode->getLeft());
                delete deleteNode;
                return;
            }
            TreeNode *leftNode = deleteNode->getLeft();
            if (leftNode->getRight() == NULL)
            {
                leftNode->setRight(deleteNode->getRight());
                root->setRight(leftNode);
                delete deleteNode;
                return;
            }
            else
            {
                TreeNode *rightDead = findDeadRight(leftNode);
                rightDead->setRight(deleteNode->getRight());
                root->setRight(leftNode);
                delete deleteNode;
                return;
            }
        }
        removeBSTRec(root->getRight(), character);
    }

    if (root->getChar().compare(character) > 0)
    {
        TreeNode *deleteNode = root->getLeft();
        if (deleteNode->getChar().compare(character) == 0)
        {
            if (deleteNode->getLeft() == NULL)
            {
                root->setLeft(deleteNode->getRight());
                delete deleteNode;
                return;
            }
            if (deleteNode->getRight() == NULL)
            {
                root->setLeft(deleteNode->getLeft());
                delete deleteNode;
                return;
            }
            TreeNode *leftNode = deleteNode->getLeft();
            if (leftNode->getRight() == NULL)
            {
                leftNode->setRight(deleteNode->getRight());
                root->setLeft(leftNode);
                delete deleteNode;
                return;
            }
            else
            {
                TreeNode *rightDead = findDeadRight(leftNode);
                rightDead->setRight(deleteNode->getRight());
                root->setLeft(leftNode);
                delete deleteNode;
                return;
            }
        }
        removeBSTRec(root->getLeft(), character);
    }
}

void BinarySearchTree::remove(string character)
{
    removeBSTRec(this->root, character);
}

int searchBSTRec(TreeNode *root, string character)
{
    if (root == NULL)
    {
        return 0;
    }
    if (root->getChar().compare(character) == 0)
    {
        return root->getCount();
    }
    if (root->getChar().compare(character) < 0)
    {
        return searchBSTRec(root->getRight(), character);
    }
    if (root->getChar().compare(character) > 0)
    {
        return searchBSTRec(root->getLeft(), character);
    }
    // return root->getCount();
}

int BinarySearchTree::search(string character)
{
    return searchBSTRec(this->root, character);
}

void printLNR(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    if (root->getLeft() != NULL)
    {
        cout << "(";
        printLNR(root->getLeft());
        cout << ")";
    }
    cout << root->getChar();
    if (root->getRight() != NULL)
    {
        cout << "(";
        printLNR(root->getRight());
        cout << ")";
    }
}

void BinarySearchTree::print()
{
    printLNR(this->root);
    cout << endl;
}

TreeNode *loopInsert(TreeNode *root, TreeNode *newNode)
{
    TreeNode *t = root;
    while (t)
    {
        if (newNode->getChar().compare(t->getChar()) < 0)
        {
            if (t->getLeft() == NULL)
            {
                t->setLeft(newNode);
                return root;
            }
            t = t->getLeft();
        }
        else
        {
            if (t->getRight() == NULL)
            {
                t->setRight(newNode);
                return root;
            }
            t = t->getRight();
        }
    }
    return root;
}

void printPath(TreeNode *root, string c)
{
    TreeNode *t = root;
    while (t)
    {
        cout << t->getChar() << endl;
        if (c.compare(t->getChar()) == 0)
        {
            return;
        }
        if (c.compare(t->getChar()) < 0)
        {
            t = t->getLeft();
        }
        else
        {
            t = t->getRight();
        }
    }
    cout << "Can not find character" << endl;
}

void printLeavesBFT(TreeNode *root)
{
}

BinarySearchTree *buildTreeFromString(string str)
{
    BinarySearchTree *bst = new BinarySearchTree();
    for (int i = 0; i < str.length(); ++i)
    {
        TreeNode *newNode = new TreeNode(str.at(i));
        bst->insert(newNode);
    }
    return bst;
}

bool checkIsBST(TreeNode *root)
{
    if (root == NULL)
        return true;
    if (root->getLeft() == NULL)
        return true;
    if (root->getRight() == NULL)
        return true;
    if (root->getLeft()->getChar().compare(root->getRight()->getChar()) > 0)
    {
        return false;
    }
    return checkIsBST(root->getLeft()) && checkIsBST(root->getRight());
}

int main()
{
    BinarySearchTree *bst = new BinarySearchTree();
    bst->insert(new TreeNode("m"));
    bst->insert(new TreeNode("e"));
    bst->insert(new TreeNode("x"));

    cout << checkIsBST(bst->root) << endl;

    return 0;
}