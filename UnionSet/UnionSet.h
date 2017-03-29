#define _CRT_SECURE_NO_WARNINGS
#include<vector>
#include<iostream>
using namespace std;

/*
* Author:Seven17000
* date:2017.03.29
* Content:���鼯��ʵ��,�����������
* ������֪��n���˺�m�Ժ��ѹ�ϵ������
*����r�������������ֱ�ӻ��ӵĺ���
*�����ѵĺ��ѵĺ���...��������Ϊ����
*����ͬһ������Ȧ����д���������n��
*����һ���ж��ٸ�����Ȧ��
*���磺n = 5��m = 3��
*r = {{1 , 2} , {2 , 3} , {4 , 5}}
*��ʾ��5���ˣ�1��2�Ǻ��ѣ�2��3�Ǻ���
*4��5�Ǻ��ѣ���1��2��3����һ������Ȧ
*4��5������һ������Ȧ�����Ϊ2������
*Ȧ��
*/

class UnionSet
{
public:
	UnionSet(size_t n)
	{//���캯������ʼÿ��Ԫ�س�ʼΪ-1
		v.resize(n+1,-1);
	}

	int Find(size_t x)
	{//����x�ĸ����
		size_t tmp = x;
		while (v[tmp] >= 0)
		{
			tmp = v[tmp];
		}

		return tmp;
	}

	void Union(size_t x, size_t y)
	{//�ϲ�����Ԫ��
		size_t root1 = Find(x);
		size_t root2 = Find(y);

		if (root1 == root2)
			return;

		v[root1] += v[root2];
		v[root2] = root1;
	}

	size_t IsInSet(size_t x, size_t y)
	{//�ж�����Ԫ���Ƿ���һ������
		return Find(x) == Find(y);
	}

	size_t SetCount()
	{//������������
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