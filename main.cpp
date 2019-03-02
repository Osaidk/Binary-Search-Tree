// Sample driver
// EE 312 Fall 2018
//
// The BST should work for any data type or object.
// Other user created objects must have the << operator overloaded for 
// output.
//

#include <iostream>
#include <fstream>
#include "BST312.h"
#include <cstdlib>


using namespace std;

template <typename T>
void print(vector<T> vec){
    for(int i = 0 ; i < vec.size() ; i++){
        cout << vec[i] << endl;
    }
}

template <typename T>
void Sum(vector <T> vec){
    int sum=0;
    for (int i=0; i< vec.size(); i++){
        sum+=stoi(vec[i]);
    }
    cout << sum << endl;
}
int main() {

    ifstream inFile;
    inFile.open("test.txt");

    BST_312<string> bst;

    string s;
    inFile >> s;
    while (inFile) {
        cout << "inserting ... " << s << endl;
        bst.insertItem(s);
        inFile >> s;
    }

    cout << "postorder traversal is " << endl;
    print(bst.postOrderTraversal());
    cout << endl;

    cout << "preorder traversal is " << endl;
    print(bst.preOrderTraversal());
    cout << endl;

    cout << "inorder traversal is " << endl;
    print(bst.inOrderTraversal());
    cout << endl;

    cout << "Remove items " << endl;
    cout << "number of nodes in tree before delete is " << bst.countNodes() << endl;
    s = "2";
    bst.deleteItem(s);
    print(bst.preOrderTraversal());
    cout << endl;
    cout << "number of nodes in tree after delete is " << bst.countNodes() << endl;
    cout << endl;
/*
    cout << "making the tree empty!" << endl;
    bst.makeEmpty();
    print(bst.preOrderTraversal());
*/
    s = "Elaf";
    cout << "checking item availability ";
    int i = bst.isItemInTree(s);
    cout << i << endl;

    Sum(bst.sumRecursive());

}

