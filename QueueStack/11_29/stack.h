#pragma once
#include<iostream>
using namespace std;

template <class T>
class Stack {
private:
	T* _a;
	size_t _capacity;
	int _size;


public:
	Stack()
		:_a(0)
		, _capacity(0)
		, _size(0)
	{}

	~Stack()
	{

	}

	void Push(const T& x) 
	{
		if (_size + 1 == _capacity) 
		{
			_capacity = 2 * _capacity + 3;
			T* tmp = new T(_capacity);
			if (tmp == NULL) 
			{
				exit(-1);
			}
			memcpy(tmp, _a, sizeof(T)*(_size + 1));   
			delete _a;
			_a = NULL;
		} 
		_a[++_size] = x;
	}
	void Pop() 
	{
		if (_size > -1) 
		{
			cout << _a[_size] << endl;
			_size--;
		}
	}
	bool empty() 
	{
		return _size = 0;
	}
};

