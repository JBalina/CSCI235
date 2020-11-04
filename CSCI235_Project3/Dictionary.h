/*
Jonathan Balina
CSCI 235
Shostak
Project 3
*/

#ifndef DICTIONARY_H_INCLUDED
#define DICTIONARY_H_INCLUDED

#include<iostream>
#include<string>

//I made my own vector class because containers were not allowed
//it holds two arrays for keys and Items
template<class KeyType, class ItemType>
class myVector
{
private:
    KeyType* SortedKeys;
    ItemType* SortedItems;
    int size;
public:
    myVector();
    ~myVector();
    void push_back(const KeyType& new_key, const ItemType& new_item);
    int Size() const;
    KeyType GetKeyAt(int index) const;
    ItemType GetItemAt(int index)const;
};

template<class KeyType, class ItemType>
class Node
{
private:
    KeyType key;
    ItemType item;
    Node<KeyType, ItemType> *left, *right;
public:
    Node();
    Node(const KeyType& new_key);
    Node(const KeyType& new_key, const ItemType& new_item);
    ItemType& GetRef();
    KeyType GetKey() const;
    void SetKey(KeyType new_key);
    Node<KeyType, ItemType>* GetLeft() const;
    Node<KeyType, ItemType>* GetRight()const;
    void SetLeft(Node<KeyType, ItemType>* const NewLeft);
    void SetRight(Node<KeyType, ItemType>* const NewRight);
};

template<class KeyType, class ItemType>
class Dictionary
{
private:
    Node<KeyType, ItemType>* root;
    int size;
    void util_clear(Node<KeyType, ItemType>* cur);
    int util_height(Node<KeyType, ItemType>* cur) const;
    Node<KeyType, ItemType>* search(const KeyType& Skey);
    void AddItem(const KeyType& new_key);
    Node<KeyType, ItemType>* util_remove(Node<KeyType, ItemType>* cur, KeyType Skey);
    void util_print(Node<KeyType, ItemType>* stree) const;
    void util_balance1(myVector<KeyType, ItemType> &SortedList, Node<KeyType, ItemType>* cur);
    Node<KeyType, ItemType>* util_balance2(myVector<KeyType, ItemType> &SortedList, int small, int large);
public:
    Dictionary();
    ~Dictionary();
    bool IsEmpty();
    void Clear();
    int Size() const;
    int Height() const;
    int Count(const KeyType& Skey);
    ItemType& operator[](const KeyType& Skey);
    void Remove(const KeyType& Skey);
    void Balance();
    void print() const;
};

#include "Dictionary.cpp"
#endif
