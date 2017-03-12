#pragma once
#include<iostream>
using namespace std;

enum Colour
{
	RED,
	BLACK,
};

template<class K,class V>
struct RBTreeNode
{
	K _key;
	V _value;
	Colour _col;

	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;

	RBTreeNode(const K& key, const V& value)
		:_key(key)
		, _value(value)
		, _col(RED)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
	{}
};

template<class K,class V> 
class RBTree
{
	typedef RBTreeNode<K, V> Node;

public:
	RBTree()
		:_root(NULL)
	{}

	pair<Node*, bool> Insert(const K& key, const V& value)
	{//插入
		if (_root == NULL)
		{
			_root = new Node(key, value);
			_root->_col = BLACK;
			return make_pair(_root, true);
		}

		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{//找到要插入的位置
			if (key > cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
				return make_pair(cur, false);
		}
		//插入结点
		cur = new Node(key, value);
		Node *node = cur; 
		if (key > parent->_key)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}

		while (parent&&parent->_col == RED)
		{//父节点为红
			Node* grandfather = parent->_parent;
			if (grandfather->_left == parent)
			{//父节点为左孩子
				Node* uncle = grandfather->_right;

				if (uncle && uncle->_col == RED)
				{//叔结点存在且为红
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{//叔结点不为红或者不存在
					if (cur == parent->_right)
					{//插入结点为右孩子，先左旋，再调整父子关系
						RotateL(parent);
						swap(cur, parent);
					}
					//右旋后调色
					RotateR(grandfather);
					grandfather->_col = RED;
					parent->_col = BLACK;
					break;
				}
			}
			else
			{//父节点为左孩子，与上面的情况对称
				Node* uncle = grandfather->_left;

				if (uncle&&uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					if (cur == parent->_left)
					{
						RotateR(parent);
						swap(cur, parent);
					}
					else
					{
						RotateL(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
				}
			}
		}
		//根结点置黑
		_root->_col = BLACK;

		return make_pair(node, true);

	}

	void IsRBTree()
	{//判断是否满足红黑树
		if (_root == NULL)
			return true;

		if (_root->_col == RED)
			return false;

		size_t count = 0;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_col == BLACK)
				count++;
			cur = cur->_left;
		}

		size_t num = 0;

		return CheckColour(_root) && CheckBlackNum(_root, count, num);
	}

protected:
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		subR->_left = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subR;

		if (ppNode == NULL)
		{
			_root = subR;
		}
		else
		{
			if (ppNode->_left == parent)
				ppNode->_left = subR;
			else
				ppNode->_right = subR;
		}

		subR->_parent = ppNode;
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		subL->_right = parent;

		Node* ppNode = parent->_parent;
		parent->_parent = subL;
		

		if (ppNode == NULL)
		{
			_root = subL;
		}
		else
		{
			if (ppNode->_left == parent)
				ppNode->_left = subL;
			else
				ppNode->_right = subL;
		}

		subL->_parent = ppNode;
	}

	bool CheckColour(Node* root)
	{
		if (root)
			return true;

		if (root->_col == RED &&root->_parent->_col == RED)
			return false;

		return CheckColour(root->_left) && CheckColour(root->_right);

	}

	bool CheckBlackNum(Node* root, const size_t &k, size_t num)
	{
		if (root == NULL)
			return true;

		if (root->_col == BLACK)
			++num;

		if (root->_left == NULL && root->_right == NULL && num != k)
			return false;

		return CheckBlackNum(root->_left) && CheckBlackNum(root->_right);
	}

private:
	Node* _root;
};

void RBTreeTest()
{
	RBTree<int,int> T1;
	T1.Insert(1, 0);
	T1.Insert(5, 0);
	T1.Insert(3, 0);
	T1.Insert(2, 0);
}