
/*  BST312.h
  CS 312 Fall 2018

  a simple implementation of a binary search tree


*/

#ifndef BST_312_H
#define BST_312_H

#include <cstdlib>  // Provides size_t
#include <iostream>
#include <vector>

using namespace std;

template<class ItemType>
class BST_312 {
public:

    BST_312();

    //Copy constructor
    BST_312(const BST_312 & src);

    ~BST_312();

/****************************
makeEmpty

Function: Removes all the items from the BST.
Preconditions: BST has been initialized
Postconditions: All the items have been removed
*****************************/
    void makeEmpty();

/****************************
isEmpty

Function: Checks to see if there are any items in the BST.
Preconditions: BST has been initialized
Postconditions: Returns true if there are no items in the BST, else false.
*****************************/
    bool isEmpty() const;

/****************************
isFull

Function: Determines if you have any more room to add items to the BST
Preconditions: BST has been initialized
Postconditions: Returns true if there is no more room to add items, else false
*****************************/
    bool isFull() const;

/****************************
insertItem

Function: Adds newItem to the BST.
Preconditions: BST has been initialized and is not full.
Postconditions: newItem is in the proper position for a BST.
*****************************/
    void insertItem(const ItemType &);

/****************************
deleteItem

Function: Removes target from BST.
Preconditions: BST has been initialized.
Postconditions: If found, element has been removed from BST.
*****************************/
    void deleteItem(const ItemType& newItem);

/****************************
countNodes

Function: Counts the number of nodes in the BST
Preconditions: BST has been initialized.
Postconditions: returns the number of nodes in the BST
*****************************/
    int countNodes();

/****************************
preOrderTraversal

Function: Returns the preOder (Node, Left, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> preOrderTraversal();

/****************************
inOrderTraversal

Function: Returns the inOder (Left, Node, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> inOrderTraversal();

/****************************
postOrderTraversal

Function: returns the postOder (Left, Right, Node) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> postOrderTraversal();

/********************
 isItemInTree

Function: Determines if a given Item is in tree.
Preconditions: BST has been initialized.
Postconditions: none
*****************************/

    bool isItemInTree(const ItemType& item);

    vector<ItemType>  sumRecursive();

private:
    struct TreeNode {
        ItemType data;
        TreeNode *left;
        TreeNode *right;
    };

    TreeNode * root;


    void insertItem(TreeNode*& t, const ItemType& newItem);
    void inOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    int countNodes(TreeNode* t) const;
    void deleteNode(TreeNode*& node);
    void makeEmpty(TreeNode*& t);
    void deleteItem(TreeNode*& t, const ItemType& newItem);
    void getPredecessor(TreeNode* t, ItemType& data);
    void preOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    void postOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    void copyTree(TreeNode*& copy, const TreeNode *originalTree);
    void sumRecursive(TreeNode* temp, vector<ItemType>& sum);

};


//Function implementations


template<class ItemType>
BST_312<ItemType>::BST_312 ()
{
    root = NULL;
}

template<class ItemType>
BST_312<ItemType>::BST_312(const BST_312 & src)
{
    copyTree(root, src.root);
}

template<class ItemType>
BST_312<ItemType>::~BST_312()
{
    makeEmpty();

}


template<class ItemType>
void BST_312<ItemType>::copyTree(TreeNode*& copy, const TreeNode* originalTree)
{
    if (originalTree == NULL)
        copy = NULL;
    else
    {
        copy = new TreeNode;
        copy->data = originalTree->data;

        copyTree(copy->left, originalTree->left);
        copyTree(copy->right, originalTree->right);
    }
}


template<class ItemType>
void BST_312 <ItemType>::deleteNode(TreeNode*& t)
{
    ItemType info;
    TreeNode *tempPtr;

    tempPtr = t;

    if (t->left == NULL)
    {
        t = t->right;
        delete tempPtr;
    }
    else if (t->right == NULL)
    {
        t = t->left;
        delete tempPtr;
    }
    else
    {
        getPredecessor(t->left, info);
        t->data = info;
        deleteItem(t->left, info);
    }
}



//find largest in left subtree
template<class ItemType>
void BST_312 <ItemType>::getPredecessor(TreeNode* t, ItemType& data)
{

    while (t->right != NULL)
        t = t->right;

    data = t->data;

}


template<class ItemType>
void BST_312 <ItemType>::deleteItem(TreeNode*& t, const ItemType& newItem)
{
    if (t == NULL)
        return;
    else if (newItem < t->data)
        deleteItem(t->left, newItem);
    else if (newItem > t->data)
        deleteItem(t->right, newItem);
    else
        deleteNode(t);
}


template<class ItemType>
void BST_312 <ItemType>::deleteItem(const ItemType& newItem)
{
    deleteItem(root, newItem);

}

template<class ItemType>
void BST_312 <ItemType>::makeEmpty(TreeNode*& t)
{
    if (t!=NULL){
        if (t->left!=NULL){
            makeEmpty(t->left);
        }
        if (t->right!=NULL){
            makeEmpty(t->right);
        }
        delete t;
    }
}

