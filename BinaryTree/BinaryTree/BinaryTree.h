#pragma once
#include<iostream>
#include<queue>
#include<stack>
#include<assert.h>
using namespace std;
/*
*Author：seven17000
*Date：2017.01.05
*Content：实现了二叉树
*/

template<class T>
struct BinaryTreeNode
{
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;
	T _data;

	BinaryTreeNode(const T& x)
		:_data(x)
		,_left(NULL)
		,_right(NULL)
	{}
};

template<class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree(T* a, size_t size, const T& invalid = T())
	{
		assert(a);
		size_t index = 0;
		_root = CreatTree(a,size,invalid,index);
	}

	BinaryTree(BinaryTree<T> &t)
	{
		_root = _Copy(t._root);
	}

	BinaryTree<T>& operator = (BinaryTree<T>& t)
	{
		if (this != &t)
		{
			Node* tmp = _Copy(t._root);
			_Destroy(_root);
			_root = tmp;
		}

		return *this;
	}

	~BinaryTree()
	{
		_Destroy(_root);
		_root = NULL;
	}

	//前序遍历二叉树（递归）
	void PrevOdrder()
	{
		_PrevOrder(_root);
		cout << endl;
	}

	//中序遍历二叉树（递归）
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	//后序遍历二叉树（递归）
	void PostOrder()
	{
		_PostOrder(_root);
		cout << endl;
	}

	//层序遍历
	void LevelOrder()
	{
		queue<Node*> q;
		if (_root)
			q.push(_root);

		while (!q.empty())
		{
			Node* front = q.front();
			q.pop();

			cout << front->_data;

			if (front->_left)
			{
				q.push(front->_left);
			}

			if (front->_right)
			{
				q.push(front->_right);
			}
		}
		cout << endl;
	}

	//前序遍历（非递归）
	void PrevOrderNor()
	{
		stack<Node*> s;
		Node* cur = _root;

		while (!s.empty()||cur)
		{
			while (cur)
			{
				cout << cur->_data;
				s.push(cur);
				cur = cur->_left;
			}

			Node* top = s.top();
			s.pop();
			cur = top->_right;
		}
		cout << endl;
	}

	//中序遍历（非递归）
	void InOrderNor()
	{
		stack<Node*> s;
		Node* cur = _root;
		while (!s.empty()||cur)
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}

			Node* top = s.top();
			cout << top->_data;
			s.pop();
			cur = top->_right;
		}
		cout << endl;
	}

	//后序遍历（非递归）
	void PostOrderNor()
	{
		stack<Node*> s;
		Node* cur = _root;
		Node* prev = NULL;
		while (!s.empty() || cur)
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}

			Node* top = s.top();
			if (top->_right == NULL||top->_right == prev)
			{
				cout << top->_data;
				prev = top;
				s.pop();
			}
			else
			{
				cur = top->_right;
			}
		}
		cout << endl;
	}

	size_t Depth()
	{
		return _Depth(_root);
	}

	size_t Size()
	{
		size_t count = 0;
		_Size(_root,count);
		return count;
	}

	size_t GetKLevelSize(size_t k)
	{
		assert(K > 0);
		size_t count = 0;
		size_t level = 1;
		_GetKLevelSize(_root, k, level, count);

		return count;
	}

	Node* Find(Node* root, const T& x)
	{
		if (root == NULL)
		{
			return NULL;
		}

		if (root->_data == x)
		{
			return root;
		}

		Node*ret = Find(root->_left, x);
		if (ret == NULL)
		{
			ret = Find(root->_right,x)
		}

		return ret;
	}
protected:
	size_t _Size(Node* root,size_t& count)//使用递归，计数器传引用。
	{
		if (root == NULL)
			return 0;

		++count;
		_Size(root->_left;count);
		_Size(root->_right;count);

	}

	size_t _Depth(Node* root)
	{
		if (root == NULL)
			return 0;
		size_t LeftDepth = _Depth(_root->_left);
		size_t RightDepth = _Depth(_root->_right);

		return LeftDepth > RightDepth ? LeftDepth + 1 : RightDepth+1;
	}

	size_t _GetKLevelSize(Node* root, const size_t k, size_t level, size_t &count)
	{
		if (root == NULL)
		{
			return;
		}

		if (level == k)
		{
			count++;
			return;
		}

		_GetKLevelSize(root->_left, k, level + 1, count);
		_GetKLevelSize(root->_right, k, level + 1, count);
	}

	void _PostOrder(Node* root)
	{
		if (root != NULL)
		{
			_PostOrder(root->_left);
			_PostOrder(root->_right);
			_PrintTree(root);
		}

		return;
	}

	void _InOrder(Node* root)
	{
		if (root != NULL)
		{
			_InOrder(root->_left);
			_PrintTree(root);
			_InOrder(root->_right);
		}

		return;
	}

	void _PrevOrder(Node* root)
	{
		if (root != NULL)
		{
			_PrintTree(root);
			_PrevOrder(root->_left);
			_PrevOrder(root->_right);
		}

		return;
	}

	void _PrintTree(Node* root)
	{
		if (root != NULL)
			cout << root->_data;

		return;
	}

	void _Destroy(Node* root)
	{
		if (root == NULL)
			return;
		_Destroy(root->_left);
		_Destroy(root->_right);
		delete root;
	}

	Node* _Copy(Node* root)
	{
		if (root == NULL)
			return 0;

		Node* node = new Node(root->_data);
		node->_left = _Copy(root->_left);
		node->_right =_Copy(root->_right);

		return node;
	}

	Node* CreatTree(T*a,size_t size,const T& invalid, size_t &index)
	{
		Node * root = NULL;
		if (index < size && a[index] != invalid)
		{
			root = new Node(a[index]);
			root->_left = CreatTree(a, size,invalid, ++index);
			root->_right = CreatTree(a, size, invalid, ++index);
		}

		return root;
	}

protected:
	Node *_root;
};


void TestTree()
{
	int a[10] = { 1, 2, 3, '#', '#', 4, '#' , '#', 5, 6 };
	BinaryTree<int> t1(a, sizeof(a) / sizeof(a[0]), '#');
	BinaryTree<int> t2(t1);
	t2 = t1;
	t2.PrevOdrder();
	t2.InOrder();
	t2.PostOrder();
	t2.LevelOrder();
	t2.PrevOrderNor();
	t2.InOrderNor();
	t2.PostOrderNor();
}
