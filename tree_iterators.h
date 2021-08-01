#pragma once
#include <iostream>
#include <cassert>

using namespace std;

template <class T>
struct TreeNodeIt 
{
    T value;
    TreeNodeIt* parent = nullptr;
    TreeNodeIt* left = nullptr;
    TreeNodeIt* right = nullptr;
};

template <class T>
void DeleteTreeIt(TreeNodeIt<T>* node) 
{
    if (!node) 
    {
        return;
    }
    DeleteTreeIt(node->left);
    DeleteTreeIt(node->right);
    delete node;
}

template <class T>
void PrintTreeIt(const TreeNodeIt<T>* root, ostream& out = cout)
{
    out << " ( "s;
    out << root->value;
    if (root->left || root->right) 
    {
        if (root->left)
        {
            PrintTreeIt(root->left, out);
        }
        else
        {
            out << "*"s;
        }
        if (root->right)
        {
            PrintTreeIt(root->right, out);
        }
        else 
        {
            out << "*"s;
        }
    }
    out << " ) "s;
}

template <class T>
ostream& operator << (ostream& out, const TreeNodeIt<T>* node)
{
    PrintTreeIt(node, out);
    return out;
}

template <class T>
TreeNodeIt<T>* begin(TreeNodeIt<T>* node)
{
    TreeNodeIt<T>* result{};
    while (node->left != nullptr)
    {
        return begin(node->left);
    }

    if (node->left == nullptr)
    {
        result = node;
    }   

    return result;
}

template <class T>
TreeNodeIt<T>* next1(TreeNodeIt<T>* node)
{       
        if (node->parent != nullptr)
        {
            if (node->value < node->parent->value)
            {
                if (node->right == nullptr)
                {
                    return node->parent;
                }
                if (node->right != nullptr)
                {
                    return node->right;
                }
            }
            if (node->parent->parent == nullptr)
            {
                if (node->value > node->parent->value
                    && node->right == nullptr)
                {
                    return node->parent->parent;
                }
            }
            else 
            {
                if (node->value > node->parent->value
                    && node->right == nullptr 
                    && node->value < node->parent->parent->value)
                {
                   return node->parent->parent;
                }
            }
            if (node->value > node->parent->value
                && node->parent != nullptr
                && node->right != nullptr)
            {
                return node->right;
            }
            if (node->value > node->parent->value
                && node->right != nullptr)
            {
                return node->right;
            }
        }   

    if (node->parent == nullptr 
        && node->right->left != nullptr)
    {
        return node->right->left;
    }
    if(node->parent == nullptr
        && node->right->left == nullptr)
    {
        return node->right;
    }
    
    return{};   
}


template <class T>
TreeNodeIt<T>* next(TreeNodeIt<T>* node)
{   
    if (node->right != nullptr)
    {
        return begin(node->right);       
    }
    if (node->parent != nullptr)
    {
        if (node->right == nullptr && node == node->parent->left)
        {
            return node->parent;
        }
    }

    if (node->parent == nullptr && node->right != nullptr)
    {
        return node->right;
    }
    
    if (node->parent == nullptr && node->right == nullptr)
    {
        return nullptr;
    }

    if (node->parent->parent != nullptr)
    {
        if (node->parent->parent->right != node->parent)
        {
            return node->parent->parent;            
        }
        
        if (node->parent->parent->right == node->parent)
        {
            return nullptr;
        }
    }  
    return nullptr;
}


// функция создаёт новый узел с заданным значением и потомками
TreeNodeIt<int>* N(int val, TreeNodeIt<int>* left = nullptr, TreeNodeIt<int>* right = nullptr)
{
    auto res = new TreeNodeIt<int>{ val, nullptr, left, right };
    if (left)
    {
        left->parent = res;
    }
    if (right) 
    {
        right->parent = res;
    }

    return res;
}


