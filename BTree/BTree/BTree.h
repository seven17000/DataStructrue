#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

/* 
*Author:seven17000
*Date:2017.3.9
*Content:实现B树
*/

template <class K, class V, size_t M = 3>
struct BTreeNode
{
	pair<K,V> _kv[M];//存放键值
	size_t _size;//键值计数

	BTreeNode<K, V>* _sub[M + 1];
	BTreeNode<K, V>* _parent;

	BTreeNode()
		:_parent(NULL)
		, _size(0)
	{
		for (size_t i = 0; i <= M; ++i)
		{
			_sub[i] = NULL;
		}
	}
};

template<class K,class V,size_t M = 3>
class BTree
{
	typedef BTreeNode<K, V> Node;

public:
	BTree()
		:_root(NULL)
	{}

	~BTree()
	{
		_root = Destroy(_root);
	}

	pair<Node*, int> Find(const K& key)
	{//查找结点，
		Node* cur = _root;
		Node* parent = NULL;

		while (cur)
		{
			size_t index = 0;
			while (index < cur->_size)
			{
				if (key > cur->_kv[index].first)
					index++;
				else if (key == cur->_kv[index].first)
					return make_pair(cur, index);
				else
					break;
			}
			parent = cur;
			cur = cur->_sub[index];
		}

		//返回其父结点
		return make_pair(parent, -1);
	}

	bool Insert(const pair<K,V>& kv)
	{//插入
		if (_root == NULL)
		{
			_root = new Node;
			_root->_kv[0] = kv;
			_root->_size++;
			return true;
		}

		pair<Node*, int> ret = Find(kv.first);
		if (ret.second != -1)
			return false;

		Node* cur = ret.first;
		Node* temp = cur;
		pair<K, V> newKV = kv;
		Node* sub = NULL;

		while (1)
		{
			_Insert(cur, newKV, sub);

			//cur还没装满，返回
			if (cur->_size < M)
				return true;


			//否则开辟新结点
			Node* tmp = new Node;
			//把旧结点分成两半，右边的一半存放在新结点内
			size_t mid = M >> 1;
			size_t i = mid + 1;
			size_t j = 0;

			while (i < cur->_size)
			{//拷贝右侧结点到新结点
				tmp->_kv[j] = cur->_kv[i];
				cur->_kv[i] = pair<K, V>();

				tmp->_sub[j] = cur->_sub[i];
				if (cur->_sub[i])
					cur->_sub[i]->_parent = tmp;

				i++;
				j++;
				tmp->_size++;
				cur->_size--;
				
			}

			tmp->_sub[j] = cur->_sub[i];
			cur->_sub[i] = NULL;
			if (cur->_sub[i])
				cur->_sub[i]->_parent = tmp;

			if (cur->_parent)
			{//将中间元素插入到父结点
				newKV = cur->_kv[mid];
				sub = tmp;
				cur->_size--;
				cur = cur->_parent;
			}
			else
			{//父结点为空，即根结点需要分裂
				Node* newRoot = new Node;
				newRoot->_kv[0] = cur->_kv[mid];
				newRoot->_size = 1;

				newRoot->_sub[0] = cur;
				cur->_parent = newRoot;
				newRoot->_sub[1] = tmp;
				tmp->_parent = newRoot;

				cur->_size--;

				_root = newRoot;
				return true;
			}
		}
	}


protected:

	Node* Destroy(Node* root)
	{
		if (_root == NULL)
		{
			return NULL;
		}

		for (size_t i = 0; i < M + 1; i++)
		{
			root->_sub[i] = Destroy(root->_sub[i]);
		}

		delete root;
		root = NULL;
	}

	void _Insert(Node* cur, const pair<K, V>& newKV, Node* sub)
	{
		int index = (cur->_size)-1;
		while (index >= 0)
		{//寻找插入位置
			if (newKV.first >= cur->_kv[index].first)
				break;

			cur->_kv[index + 1] = cur->_kv[index];
			cur->_sub[index + 2] = cur->_sub[index + 1];
			index--;
		}

		//放入结点及对应孩子结点
		cur->_kv[index + 1] = newKV;
		cur->_sub[index + 2] = sub;
		//孩子存在，给其父亲赋值
		if (sub)
			sub->_parent = cur;

		cur->_size++;
	}


	void _InOrder(Node* root)
	{//中序遍历递归
		if (root == NULL)
			return;

		size_t index = 0;
		while (index < root->_size)
		{//打印左孩子
			_InOrder(root->_sub[index]);
			cout << root->_kv[index].first << " ";
			index++;
		}
		//打印最后一个右孩子
		_InOrder(root->_sub[root->_size]);
	}

private:
	Node* _root;
};

int BTreeTest()
{
	BTree<int,int> T1;
	/*T1.Insert(make_pair(1, 1));*/
	//T1.Insert(make_pair(3, 1));
	//T1.Insert(make_pair(9, 1));
	//T1.Insert(make_pair(5, 1));
	//T1.Insert(make_pair(4, 1));
	//T1.Insert(make_pair(6, 1));
	//T1.Insert(make_pair(7, 1));
	//T1.Insert(make_pair(2, 1));
	return 0;
}