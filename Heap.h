#ifndef HEAP_H
#define HEAP_H

#include "AVLTree.h"
#include <string>
#include <iostream>

using namespace std;


//T needs the following operations overloaded:
//   +=  < ==

template <class T>
class Heap{
    private:
        class Shell{
            public:
                T* data;
                int index;
                Shell(T* data, int index){
                    this->data = data;
                    this->index = index;
                }
                ~Shell(){
                    delete data;
                }
                bool operator<(const Shell& other){
                    return *this->data<*other.data;
                }
                bool operator==(const Shell& other){
                    return *this->data==*other.data;
                }
                bool operator>(const Shell& other){
                    return !(*this<other || *this==other);
                }
                
        };
        void increaseCapacity(){
            capacity = capacity*2+1;
            Shell** newBacking = new Shell*[capacity];
            for(int i = 0; i<_size; i++){
                newBacking[i] = backing[i];
            }
            delete[] backing;
            backing = newBacking;
        }
        Shell* parent(Shell* child){
            return backing[(child->index-1)/2];
        }
        Shell* left(Shell* parent){ return backing[parent->index*2+1]; }
        Shell* right(Shell* parent){ return backing[parent->index*2+2]; }
        void swap(Shell* s1, Shell* s2){
            int tempIndex = s1->index;
            s1->index = s2->index;
            s2->index = tempIndex;

            backing[s1->index] = s1;
            backing[s2->index] = s2;

        }
        void floatUp(Shell* start){
            while(*start>*parent(start)){
                swap(start,parent(start));
            }
        }
        void heapify(Shell* start){
            if(start->index*2+1>=_size) return;
            if(start->index*2+2==_size){
                if(*start>*left(start)) return;
                swap(start,left(start));
                return;
            }
            if(*start<*left(start) || *start<*right(start)){
                if(*left(start)<*right(start)){
                    swap(start,right(start));
                    heapify(start);
                }else{
                    swap(start,left(start));
                    heapify(start);
                }
            }
        }
        Shell** backing;
        AVLTree<Shell>* lookupTable;
        int _size,capacity;
    public:
        Heap(){
            capacity = 1;
            _size = 0;
            backing = new Shell*[capacity];
            lookupTable = new AVLTree<Shell>();
        }
        ~Heap(){
            delete[] backing;
            delete lookupTable;
        }
        int size() { return _size; }
        void insert(string key, T* data){
            Shell* shell;
            if(lookupTable->has(key)){
                shell = lookupTable->get(key);
                shell->index = _size;
                delete shell->data;
                shell->data = data;
            }else{
                shell = new Shell(data,_size);
                lookupTable->insert(key,shell);
            }

            backing[_size++] = shell;
            if(_size==capacity){
                increaseCapacity();
            }
            floatUp(shell);
            
        }
        Shell* extractMax(){
            Shell* max = backing[0]; 
            backing[0] = backing[--_size];
            backing[0]->index = 0;
            heapify(backing[0]);
            max->index = -1;
            return max;
        }
        T** topK(int k){
            Shell** top = new Shell*[k];
            for(int i = 0; i<k; i++){
                top[i] = extractMax();
            }
            T** topData = new T*[k];
            for(int i = 0; i<k; i++){
                top[i]->index = _size;
                backing[_size++] = top[i];
                if(_size==capacity){
                    increaseCapacity();
                }
                floatUp(top[i]);
                topData[i] = top[i]->data;
            }
            delete[] top;
            return topData;
        }
        bool has(string key){
            return lookupTable->has(key) && lookupTable->get(key)->index!=-1;
        }
        void increaseBy(string key, int amount){
            Shell* shell = lookupTable->get(key);
            if(shell!=nullptr){
                (*shell->data)+=amount;
                floatUp(shell);
            }
        }
        void display(){
            cout << "Displaying Users <Position> <UserId> <Votes>:" << endl;
            for(int i = 0; i < size(); i++){
                cout << i + 1 << ": " << *backing[i]->data << endl;
            }
        }
};


#endif