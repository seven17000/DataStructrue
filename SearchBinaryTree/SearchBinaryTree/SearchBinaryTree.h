#pragma once
#include<iostream>

template<class K,class V>
struct SearchBinaryTreeNode
{
	SearchBinaryTreeNode<K, V>* _left;
	SearchBinaryTreeNode<K, V>* _right;

	//const K _key;
	K _key;//�˴���ɾ�����ʱ�ᷢ���滻������Ϊconst
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

	//����ڵ�ݹ�ʵ��
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
	
	//ɾ�����ݹ�ʵ��
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

		//�ҵ�Ҫɾ���Ľ��
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
			{//Ҫɾ���Ľ������Ϊ��ʱ
				root = root->_right;
			}
			else if (root->_right == NULL)
			{//Ҫɾ���Ľ���Һ���Ϊ��ʱ
				root = root->_left;
			}
			else
			{//���Ҷ���Ϊ��ʱ
				Node* del = root;
				Node* parent = root;
				Node* subLeft = root->_right;
				while (subLeft->_left)
				{//�ҵ�Ҫɾ����������ĺ�̽��
					parent = subLeft;
					subLeft = subLeft->_left;
				}

				//ʹ�ý����Ҫɾ����㽻��
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

	//���ҵݹ�ʵ��
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
	{//�ǵݹ�Ĳ���
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
	{//�ǵݹ��ɾ�����
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

