//
// Written by Sorrachai Yingchareonthawornchai, 26 Sep 2014
//
// Name :        main.cpp
// Description : Main program that reads an input file and builds a binary search tree.
//

#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include "Tree.h"                // Edit your code for BST implementation in this file

using namespace std;


int main() {
    // load vector from file
    ifstream is("numbers_small.txt");
    istream_iterator<int> s(is), e;
    vector<int> x(s, e);
    cout << "Read " << x.size() << " numbers" << endl;

    BinarySearchTree<int> tree1,tree2,tree3;

    for_each(begin(x),end(x),[&](int n) {
            tree1.insert(n); //edit your insert code in Tree.h
            tree2.insert(n); //edit your insert code in Tree.h
            tree3.insert(n); //edit your insert code in Tree.h
     });

    cout << "The tree has been created";
    cout << " and it is " << (tree1.verifyBinarySearchTree()?"":"not ") << "a binary search tree" << endl;
    cout << "Display tree1 "<< endl;
    tree1.display();
    
    vector<int> inorder;
    tree1.inOrderTraverse(inorder);         // edit your inorder traversal code in Tree.h

    cout << "show output of traversal" <<endl;
    for_each(begin(inorder),end(inorder),[](int n){
            cout << n << " ";
     });
        
    cout << endl;

     for_each(begin(x),end(x),[&tree1](int n) {
            if(n%2 ==0) tree1.deleteNode(n); // edit your deleteNode code in Tree.h
    });
     

    cout << "Tree1's nodes that are even are deleted. The resultant tree1 is " << (tree1.verifyBinarySearchTree()?"":"not ") << "a binary search tree" << endl;
    cout << "Display this modified tree" <<endl;
    tree1.display();
    
    tree2.filter([](int n) {  //edit your filter code in Tree.h
            if(n%3 !=0) return 1; 
            return 0;
        }); //basically, delete nodes that are divisible by 3.

    cout << "Tree2's nodes that are divisible by 3 are deleted. The resultant tree2 is " << (tree2.verifyBinarySearchTree()?"":"not ") << "a binary search tree" << endl;
    cout << "Display filtered tree2" << endl;
    tree2.display();

    cout << "Display tree3 " <<endl;
    tree3.display();
     
    cout << "Printing members of tree3 whose elements are in range [5,30]" << endl;
    tree3.forEachInterval(5,30,[](int n) { //edit your forEachInterval in tree.h
            cout << n << " ";
        });
    cout << endl;
    
    
    cout << "In summary: "<< endl;
    cout << "This is tree1:" <<endl;
    tree1.display();
    cout << "This is tree2:" <<endl;
    tree2.display();
    cout << "This is tree3:" <<endl;
    tree3.display();
    
    return 0;
}
