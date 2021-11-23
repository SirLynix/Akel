// This file is a part of Akel
// CREATED : 17/11/2021
// UPDATED : 23/11/2021

#ifndef __AK_BINARY_SEARCH_TREE__
#define __AK_BINARY_SEARCH_TREE__

namespace Ak
{
    template <typename T>
    class BinarySearchTree
    {
        public:
            explicit BinarySearchTree(T data);
            BinarySearchTree<T>* add(T data); // The type returned is for internal recursion
            BinarySearchTree<T>* remove(T data); // Same shit
            BinarySearchTree<T>* find_minimum();
            BinarySearchTree<T>* find(T data);
            inline BinarySearchTree<T>* getRight() { return _right; }
            inline BinarySearchTree<T>* getLeft() { return _left; }
            inline T& getData() { return _data; }
            inline BinarySearchTree<T>* setRight(BinarySearchTree<T>* right) { _right = right; }
            inline BinarySearchTree<T>* setLeft(BinarySearchTree<T>* left) { _left = left; }
            ~BinarySearchTree();
        
        private:
            T _data;
            BinarySearchTree<T>* _left = nullptr;
            BinarySearchTree<T>* _right = nullptr;
    };
}

#include <Utils/Containers/bst.inl>

#endif // __AK_BINARY_SEARCH_TREE__
