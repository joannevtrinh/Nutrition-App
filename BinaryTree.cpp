#include "BinaryTree.h"
#include <iostream>
#include <queue>

template<class ItemType>
BinaryTree<ItemType>::BinaryTree()
{
    rootPtr = nullptr;
    count = nullptr;
}

template<class ItemType>
BinaryTree<ItemType>::BinaryTree(const BinaryTree<ItemType> & tree)
{
    rootPtr = copyTree(tree.rootPtr);
    count = tree.count;
}

template<class ItemType>
BinaryTree<ItemType>::~BinaryTree()
{
    destroyTree(rootPtr);
}

template<class ItemType>
bool BinaryTree<ItemType>::isEmpty() const
{
    return count == nullptr;
}

template<class ItemType>
int BinaryTree<ItemType>::size() const
{
    return count;
}

template<class ItemType>
void BinaryTree<ItemType>::clear()
{
    destroyTree(rootPtr);
    rootPtr = nullptr;
    count = nullptr;
}

template<class ItemType>
void BinaryTree<ItemType>::preOrder(void visit(ItemType &)) const
{
    _preorder(visit, rootPtr);
}

template<class ItemType>
void BinaryTree<ItemType>::inOrder(void visit(ItemType &)) const
{
    _inorder(visit, rootPtr);
}

template<class ItemType>
void BinaryTree<ItemType>::postOrder(void visit(ItemType &)) const
{
    _postorder(visit, rootPtr);
}



template<class ItemType>
BinaryTree<ItemType> & BinaryTree<ItemType>::operator=(const BinaryTree<ItemType> & sourceTree)
{
    rootPtr = copyTree(sourceTree.rootPtr);
    count = sourceTree.count;
    
    return *this;
}

template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
    if(nodePtr != nullptr)
    {
        destroyTree(nodePtr->getLeftPtr());
        destroyTree(nodePtr->getRightPtr());
        delete nodePtr;
    }
}

template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr)
{
    BinaryNode<ItemType>* newNodePtr = nullptr;
    
    if(nodePtr == nullptr)
        newNodePtr = nullptr;
    else
    {
        newNodePtr = new BinaryNode<ItemType>(nodePtr->getItem());
        newNodePtr->setLeftPtr(copyTree(nodePtr->getLeftPtr()));
        newNodePtr->setRightPtr(copyTree(nodePtr->getRightPtr()));
    }
    
    return newNodePtr;
}

template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr != nullptr)
    {
        ItemType item = nodePtr->getItem();
        visit(item);
        _preorder(visit, nodePtr->getLeftPtr());
        _preorder(visit, nodePtr->getRightPtr());
    }
}

template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr != nullptr)
    {
        _inorder(visit, nodePtr->getLeftPtr());
        ItemType item = nodePtr->getItem();
        visit(item);
        _inorder(visit, nodePtr->getRightPtr());
    }
}

template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr != nullptr)
    {
        _postorder(visit, nodePtr->getLeftPtr());
        _postorder(visit, nodePtr->getRightPtr());
        ItemType item = nodePtr->getItem();
        visit(item);
        
    }
}

//template<class ItemType>
//void BinaryTree<ItemType>::breadthfirst(void visit(ItemType &)) const
//{
//    queue<BinaryNode<ItemType>*> q;
//    ItemType item;
//    
//    if(rootPtr != nullptr)
//        q.push(rootPtr);
//    
//    while (!q.empty())
//    {
//        item = q.front()->getItem();
//        visit(item);
//        if(q.front()->getLeftPtr() != nullptr)
//            q.push(q.front()->getLeftPtr());
//        if(q.front()->getRightPtr() != nullptr)
//            q.push(q.front()->getRightPtr());
//        q.pop();
//    }
//}