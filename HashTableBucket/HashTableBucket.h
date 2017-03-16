#pragma once
#include<iostream>
#include<vector>
using namespace std;

/*
*Author:Seven17000
*Date:2017.03.14
*Content:ʵ�ֹ�ϣͰ
*/

template<class K,class V>
struct HashTableBucketNode
{
	K _key;
	V _value;

	HashTableBucketNode<K, V>* _next;

	HashTableBucketNode(const K& key, const V& value)
		:_key(key)
		, _value(value)
		, _next(NULL)
	{}
};

template<class K>
struct _HashFunc
{//��������key�ķº���
	size_t operator()(const K& key)
	{
		return key;
	}
};

template<>
struct _HashFunc<string>
{//�ػ�string�汾

	static size_t BKDRHash(const char*str)
	{
		unsigned int seed = 131;// 31 131 1313 13131 131313
		unsigned int hash = 0;
		while (*str)
		{
			hash = hash*seed + (*str++);
		}
		return(hash & 0x7FFFFFFF);
	}

	size_t operator()(const string& key)
	{
		return BKDRHash(key.c_str());
	}
};

const int _PrimeSize = 28;
static const unsigned long _PrimeList[_PrimeSize] =
{//������
	53ul, 97ul, 193ul, 389ul, 769ul,
	1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
	49157ul, 98317ul, 196613ul, 393241ul,
	786433ul,
	1572869ul, 3145739ul, 6291469ul, 12582917ul,
	25165843ul,
	50331653ul, 100663319ul, 201326611ul, 402653189ul,
	805306457ul,
	1610612741ul, 3221225473ul, 4294967291ul
};


template<class K,class V,class HashFunC = _HashFunc<K>>
class HashTableBucket
{
	typedef HashTableBucketNode<K,V> Node;
public:
	HashTableBucket(size_t size)
		:_size(0)
	{
		size_t newsize = GetPrime(size);
		_v.resize(newsize);
	}

	size_t HashFunc(const K& key)
	{//��ϣ����
		HashFunC hs;
		size_t hash = hs(key);
		return hash % _v.size();
	}

	pair<Node*, bool> Insert(const K& key, const V& value)
	{//����
		CheckCapacity();
		size_t index = HashFunc(key);

		if (!_v[index])
		{//ͷָ��Ϊ��
			Node* newNode = new Node(key, value);
			_v[index] = newNode;
			++_size;
			return make_pair(newNode, true);
		}

		//�������в��Ҳ���λ��
		Node* prev = NULL;
		Node* cur = _v[index];
		while (cur)
		{
			if (cur->_key == key)
				return make_pair(cur, false);

			prev = cur;
			cur = cur->_next;
		}
		Node* newNode =new Node(key, value);
		prev->_next = newNode;
		++_size;
		return make_pair(newNode, true);
	}

	//Node* Find(const K& key)
	//{//���ҵĵ�һ��ʵ�֣�ֱ�Ӱ�λ�ò���
	//	size_t index = HashFunc(key);

	//	Node* cur = _v[index];
	//	while (cur)
	//	{
	//		if (cur->_key == key)
	//			return cur;

	//		cur = cur->_next;
	//	}

	//	return NULL;
	//}

	Node* Find(const K& key)
	{//��������
		for (size_t index = 0; index < _size; ++index)
		{
			Node* cur = _v[index];
			while (cur)
			{
				if (cur->_key = key)
					return cur;

				cur = cur->_next;
			}
		}

		return NULL;
	}

	bool Remove(const K& key)
	{//ɾ��
		size_t index = HashFunc(key);

		Node* prev = NULL;
		Node* cur = _v[index];

		while (cur)
		{
			if (cur->_key == key)
			{
				if (prev == NULL)
					_v[index] = NULL;	
				else
					prev->_next = cur->_next;

				delete cur;
				return true;
			}
		}
		return false;
	}


protected:

	size_t GetPrime(size_t size)
	{//�������������
		for (size_t i = 0; i < _PrimeSize; ++i)
		{
			if (_PrimeList[i] > size)
			{
				return _PrimeList[i];
			}

		}
		return _PrimeList[_PrimeSize - 1];
	}

	void Swap(HashTableBucket<K, V> tmp)
	{//����
		std::swap(_v, tmp._v);
		std::swap(_size, tmp._size);
	}

	void CheckCapacity()
	{//�������
		if (_size == _v.size())
		{
			HashTableBucket<K, V> tmp(_v.size());

			for (size_t index = 0; index < _size; ++_size)
			{
				Node* cur = _v[index];
				while (cur)
				{
					Node* cur = _v[index];
					while (cur)
					{
						tmp.Insert(cur->_key, cur->_value);
						cur = cur->_next;
					}
				}
			}
			Swap(tmp);
		}
	}
private:
	vector<Node*> _v;
	size_t _size;
};

int HashTableBucketTest()
{
	HashTableBucket<int,int> hs1(5);
	hs1.Insert(1, 1);
	hs1.Insert(54, 54);
	hs1.Insert(3, 3);
	hs1.Insert(4, 4);
	hs1.Insert(56, 56);
	hs1.Find(6);
	hs1.Remove(3);
	return 0;
}