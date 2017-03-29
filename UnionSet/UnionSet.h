#define _CRT_SECURE_NO_WARNINGS
#include<vector>
#include<iostream>
using namespace std;

/*
* Author:Seven17000
* date:2017.03.29
* Content:并查集的实现,解决如下问题
* 假如已知有n个人和m对好友关系（存于
*数字r）如果两个人是直接或间接的好友
*（好友的好友的好友...），则认为他们
*属于同一个朋友圈，请写程序求出这n个
*人里一共有多少个朋友圈。
*假如：n = 5，m = 3，
*r = {{1 , 2} , {2 , 3} , {4 , 5}}
*表示有5个人，1和2是好友，2和3是好友
*4和5是好友，则1、2、3属于一个朋友圈
*4、5属于另一个朋友圈，结果为2个朋友
*圈。
*/

class UnionSet
{
public:
	UnionSet(size_t n)
	{//构造函数，初始每个元素初始为-1
		v.resize(n+1,-1);
	}

	int Find(size_t x)
	{//查找x的根结点
		size_t tmp = x;
		while (v[tmp] >= 0)
		{
			tmp = v[tmp];
		}

		return tmp;
	}

	void Union(size_t x, size_t y)
	{//合并两个元素
		size_t root1 = Find(x);
		size_t root2 = Find(y);

		if (root1 == root2)
			return;

		v[root1] += v[root2];
		v[root2] = root1;
	}

	size_t IsInSet(size_t x, size_t y)
	{//判断两个元素是否在一棵树下
		return Find(x) == Find(y);
	}

	size_t SetCount()
	{//计算树的数量
		size_t count = 0;
		for (int i = 0; i < v.size(); ++i)
		{
			if (v[i] > 0)
				count++;
		}

		return count-1;
	}

private:
	vector<int> v;
};

int Test()
{
	int arr[3][2] = { {1,2},{2,3},{4,5} };
	UnionSet U(5);
	for (size_t i = 0; i < 3; ++i)
	{
		U.Union(arr[i][0], arr[i][1]);
	}
	cout << U.SetCount() << endl;
	return 0;
}