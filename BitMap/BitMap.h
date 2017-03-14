#pragma once
#include<iostream>
#include<vector>
using namespace std;

/*
*Authotr:Seven17000
*Date:2017.03.12
*Content:ʵ��λͼ
*/

class BitMap
{
public:
	BitMap(size_t size = 100)
	{//���캯��
	 //sizeΪҪ����ĵ���������
	 //һ�����Ϳ��Դ��32������״̬
	 //��������vector��sizeΪsize/32
		_v.resize((size >> 5) + 1);
	}

	void Set(size_t x)
	{//��xλ�õ�״̬��һ
		if (x / 32 > _v.size())
		{
			cout << "����" << x << "������Χ" << endl;
			return;
		}

		size_t index = x >> 5;
		size_t num = x % 32;

		_v[index] |= 1 << (num - 1);
	}

	void Reset(size_t x)
	{//��xλ�õ�״̬������
		if (x / 32 > _v.size())
		{
			cout << "����" << x << "������Χ" << endl;
			return;
		}

		size_t index = x >> 5;
		size_t num = x % 32;

		_v[index] ^= 1 << (num - 1);

	}

	int Find(size_t x)
	{//����xλ�õ�״̬������
		if (x/32 > _v.size())
		{
			cout << "����"<<x<<"������Χ" << endl;
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