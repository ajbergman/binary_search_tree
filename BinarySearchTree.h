/**
 * Binary Search Tree Class
 * Stub written by Sorrachai Yingchareonthawornchai, 26 Sep 2014
 * Completed by Alex Bergman
 */

#ifndef BinarySearchTree_H
#define BinarySearchTree_H

#include <iostream>
using namespace std;
template<class T> class BinarySearchTree
{
    public:
    BinarySearchTree() {root = nullptr;}
    //destructor
    ~BinarySearchTree() {
        // deleteTree(root);
    }
    void display() const
    {
        int level=0;
        _display(root,level);
    }



    void insert(const T &t)
    {

        if(root == nullptr){
            root = new Node(t);
        } else {            
            Node *next = root;
            Node *current;
            while(next != nullptr){
                current = next;
                if(current->m_num > t){
                    next = current->m_ll;
                } else {
                    next = current->m_rl;
                }
            }
            if(current->m_num > t){
                current->m_ll = new Node(t);
            } else {
                current->m_rl = new Node(t);
            }
        }
    }
    void inOrderTraverse(vector<T>& vec) const
    {
        if(root != nullptr) inOrderRecursive(root, vec);
    }
    void deleteNode(const T &t)
    {
        deleteRecursive(root, t);
    }
    void forEachInterval(const T &a, const T&b, function<void (const T)> func) const
    {
        if(b < a){
            cout << "invalid range" << endl;
        }
        forEachRecursive(a, b, func, root);

    }
    void filter(function<bool (const T)> isIn)
    {
        filterRecursive(isIn, root);
        // cout << "filter" << endl;
        // vector<T> inorder;
        // inOrderTraverse(inorder);
        // for_each(begin(inorder),end(inorder),[&](const T &n){
        //     cout << n << endl;
        //     if(!isIn(n)) deleteNode(n);//deleteRecursive(root, n);
        // });
    }
    bool verifyBinarySearchTree() const
    {
        return verifyRecursive(root);
    }
    

    private:
        // class Node (you can modify,but it is not necessary)
        // The nested node class for objects in our tree.
        struct Node
        {
                friend class BinarySearchTree;

                Node() {m_ll = nullptr;  m_rl = nullptr;}

                Node(const T &t) {m_num = t;  m_ll = nullptr;  m_rl = nullptr;}
                Node(const T &t, Node * l, Node *r) : m_num{t}, m_ll{l}, m_rl{r} {}

                T &data() {return m_num;}

                const T &data() const {return m_num;}

                Node    *m_ll;
                Node    *m_rl;
                T       m_num;
        };

     Node *root;

    //internal method
    void _display(Node *p,int level) const
    {
        if (p ==nullptr) return;
        level++;
        if (p->m_rl != nullptr)
        {
            _display(p->m_rl,level);
        }
        for (int i = 0; i <= level; i++)
        {
            cout<<"    ";
        } 
        cout << "__" << p->data()<<endl;
        if (p->m_ll != nullptr)
        {
            _display(p->m_ll, level);
        }
    }
 
    // ADD private methods to help complete implementation

    void inOrderRecursive(Node *N, vector<T>& vec) const
    {
        if(N != nullptr){
            inOrderRecursive(N->m_ll, vec);
            vec.push_back(N->m_num);
            inOrderRecursive(N->m_rl, vec);
        }
    }
    bool verifyRecursive(Node *N) const
    {
        if(N == nullptr){ //no more recursion
            return true;
        } else {
            if(N->m_ll != nullptr && N->m_rl != nullptr){
                if((N->m_ll->m_num < N->m_num) && (N->m_rl->m_num > N->m_num)){

                    if( verifyRecursive(N->m_ll) && verifyRecursive(N->m_rl) ){ //recursive part
                        return true;
                    } else {
                        return false;
                    }

                } else { 
                    return false;
                }
            } else if( (N->m_ll != nullptr) || (N->m_rl != nullptr) ){
                if(N->m_ll != nullptr){
                    return ((N->m_ll->m_num < N->m_num)? true : false);

                } else {
                    return ((N->m_rl->m_num > N->m_num)? true : false);
                }

            } else {
                return true;
            }
        }
    }
    Node* smallestNode(Node *curr)
    {
        if (curr->m_ll == nullptr) return curr;
        else return smallestNode(curr->m_ll);
    }
    Node* deleteRecursive(Node *current, const T &k) 
    {
        if (current == nullptr) return nullptr;
        if ( k == current->m_num ) {
           if (current->m_ll == nullptr && current->m_rl == nullptr) return nullptr;
           if (current->m_ll == nullptr) return current->m_rl;
           if (current->m_rl == nullptr) return current->m_ll;
           
           Node *tmp = smallestNode(current->m_rl);
           current->m_num = tmp->m_num;
           current->m_rl = deleteRecursive(current->m_rl, tmp->m_num) ;
           return current;
           
        }
        else if (k < current->m_num) {
            current->m_ll = deleteRecursive(current->m_ll, k);
            return current;
        }
        else {
            current->m_rl = deleteRecursive(current->m_rl, k) ;
            return current;
        }
    }

    void forEachRecursive(const T &a, const T&b, function<void (const T)> func, Node* current) const
    {
        if (current == nullptr) return;
        if(current->m_num < a) {
            forEachRecursive(a, b, func, current->m_rl);
        } else if(current->m_num > b) {
            forEachRecursive(a, b, func, current->m_ll);
        } else if ( (current->m_num >= a) && (current->m_num <= b) ) {

            func(current->m_num);
            forEachRecursive(a, b, func, current->m_ll);
            forEachRecursive(a, b, func, current->m_rl);
           
        } else {
            cout << "#####  error  #####" << endl;
            return;
        }
    }

    Node* filterRecursive(function<bool (const T)> isIn, Node* current)
    {
        if (current == nullptr) return nullptr;
        if ( !isIn(current->m_num) ) {
           if (current->m_ll == nullptr && current->m_rl == nullptr) return nullptr;
           if (current->m_ll == nullptr) return current->m_rl;
           if (current->m_rl == nullptr) return current->m_ll;

            Node *tmp = smallestNode(current->m_rl);
            current->m_num = tmp->m_num;
            current->m_rl = deleteRecursive(current->m_rl, tmp->m_num);
            while(!isIn(current->m_num)){
                tmp = smallestNode(current->m_rl);
                current->m_num = tmp->m_num;
                current->m_rl = deleteRecursive(current->m_rl, tmp->m_num);
            }
           
        }
        current->m_ll = filterRecursive(isIn, current->m_ll);
        current->m_rl = filterRecursive(isIn, current->m_rl);
        return current;
        

    }

};


#endif
