#pragma once
#include <cassert>
#include<algorithm>
#include <iostream>

using namespace std;
template <typename T>
struct TreeNode {
	T value;
	TreeNode* left = nullptr;
	TreeNode* right = nullptr;
};

template <typename T>
void DeleteTree(TreeNode<T>* node)
{
	if (!node)
	{
		return;
	}
	DeleteTree(node->left);
	DeleteTree(node->right);
	delete node;
}

template <typename T>
bool CheckTreeProperty(const TreeNode<T>* node, const T* min_, const T* max_)
{	
	if (node == nullptr)
	{
		return true;
	}
	
	if (!CheckTreeProperty(node->left, min_, max_))
	{
		return false;
	}

	if (!CheckTreeProperty(node->right, min_, max_))
	{
		return false;
	}

	min_ = &node->left->value;
	max_ = &node->right->value;	

	if (min_ == nullptr && max_ == nullptr)
	{
		return true;
	}

	if (min_ != nullptr && max_ != nullptr)
	{
		if (*min_ >= *max_)
		{
			return false;
		}
	} 

	if (min_ == nullptr && max_ != nullptr)
	{		
		if (node->value <= *max_)
		{
			return false;
		}
		return true;
		
	}

	if (min_ != nullptr && max_ == nullptr)
	{		
		if (*min_ >= node->value)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	if (*min_ >= node->value && node->value <= *max_)
	{
		return false;
	}
	else
	{
		return true;
	}
}


template <typename T>
void Print(const TreeNode<T>* node)
{
	if (!node)
	{
		return;
	}
	Print(node->left);
	cout << node->value << " ";
	Print(node->right);
}


template <typename T>
bool CheckTreeProperty(const TreeNode<T>* node)
{	
	return CheckTreeProperty<T>(node, nullptr, nullptr);
}

template <typename T>
bool isBalancedUtil(TreeNode<T>* root, int& maxh, int& minh)
{
	// Базовый вариант
	if (root == nullptr)
	{
		maxh = minh = 0;
		return true;
	}
	int lmxh, lmnh;
	// Для сохранения максимальной и минимальной высоты левого поддерева
	int rmxh, rmnh;
	// Для сохранения максимальной и минимальной высоты правого поддерева
	// Проверить, сбалансировано ли левое поддерево, также установить lmxh и lmnh

	if (isBalancedUtil(root->left, lmxh, lmnh) == false)
		return false;
	// Проверить, сбалансировано ли правое поддерево, также установить rmxh и rmnh

	if (isBalancedUtil(root->right, rmxh, rmnh) == false)
		return false;
	// Устанавливаем максимальную и минимальную высоты этого узла для родительского вызова

	maxh = max(lmxh, rmxh) + 1;

	minh = min(lmnh, rmnh) + 1;
	// Посмотрим, сбалансирован ли этот узел
	if (maxh <= 2 * minh)
		return true;
	return false;
}


// Обёртка над isBalancedUtil ()
template <typename T>
bool isBalanced(TreeNode<T>* root)
{
	int maxh, minh;
	return isBalancedUtil(root, maxh, minh);
}





