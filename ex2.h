
#ifndef AP_EX2_EX2_H
#define AP_EX2_EX2_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>

using namespace std;

/**
 * Node Class.
 * Used as nodes in the linked list of CacheManager Class
 */
template <class T>
class Node {
private:
    string key;
    T value;
    Node<T>* next;
    Node<T>* prev;
    template <class>
    friend class CacheManager;
public:
    explicit Node() {
        this->next = NULL;
        this->prev = NULL;
    }
};

/**
 * CacheManager Class
 */
template <class T>
class CacheManager {
private:
    int capacity;
    string fileName;
    //using unordered_map so the 'get' will be in O(1) time in average
    unordered_map<string, Node<T>*> cacheMap;
    //first and last priority nodes in the linked list
    Node<T>* first;
    Node<T>* last;
public:
    explicit CacheManager(int num) : capacity(num) {
        this->first = NULL;
        this->last = NULL;
        //make the file name as the class_name of T
        this->fileName = T::class_name;
    }
    ~CacheManager() {
        //delete all the allocated memory
        this->deleteAll();
    }
    void insert(string key, T obj) {
        auto itr = this->cacheMap.find(key);
        //if the key is in the cacheMap map
        if (itr != this->cacheMap.end()) {
            Node<T>* node = itr->second;
            node->value = obj;
            this->removeNode(node);
            this->makeFirst(node);
        } else {
            this->addNewNode(obj, key);
        }
        fstream file;
        string objectFileName = this->fileName + key;
        file.open(objectFileName, ios::out | ios::binary);
        if (!file.is_open()) {
            file.close();
            throw "an error";
        }
        //write object to file
        file.write((char *) &obj, sizeof(obj));
        file.close();
    }
    T get(string key) {
        auto itr = this->cacheMap.find(key);
        //if the key is in the cacheMap map
        if (itr != this->cacheMap.end()) {
            Node<T>* node = itr->second;
            this->removeNode(node);
            this->makeFirst(node);
            return node->value;
        } else {
            string objectFileName = this->fileName + key;
            try {
                return this->readFromFile(objectFileName, key);
            } catch (const char * e) {
                throw e;
            }
        }
    }
    T readFromFile(string nameOfFile, string key) {
        //least recently used object
        T obj = this->last->value;
        fstream file;
        file.open(nameOfFile, ios::in | ios::binary);
        if (!file.is_open()) {
            file.close();
            throw "an error";
        }
        //read object from file
        file.read((char *) &obj, sizeof(obj));
        file.close();
        this->addNewNode(obj, key);
        return obj;
    }
    void addNewNode(T obj, string key) {
        auto* newNode = new Node<T>();
        newNode->key = key;
        newNode->value = obj;
        newNode->next = NULL;
        newNode->prev = NULL;
        //if the cache is already full
        if ((unsigned) this->cacheMap.size() == (unsigned) this->capacity) {
            //erase the least recently used object
            this->cacheMap.erase(this->last->key);
            Node<T>* erasedNode = this->last;
            this->removeNode(this->last);
            delete erasedNode;
            //make the new node first in the linked list
            this->makeFirst(newNode);
        } else {
            this->makeFirst(newNode);
        }
        this->cacheMap.insert(pair<string, Node<T>*>(key, newNode));
    }
    //get a template function
    template <typename Func>
    void foreach(Func f) {
        Node<T>* node = this->first;
        //does the function on all nodes
        while (node != NULL) {
            f(node->value);
            node = node->prev;
        }
    }
    //remove the node from the linked list
    void removeNode(Node<T>* node) {
        if (node->next != NULL) {
            node->next->prev = node->prev;
        } else {
            this->first = node->prev;
        }
        if (node->prev != NULL) {
            node->prev->next = node->next;
        } else {
            this->last = node->next;
        }
    }
    //make this node the first in the linked list
    void makeFirst(Node<T>* node) {
        node->prev = this->first;
        node->next = NULL;
        if (this->first != NULL) {
            this->first->next = node;
        }
        this->first = node;
        if (this->last == NULL) {
            this->last = this->first;
        }
    }
    //free all the memory of the objects in the linked list
    void deleteAll() {
        Node<T>* node = this->last;
        while (node != NULL) {
            Node<T>* deletedNode = node;
            if (node->next != NULL) {
                node = node->next;
            } else {
                node = NULL;
            }
            delete deletedNode;
        }
    }
};

#endif //AP_EX2_EX2_H