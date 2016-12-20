#pragma once
#include<iostream>
using namespace std;
template<class T>
struct Node
{
	Node<T> * _next;
	T _data;

	Node(const T& x)
		:_data(x)
		,_next(NULL)
	{}
};

template<class T>
class Queue
{
	typedef Node<T> Node;
public:
	Queue()
	{
		Node._next = NULL;
		Node._data = 0;
		pHead = pTail = &Node;
	}

	~Queue()
	{
		Node *temp;
		while (pHead != NULL)
		{
			temp = pHead;
			pHead = pHead->_next;
			delete temp;
		}
	}

	void Push(const T& _data)
	{
		NODE* pTemp = (NODE*)malloc(sizeof(NODE));
		if (!pTemp)return false;
		pTemp->next = NULL;
		pTemp->Item = Item;

		pTail->next = pTemp;
		pTail = pTemp;
		return true;
	}
	T Pop()
	{
		if (IsEmpty())
			return false;
		NODE* pTemp = NULL;

		pTemp = pHead->next;
		pHead->next = pTemp->next;

		T rst = pTemp->Item;
		delete pTemp;
		return rst;
	}

	bool IsEmpty() 
	{ 
		return _pHead == _pTail;
	}

private:
	Node* pHead, *pTail;
};


