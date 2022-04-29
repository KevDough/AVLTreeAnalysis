#ifndef AVLTREE_H
#define AVLTREE_H

using namespace std;
#include <string>
#include <iostream>

template <class T>
class AVLTree{
    public:
        class Node
        {
            public:
                Node(string key,T* data){
                    this->key = key;
                    this->data = data;
                    left = nullptr;
                    right = nullptr;
                    height = 1;
                }
                ~Node(){
                    if(left!=nullptr) delete left;
                    if(right!=nullptr) delete right;
                    delete data;
                }
                string key;
                T* data;
                Node *left;
                Node *right;
                int height;
                bool operator<(const string& other){
                    return key.compare(other)<0;
                }
                bool operator>(const string& other){
                    return key.compare(other)>0;
                }
        };
        Node* insert(Node* node, string key, T* data){
            if(node==nullptr){
                return new Node(key,data);
            }else{
                Node* insertedNode;
                if(*node<key){
                    insertedNode = insert(node->right,key,data);
                    node->right = insertedNode;
                }else{
                    insertedNode = insert(node->left,key,data);
                    node->left = insertedNode;
                }
                setHeightFromChildren(node);

                int balanceDiff = getHeight(node->left)-getHeight(node->right);
                if(balanceDiff>1){//Left unbalanced
                    if(*node->left<key){//Left-Right
                        node->left = rotateLeft(node->left);
                        return rotateRight(node);
                    }else{//Left-Left
                        return rotateRight(node);
                    }
                }else if(balanceDiff<-1){//Right unbalanced
                    if(*node->right<key){//Right-Right
                        return rotateLeft(node);
                    }else{//Right-Left
                        node->right = rotateRight(node->right);
                        return rotateLeft(node);
                    }
                }
                return node;
            }
        }

    private:
        Node* root;

        Node* rotateRight(Node * pivot){
            Node* newHead = pivot->left;
            Node* oldRight = newHead->right;

            newHead->right = pivot;
            pivot->left = oldRight;

            setHeightFromChildren(pivot);
            setHeightFromChildren(newHead);

            return newHead;
        }
        Node* rotateLeft(Node * pivot){
            Node* newHead = pivot->right;
            Node* oldRight = newHead->left;

            newHead->left = pivot;
            pivot->right = oldRight;

            setHeightFromChildren(pivot);
            setHeightFromChildren(newHead);

            return newHead;
        }
        int getHeight(Node *node){
            if(node==nullptr) return 0;
            return node->height;
        }
        void setHeightFromChildren(Node* node){
            if(node!=nullptr){
                node->height = max(getHeight(node->left),getHeight(node->right))+1;
            }
        }
        int getBalance(Node *N)
        {
            if (N == NULL)
                return 0;
            return getHeight(N->left) -
                getHeight(N->right);
        }
        Node * minValueNode(Node* node)
        {
            Node* current = node;
        
            /* loop down to find the leftmost leaf */
            while (current->left != NULL)
                current = current->left;
        
            return current;
        }
        
    public:
        AVLTree(){
            root = nullptr;
        }
        ~AVLTree(){
            delete root;
        }
        void preOrder(){
            preOrder(root,0);
        }
        void preOrder(Node *node, int space)
        {
            if (node == nullptr)
                return;
        
            // Increase distance between levels
            space += 10;
        
            // Process right child first
            preOrder(node->right, space);
        
            // Print current node after space
            // count
            cout<<endl;
            for (int i = 10; i < space; i++)
                cout<<" ";
            cout<<node->key<<"("<<*node->data<<")\n";
        
            // Process left child
            preOrder(node->left, space);
        }
        
        void insert(string key, T* data){
            root = insert(root,key,data);
            
        }

        Node* removeNode(Node* node, string key){
            if(node==nullptr) return node;

            if ( *node>key )
                node->left = removeNode(node->left, key);
            else if( *node<key )
                node->right = removeNode(node->right, key);
            else
            {
                if( (node->left == nullptr) || (node->right == nullptr) )
                {
                    Node *temp = node->left ?
                                node->left :
                                node->right;
        
                    if (temp == nullptr)
                    {
                        temp = node;
                        node = nullptr;
                    }
                    else *node = *temp; 
                    delete temp;
                }
                else
                {
                    Node* temp = minValueNode(node->right);
                    node->key = temp->key;
                    node->right = removeNode(node->right,
                                            temp->key);
                }
            }
            if (node == NULL)
            return node;
            setHeightFromChildren(node);

            int balance = getBalance(node);
        
            // Left Left Case
            if (balance > 1 && getBalance(node->left) >= 0)
                return rotateRight(node);
        
            // Left Right Case
            if (balance > 1 &&
                getBalance(node->left) < 0)
            {
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
        
            // Right Right Case
            if (balance < -1 &&
                getBalance(node->right) <= 0)
                return rotateLeft(node);
        
            // Right Left Case
            if (balance < -1 &&
                getBalance(node->right) > 0)
            {
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
        
            return node;
        }

        

        void remove(string key){
            root = removeNode(root,key);
        }
        T* get(string key){
            Node* start = root;
            while(start!=nullptr && start->key!=key){
                if(*start<key){
                    start=start->right;
                }else{
                    start=start->left;
                }
            }
            return (start==nullptr) ? nullptr : start->data;
        }
        bool has(string key){
            return get(key)!=nullptr;
        }     
};


#endif