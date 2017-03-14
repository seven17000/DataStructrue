#pragma once
#include<string>
#include<iostream>
#include<cassert>
#include<vector>
using namespace std;

/*
*Author：seven17000
*Date：2017.2.18
*Content：实现哈希表
*/

enum Status
{
	EXIST,
	DELETE,
	EMPTY,
};

template<class K, class V>
struct HashNode
{
	K _key;
	V _value;
	Status _status;

	HashNode(const K& key = K(), const V& value = V())
		:_key(key)
		, _value(value)
		, _status(EMPTY)
	{}
};

template<class K>
struct __HashFunc
{
	size_t operator()(const K& key)
	{
		return key;
	}
};

template<>
struct __HashFunc<string>
{
	size_t BKDRHash(const char* str)
	{
		register size_t hash = 0;
		while (*str)
		{
			hash = hash * 131 + *str;
			++str;
		}
		return hash;
	}
	size_t operator()(const string& s)
	{
		return BKDRHash(s.c_str());
	}
};

template<class K, class V, class HashFunc = __HashFunc<K>>
class HashTable
{
	typedef HashNode<K, V> Node;
public:
	HashTable(size_t size)
	{
		assert(size > 0);
		_tables.resize(size);
	}

	~HashTable()
	{}

	pair<Node*, bool> Insert(const K& key, const V& value)
	{

		if (_tables.size() == _size)
		{
			cout << "HashTables is full.";
			//_tables.resize(_size * 2);
			return make_pair((Node*)NULL, false);
		}
		size_t index = _HashFunc(key);
		while (_tables[index]._status == EXIST)
		{
			if (_tables[index]._key == key)
				return make_pair(&_tables[index], false);
			++index;
			if (index == _tables.size())
			{
				index = 0;
			}
		}
		_tables[index]._key = key;
		_tables[index]._value = value;
		_tables[index]._status = EXIST;

		++_size;

		return make_pair(&_tables[index], true);
	}

	Node* Find(const K& key)
	{
		size_t index = _HashFunc(key);
		while (_tables[index]._status != EMPTY)
		{
			if (_tables[index]._key == key)
			{
				if (_tables[index]._status != DELETE)
				{
					return &_tables[index];
				}
				else
				{
					return NULL;
				}
			}
			++index;
			if (index = _tables.size())
			{
				index = 0;
			}
		}
		return NULL;
	}

	bool Remove(const K& key)
	{
		Node* ret = Find(key);
		if (ret)
		{
			ret->_status = DELETE;
			--_size;
			return true;
		}
		return false;
	}

	size_t _HashFunc(const K& key)
	{
		HashFunc hf;
		return hf(key) % _tables.size();
	}

	void Swap(HashTable<K, V>& ht)
	{
		_tables.swap(ht._tables);
		swap(_size, ht._size);
	}

	void CheckCapacity()
	{
		if (_tables.empty())
		{
			_tables.resize(7);
			return;
		}
		if (_size * 10 / _tables.size() >= 7)
		{
			size_t newSize = _tables._size() * 2;
			HashTable<K, V> tmp(newSize);
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				if (_tables[i].status == EXIST)
				{
					tmp.Insert(_tables[i]._key, _tables[i]._value);
				}
			}

			this->Swap(tmp);
		}
	}




protected:
	vector<Node> _tables;
	size_t _size;
};



void Test()
{
	HashTable<int, int> ht1(10);
	ht1.Insert(89, 0);
	ht1.Insert(49, 0);
	ht1.Insert(50, 0);
	ht1.Insert(12, 0);

	HashTable<string, string> h2(20);
	h2.Insert("hash", "table");
	h2.Find("hash");
	h2.Find("table");

}
