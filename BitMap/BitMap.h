#pragma once
#include<iostream>
#include<vector>
using namespace std;

/*
*Authotr:Seven17000
*Date:2017.03.12
*Content:实现位图
*/

class BitMap
{
public:
	BitMap(size_t size = 100)
	{//构造函数
	 //size为要处理的的数据总数
	 //一个整型可以存放32个数据状态
	 //所以这里vector的size为size/32
		_v.resize((size >> 5) + 1);
	}

	void Set(size_t x)
	{//将x位置的状态置一
		if (x / 32 > _v.size())
		{
			cout << "参数" << x << "超出范围" << endl;
			return;
		}

		size_t index = x >> 5;
		size_t num = x % 32;

		_v[index] |= 1 << (num - 1);
	}

	void Reset(size_t x)
	{//将x位置的状态的置零
		if (x / 32 > _v.size())
		{
			cout << "参数" << x << "超出范围" << endl;
			return;
		}

		size_t index = x >> 5;
		size_t num = x % 32;

		_v[index] ^= 1 << (num - 1);

	}

	int Find(size_t x)
	{//查找x位置的状态并返回
		if (x/32 > _v.size())
		{
			cout << "参数"<<x<<"超出范围" << endl;
			return false;
		}

		size_t index = x >> 5;
		size_t num = x % 32;

		return (_v[index] >> (num - 1)) & 1;
	}

private:
	vector<size_t>  _v;
};

int BitMapTest()
{
	BitMap bm;
	bm.Set(1);
	bm.Set(2001);
	cout << bm.Find(1) << endl;
	cout << bm.Find(2) << endl;
	
	bm.Reset(1);
	cout << bm.Find(1) << endl;
	return 0;
}