template<class ItemType>
void BST_312 <ItemType>::makeEmpty()
{
    makeEmpty(root);
    root = NULL;
}

template<class ItemType>
bool BST_312 <ItemType>::isEmpty() const
{
    return root == NULL;
}



template<class ItemType>
bool BST_312 <ItemType>::isFull() const
{
    try
    {
        TreeNode *temp = new TreeNode;
        delete temp;
        return false;
    }
    catch (std::bad_alloc)
    {
        return true;
    }

}


template<class ItemType>
void BST_312 <ItemType>::insertItem(TreeNode*& t, const ItemType& newItem) {
   TreeNode* current = NULL;
   if (t==NULL){
       t=new TreeNode;
       t->data=newItem;
       t->left=NULL;
       t->right=NULL;
       root=t;
       return;
   }

   while (t!=NULL){
       current = t;
       if (newItem < t->data){ t=t->left;}
       else  t=t->right;
   }

    TreeNode* newNode = new TreeNode;
    newNode -> data = newItem;
    newNode -> left = NULL;
    newNode -> right = NULL;

    if (current->data > newItem){
       current->left=newNode;
    }
    else{
        current->right=newNode;
    }

    /*   if (t==NULL) {
           t = new TreeNode;
           t->data = newItem;
           t->left = NULL;
           t->right = NULL;
       }
       else {
           if (t->data > newItem) {
               insertItem(t->left, newItem);
           }
           else if (t->data < newItem){
               insertItem(t->right,newItem);
           }

       }

   }
     */
}
template<class ItemType>
void BST_312 <ItemType>::insertItem(const ItemType &newItem) {
    TreeNode* temp=root;
    insertItem(temp, newItem);
}



template<class ItemType>
int BST_312 <ItemType>::countNodes(TreeNode* t) const
{
  int num=0;
  if (t!=NULL){
      num++;
      if (t->left!=NULL){
          num+=countNodes(t->left);
      }
      if (t->right!=NULL){
          num+=countNodes(t->right);
      }
  }
    return num;
}


template<class ItemType>
int BST_312 <ItemType>::countNodes()
{
    TreeNode* temp=root;
    int num=countNodes(temp);
    return num;
}

template<class ItemType>
void BST_312 <ItemType>::preOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{

    if (t!=NULL) {
        result.push_back(t->data);
        preOrderTraversal(t->left,result);
        preOrderTraversal(t->right,result);
    }
}


template<class ItemType>
vector<ItemType> BST_312 <ItemType>::preOrderTraversal()
{
    vector<ItemType> string;
    TreeNode* temp=root;
    preOrderTraversal(temp,string);
    return string;
}

template<class ItemType>
void BST_312 <ItemType>::inOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
   if (t!=NULL){
       inOrderTraversal(t->left, result);
       result.push_back(t->data);
       inOrderTraversal(t->right, result);

   }

}

template<class ItemType>
vector<ItemType> BST_312 <ItemType>::inOrderTraversal()
{
    vector<ItemType> string;
    TreeNode *temp=root;
    inOrderTraversal(temp,string);
    return string;
}

template<class ItemType>
void BST_312 <ItemType>::postOrderTraversal(TreeNode* t,vector<ItemType>& result) const {

    if (t!=NULL) {
        postOrderTraversal(t->left, result);
        postOrderTraversal(t->right, result);
        result.push_back(t->data);
    }
}

template<class ItemType>
vector<ItemType> BST_312 <ItemType>::postOrderTraversal()
{
    vector<ItemType> string;
    TreeNode* temp=root;
    postOrderTraversal(temp,string);
    return string;
}

template<class ItemType>
bool BST_312 <ItemType>::isItemInTree(const ItemType& item)
{
    int NOT_FOUND=1;
    TreeNode* temp=root;
    if (temp != NULL) {
        if (temp->data == item) {
            return true;
        }
        else {
            while (NOT_FOUND) {
                if (item < temp->data) {
                    if (temp->left==NULL) {
                        NOT_FOUND=0;
                    }
                    else {
                        temp=temp->left;
                    }
                }
                else {
                    if (temp->right==NULL) {
                        NOT_FOUND=0;
                    }
                    else {
                        temp=temp->right;
                    }
                }
                if (temp->data==item) {
                    return true;
                }
            }
        }
    }

    return false;
}

template<class ItemType>
vector<ItemType> BST_312<ItemType>::sumRecursive() {
    vector<ItemType> sum;
    TreeNode* temp= root;
    sumRecursive(temp, sum);
    return sum;
}


template<class ItemType>
void BST_312<ItemType>::sumRecursive(TreeNode *temp, vector<ItemType>& sum) {
    if ( temp !=NULL) {
        sumRecursive(temp->left,sum);
        sumRecursive(temp->right,sum);
        sum.push_back(temp->data);
    }
}


#endif

