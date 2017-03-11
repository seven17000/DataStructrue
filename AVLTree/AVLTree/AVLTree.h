#pragma once
#include<stdlib.h>
#include<iostream>
using namespace std;

/*
*Author：seven17000
*Date：2017.03.04
*Content：实现了AVL树
*/

template<class K,class V>
struct AVLTreeNode
{
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;

	K _key;
	V _value;

	int _bf;

	AVLTreeNode(const K& key, const V& value)
		:_left(NULL)
		,_right(NULL)
		,_parent(NULL)
		,_key(key)
		,_value(value)
		,_bf(0)
	{}
};

template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K,V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}

	~AVLTree()
	{
		Destroy(_root);
	}

	void Destroy(Node* root)
	{
		if (root == NULL)
			return;

		Destroy(root->_left);
		Destroy(root->_right);

		delete root;
		root == NULL;
	}

	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}
		
		Node* parent = NULL;
		Node* cur = _root;
		while(cur)
		{//找到要插入结点的父节点位置
			if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (key>cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}

		//插入新结点
		cur = new Node(key, value);
		if (key < parent->_key)
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_right = cur;
			cur->_parent = parent;
		}

		while (parent)
		{//调整平衡因子
			if (parent->_left == cur)
				parent->_bf -= 1;
			else
				parent->_bf += 1;

			if (parent->_bf == 0)
				break;
			else if (parent->_bf == 1
				|| parent->_bf == -1)
			{//父结点的平衡因子变化，继续向上更新
				cur = parent;
				parent = cur->_parent;
			}
			else if (parent->_bf == 2
				||parent->_bf ==-2)
			{

				if (parent->_bf == 2)
				{
					if (parent->_bf == 2)
					{
						if (cur->_bf == 1)
						{
							RotateL(parent);
						}
						else
						{
							RotateRL(parent);
						}
					}
					else
					{
						if (cur->_bf == -1)
						{
							RotateR(parent);
						}
						else
						{
							RotateLR(parent);
						}
					}

					break;
				}
			}
		}
	}

	bool Remove(const K& key)
	{
		return _Remove(_root,key);
	}

	bool _Remove(Node* root,const K& key)
	{//与二叉搜索树的删除基本相同
		if (root == NULL)
			return false;

		if (key < root->_key)
		{
			root->_bf += 1;
			return _Remove(root->_left, key);
		}
		else if (key>root->_key)
		{
			root->_bf -= 1;
			return _Remove(root->_right, key);
		}
		else
		{
			Node* del = root;
			
			if (root->_left == NULL)
			{
				root->_right->_parent = root->_parent;
				root = root->_right;
			}
			else if (root->_right == NULL)
			{
				root->_left->_parent = root->_parent;
				root = root->_left;
			}
			else
			{
				Node* subLeft = root->_right;
				while (subLeft->_left)
				{
					subLeft = subLeft->_left;
				}

				root->_key = subLeft->_key;
				root->_value = subLeft->_value;
				del = subLeft;

				subLeft = subLeft->_right;

				while (del->_parent)
				{//调整平衡，从要被真正delete的那个结点开始向上调整
					if (del->_parent->_bf == 2
						|| del->_parent->_bf == -2)
					{
						if (del->_parent->_bf == 2)
						{
							if (del->_bf == 1)
								RotateL(del->_parent);
							else
								RotateRL(del->_parent);
						}
						else
						{
							if (del->_parent->_bf == -2)
							{
								if (del->_bf == 1)
									RotateR(del->_parent);
								else
									RotateLR(del->_parent);
							}
						}
					}
					else
						return true;
				}

			}
			delete del;
			return true;
		}


	}

	bool IsBalance()
	{//判断是否平衡
		return _IsBalance(_root);
	}

	size_t _Depth(Node* root)
	{//求深度
		if (root == NULL)
			return 0;
		
		size_t leftDepth = _Depth(root->_left);
		size_t rightDepth = _Depth(root->_right);

		return leftDepth < rightDepth ? rightDepth+1 : leftDepth+1;

	}

	bool _IsBalance(Node* root)
	{//时间复杂度O(N?)
		if (root == NULL)
			return true;

		size_t leftH = _Depth(root->_left);
		size_t rightH = _Depth(root->_right);

		if ((rightH - leftH) != root->_bf)
		{
			cout << "平衡因子异常：" << root->_key << endl;
		}

		return abs(rightH - leftH) <= 1 
			&& _IsBalance(root->_left) 
			&& _IsBalance(root->_right);
	}

	bool IsBalanceOP()
	{//判断是否平衡
		size_t depth= 0;
		return _IsBalanceOP(_root,depth);
	}

	bool _IsBalanceOP(Node* root, size_t& depth)
	{//时间复杂度O(N)
		if (root == NULL)
		{
			depth = 0;
			return true;
		}

		size_t leftDepth, rightDepth;
		if (_IsBalanceOP(root->_left, leftDepth)
			&& _IsBalanceOP(root->_right, rightDepth))
		{
			depth = leftDepth < rightDepth ? rightDepth + 1 : leftDepth + 1;
			return abs(leftDepth - rightDepth) < 2;
		}
	}

	void RotateL(Node* parent)
	{//左旋
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
			subR->_parent = NULL;
		}
		else
		{
			if (parent == ppNode->_left)
				ppNode->_left = subR;
			else
				ppNode->_right = subR;

			subR->_parent = ppNode;
		}

		subR->_bf = parent->_bf = 0;
	}


	void RotateR(Node* parent)
	{//右旋
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		subL->_right = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subL;

		if (parent == _root)
		{
			_root = subL;
			_root->_parent = NULL;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subL;
			}
			else
			{
				ppNode->_right = subL;
			}
			subL->_parent = ppNode;
		}

		parent->_bf = subL->_bf = 0;
	}

	void RotateLR(Node* parent)
	{//左右
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;

		RotateL(parent->_left);
		RotateR(parent);

		if (bf == 1)
		{
			subL->_bf = -1;
			parent->_bf = 0;
		}
		else if (bf == -1)
		{
			parent->_bf = 1;
			subL->_bf = 0;
		}
		else
		{
			parent->_bf = subL->_bf = 0;
		}

		subLR->_bf = 0;
	}

	void RotateRL(Node* parent)
	{//右左
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;

		RotateR(parent->_right);
		RotateL(parent);

		if (bf == 1)
		{
			subR->_bf = 0;
			parent->_bf = -1;
		}
		else if (bf == -1)
		{
			subR->_bf = 1;
			parent->_bf = 0;
		}
		else
		{
			subR->_bf = parent->_bf = 0;
		}

		subRL->_bf = 0;
	}

protected:
	Node* _root;
};

void AVLtest()
{
	AVLTree<int, int> T1;
	T1.Insert(2, 1);
	T1.Insert(6, 1);
	T1.Insert(4, 1);
	T1.Insert(5, 1);
	T1.Insert(8, 1);
	T1.Insert(1, 1);
	T1.Insert(10, 1);
	T1.Insert(9,1);
	T1.Remove(6);
}
