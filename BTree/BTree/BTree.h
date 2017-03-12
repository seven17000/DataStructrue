#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

/* 
*Author:seven17000
*Date:2017.3.9
*Content:ʵ��B��
*/

template <class K, class V, size_t M = 3>
struct BTreeNode
{
	pair<K,V> _kv[M];//��ż�ֵ
	size_t _size;//��ֵ����

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
	{//���ҽ�㣬
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

		//�����丸���
		return make_pair(parent, -1);
	}

	bool Insert(const pair<K,V>& kv)
	{//����
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

			//cur��ûװ��������
			if (cur->_size < M)
				return true;


			//���򿪱��½��
			Node* tmp = new Node;
			//�Ѿɽ��ֳ����룬�ұߵ�һ�������½����
			size_t mid = M >> 1;
			size_t i = mid + 1;
			size_t j = 0;

			while (i < cur->_size)
			{//�����Ҳ��㵽�½��
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
			{//���м�Ԫ�ز��뵽�����
				newKV = cur->_kv[mid];
				sub = tmp;
				cur->_size--;
				cur = cur->_parent;
			}
			else
			{//�����Ϊ�գ����������Ҫ����
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
		{//Ѱ�Ҳ���λ��
			if (newKV.first >= cur->_kv[index].first)
				break;

			cur->_kv[index + 1] = cur->_kv[index];
			cur->_sub[index + 2] = cur->_sub[index + 1];
			index--;
		}

		//�����㼰��Ӧ���ӽ��
		cur->_kv[index + 1] = newKV;
		cur->_sub[index + 2] = sub;
		//���Ӵ��ڣ����丸�׸�ֵ
		if (sub)
			sub->_parent = cur;

		cur->_size++;
	}


	void _InOrder(Node* root)
	{//��������ݹ�
		if (root == NULL)
			return;

		size_t index = 0;
		while (index < root->_size)
		{//��ӡ����
			_InOrder(root->_sub[index]);
			cout << root->_kv[index].first << " ";
			index++;
		}
		//��ӡ���һ���Һ���
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