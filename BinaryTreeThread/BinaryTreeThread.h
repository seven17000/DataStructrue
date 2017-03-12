#define _CRT_SECURE_NO_WARNINGS
#include<cassert>
#include<iostream>
using namespace std;

/*
*Author：seven17000
*Date：2017.01.20
*Content：实现了二叉树的线索化
*/

//枚举定义结点线索化标签
enum PointerTag
{
	THREAD,
	LINK
};

//定义线索化二叉树结点模板类
template<class T>
struct BinaryTreeThreadNode
{
	T _data;
	BinaryTreeThreadNode<T>* _left;
	BinaryTreeThreadNode<T>* _right;

	PointerTag _LeftTag;
	PointerTag _RightTag;

	BinaryTreeThreadNode(const T& x)
		:_data(x)
		, _left(NULL)
		, _right(NULL)
		, _LeftTag(LINK)
		, _RightTag(LINK)
	{}

};

template<class>

//定义线索化二叉树模板类
template<class T>
class BinaryTreeThread
{
	typedef BinaryTreeThreadNode<T> Node;
public:
	BinaryTreeThread(T* a, size_t n, const T& invalid)
	{
		assert(a);
		size_t index = 0;
		_root = _CreatTree(a, index, n, invalid);
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	void PreOrder()
	{
		_PreOrder(_root);
		cout << endl;
	}

	void InOrderThreading()
	{
		Node* pre = NULL;
		_InOrderThreading(_root,pre);
		if (pre&&pre->_right == NULL)
			pre->_RightTag = THREAD;
	}

	void PreOrderThreading()
	{
		Node* pre = NULL;
		_PreOrderThreading(_root,pre);
	}

	void PostOrderThreading()
	{
		Node* pre = NULL;
		if (_root != NULL)
		{
			_PostOrderThreading(_root, pre);
		}
	}

protected:

	void _PostOrderThreading(Node *cur, Node* &pre)
	{
		if (cur == NULL)
		{
			return;
		}
		_PostOrderThread(cur->_left, pre);
		_PostOrderThread(cur->_right, pre);
		if (cur->_left == NULL)
		{
			cur->_left = pre;
			cur->_LeftTag = THREAD;
		}
		if (prev&&prev->_right == NULL)
		{
			prev->_RightTag = THREAD;
			prev->_right = cur;
		}
		pre = cur;
	}

	void _PreOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}
		Node* cur = root;

		while (cur)
		{
			cout << cur->_data << " ";

			if (cur->_LeftTag == LINK)
				cur = cur->_left;
			else if (cur->_RightTag == LINK)
				cur = cur->_right;
			else
			{
				while (cur&&cur->_RightTag == THREAD)
				{
					cur = cur->_right;
				}
				if (cur)
					cur = cur->_right;
			}
		}
	}

	void _PreOrderThreading(Node* cur, Node*& pre)
	{
		if (cur == NULL)
			return;
		if (cur->_left == NULL)
		{
			cur->_left = pre;
			cur->_LeftTag = THREAD;
		}
		if (pre&&pre->_right == NULL)
		{
			pre->_RightTag = THREAD;
			pre->_right = cur;
		}
		prev = cur;
	}

	void _InOrder(Node* root)
	{
		if (root == NULL)
			return;
		Node* cur = root;
		while (cur)
		{
			while (cur->_LeftTag == LINK)
			{
				cur = cur->_left;
			}
			
			cout << cur->_data << " ";

			while (cur->_RightTag == THREAD)
			{
				cur = cur->_right;
				cout << cur->_data << " ";
			}
			cur = cur->_right;
		}


	}

	void _InOrderThreading(Node* cur,Node*& pre)
	{
		if (cur == NULL)
			return;

		_InOrderThreading(cur->_left, Node*& pre);

		if (cur->_left == NULL)
		{
			cur->_left = pre;
			cur->_LeftTag = Thread;
		}

		if (pre && pre->_right == NULL)
		{
			pre->right = cur;
			pre->RightTag = THREAD;
		}

		pre = cur;

		_InOrderThreading(cur->_right,Node*& pre)
	}

	Node* _CreateTree(T* a, size_t& index, size_t n, const T& invalid)
	{
		Node* root = NULL;
		if (index < n && a[index] != invalid)
		{
			root = new Node(a[index]);
			root->_left = _CreateTree(a,++index,n,invalid);
			root->_right = _CreateTree(a,++index,n,invalid);
		}
	}
protected:
	Node* _root;
};

void TestBinaryTreeThd()
{
	int a[10] = { 1, 2, 3, '#', '#', 4, '#' , '#', 5, 6 };
	BinaryTreeThread<int> t1(a, sizeof(a) / sizeof(a[0]), '#');
	t1.InOrderThreading();
	t1.InOrder();
}
