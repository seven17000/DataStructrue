#pragma once
#include<iostream>

/*
*Author：seven17000
*Date：2017.02.28
*Content：实现二叉搜索树
*/

template<class K,class V>
struct SearchBinaryTreeNode
{
	SearchBinaryTreeNode<K, V>* _left;
	SearchBinaryTreeNode<K, V>* _right;

	//const K _key;
	K _key;//此处在删除结点时会发生替换，不能为const
	V _value;

	SearchBinaryTreeNode(const K& k, const V& v)
		:_left(NULL)
		,_right(NULL)
		,_key(k)
		,_value(v)
	{}

};

template<class K,class V>
class SearchBinaryTree
{
	typedef SearchBinaryTreeNode<K, V> Node;
public:
	SearchBinaryTree()
		:_root(NULL)
	{}

	~SearchBinaryTree()
	{
		Destroy(_root);
	}

	void Destroy(Node*& root)
	{
		if (root == NULL)
			return;

		Destroy(root->_left);
		Destroy(root->_right);

		delete root;
		root = NULL;
	}

	//插入节点递归实现
	bool InsertR(const K& key, const V& value)
	{
		return _InsertR(_root, key, value);
	}

	bool _InsertR(Node*& root, const K& key, const V& value)
	{
		if (root == NULL)
		{
			root = new Node(key, value);
			return true;
		}

		if (key < root->_key)
		{
			return _InsertR(root->_left,key,value);
		}
		else if (key>root->_key)
		{
			return _InsertR(root->_right,key,value);
		}
		else
			return false;
	}
	
	//删除结点递归实现
	bool RemoveR(const K& key)
	{
		return _RemoveR(_root, key);
	}

	bool _RemoveR(Node*& root,const K& key)
	{
		if (root == NULL)
		{
			return false;
		}

		//找到要删除的结点
		if (key < root->_key)
		{
			return _RemoveR(root->_left, key);
		}
		else if (key>root->_key)
		{
			return _RemoveR(root->_right, key);
		}
		else
		{
			if (root->_left == NULL)
			{//要删除的结点左孩子为空时
				root = root->_right;
			}
			else if (root->_right == NULL)
			{//要删除的结点右孩子为空时
				root = root->_left;
			}
			else
			{//左右都不为空时
				Node* del = root;
				Node* parent = root;
				Node* subLeft = root->_right;
				while (subLeft->_left)
				{//找到要删除结点的中序的后继结点
					parent = subLeft;
					subLeft = subLeft->_left;
				}

				//使该结点与要删除结点交换
				root->_key = subLeft->_key;
				root->_value = subLeft->_value;
				del = subLeft;

				if (parent->_right == NULL)
				{
					parent->_right = subLeft->_right;
				}
				else
				{
					parent->_left = subLeft->_right;
				}

				delete del;
				return true;
			}
		}
	}

	//查找递归实现
	Node* FindR(const K& key)
	{
		return FindR(_root, key);
	}

	Node* _FindR(Node* root, const K& key)
	{
		if (root == NULL)
		{
			return false;
		}

		if (key < root->_key)
		{
			return _FindR(root->_left, key);
		}
		else if (key > root->_key)
		{
			return _FindR(root->_right, key);
		}
		else if(key == root->_key)
		{
			return root;
		}
	}

	bool Insert(const K& key,const V& value)
	{//非递归的插入
		if (_root == NULL)
		{
			_root = new Node<key, value>;
			return true;
		}

		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			if (_root->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
				return false;
		}

		if (parent->_key < key)
		{
			parent->_right = new Node(key, value);
		}
		else if (parent->_key>key)
		{
			parent->_left = new Node(key, value);
		}
		else
			return false;

		return true;

	}

	bool Remove(const K& key)
	{//非递归的删除结点
		if (_root == NULL)
			return false;

		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (key > cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				if (cur->_left == NULL)
				{
					if (parent == NULL)
					{
						_root = cur->_right;
					}
					else if (parent->_left == cur)
					{
						parent->_left = cur->_right;
					}
					else
					{
						parent->_right = cur->_right;
					}
				}
				else if (cur->_right == NULL)
				{
					if (parent == NULL)
					{
						_root = cur->_left;
					}
					else if (parent->_left == cur)
					{
						parent->_left = cur->_left;
					}
					else
					{
						parent->_right = cur->_left;
					}
				}
				else
				{
					parent = cur;
					Node* subLeft = cur->_right;
					while (subLeft->_left)
					{
						parent = subLeft;
						subLeft = subLeft->_left;
					}

					cur->_key = subLeft->_key;
					cur->_value = subLeft->_value;

					if (parent->_left == subLeft)
						parent->_left = subLeft->_right;
					else
						parent->_right = subLeft->_right;
				}

				delete cur;
			}
		}

		return true;
	}

protected:
	Node* _root;

};

void FunTest()
{
	SearchBinaryTree<int, int> T1;
	T1.InsertR(2, 100);
	T1.InsertR(5, 200);
	T1.InsertR(4, 300);
	T1.Insert(6, 400);
	T1.Insert(1, 500);
	T1.Insert(7, 600);
	T1.Remove(5);
	T1.RemoveR(4);
}

