#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include "SeqListD.h"

void InitSeqlist(pSeq Seq)
{//��ʼ��
	assert(Seq);
	Seq->capacity = 3;
	Seq->array = (DataType*)malloc(sizeof(DataType)*Seq->capacity);
	memset(Seq->array, 0, sizeof(DataType) * 3);
	Seq->size = 0;
}
int Empty(pSeq Seq)
{//�п�
	assert(Seq);
	if (0 == Seq->size)
	{
		return 1;
	}
	return 0;
}
void PopBack(pSeq Seq)
{//βɾ
	assert(Seq);
	if (Empty(Seq))
		return 0;
	Seq->size--;
}
void PushBack(pSeq Seq, DataType data)
{//β��
	assert(Seq && data);
	if (Seq->size >= Seq->capacity)
	{
		DataType* temp;
		Seq->capacity *= 2;
		temp = (DataType*)malloc(sizeof(DataType)*Seq->capacity);
		memcpy(temp, Seq->array, sizeof(DataType)*Seq->size);
		Seq->array = temp;
	}
	Seq->array[Seq->size++] = data;
}
void PopFront(pSeq Seq)
{//ͷɾ
	int i = 0;
	assert(Seq);
	if (Empty(Seq))
		return 0;
	for (i = 0; i < Seq->size - 1; i++)
	{
		Seq->array[i] = Seq->array[i + 1];
	}
	Seq->size--;
}
void PushFront(pSeq Seq, DataType data)
{//ͷ��
	int i = 0;
	assert(Seq && data);
	if (Seq->size >= Seq->capacity)
	{
		DataType* temp;
		Seq->capacity *= 2;
		temp = (DataType*)malloc(sizeof(DataType)*Seq->capacity);
		memcpy(temp, Seq->array, sizeof(DataType)*Seq->size);
		Seq->array = temp;
	}
	for (i = Seq->size; i > 0; i--)
	{
		Seq->array[i] = Seq->array[i - 1];
	}
	Seq->array[0] = data;
	Seq->size++;

}
void PrintSeq(pSeq Seq)
{//��ӡ
	int i = 0;
	assert(Seq);
	for (i = 0; i < Seq->size; i++)
		printf("%d", Seq->array[i]);
	printf("\n");
}
void BubbleSort1(pSeq Seq)
{//ð������
	int i = 0;
	int j = 0;
	int flag = 0;
	assert(Seq);
	for (j = 0; j < Seq->size; j++)
	{
		flag = 1;
		for (i = 0; i < Seq->size - j - 1; i++)
		{
			if (Seq->array[i]>Seq->array[i + 1])
			{
				DataType temp = Seq->array[i];
				Seq->array[i] = Seq->array[i + 1];
				Seq->array[i + 1] = temp;
				flag = 0;
			}
		}
		if (flag)
			return 0;
	}
}

void BubbleSort2(pSeq Seq)
{//ð�ݽ���
	int i = 0;
	int j = 0;
	int flag = 0;
	assert(Seq);
	for (i = 0; i < Seq->size; i++)
	{
		flag = 1;
		for (j = 0; j < Seq->size - i - 1; j++)
		{
			if (Seq->array[j] < Seq->array[j + 1])
			{
				DataType temp = Seq->array[j];
				Seq->array[j] = Seq->array[j + 1];
				Seq->array[j + 1] = temp;
				flag = 0;
			}
		}
		if (flag)
			return 0;
	}
}

void BubbleSort(pSeq Seq, void(*op)(pSeq))
{//�ص������ǼǺ���
	assert(Seq);
	op(Seq);
}
void SelectSort(pSeq Seq)
{//ѡ��������
	int i = 0;
	int j = 0;
	int min = 0;
	assert(Seq);
	for (j = 0; j < Seq->size; j++)
	{
		min = j;
		for (i = j + 1; i < Seq->size - j - 1; i++)
		{
			if (Seq->array[min] > Seq->array[i])
			{
				min = i;
			}
			DataType temp = 0;
			temp = Seq->array[i];
			Seq->array[i] = Seq->array[min];
			Seq->array[min] = temp;
		}
	}
}

int BinarySearch(pSeq Seq, DataType data)
{//����
	assert(Seq);
	int left = 0;
	int right = Seq->size - 1;
	int mid = left + (right - left) >> 1;
	assert(Seq && data);
	while (left <= right)
	{
		if (Seq->array[mid] > data)
			right = mid - 1;
		else if (Seq->array[mid] < data)
			left = mid + 1;
		else
			return mid;
	}
}

int BinarySearch2(pSeq Seq,DataType data,int left,int right)
{//�ݹ����
	assert(Seq&& (right < Seq->size));
	int mid = left + (right - left) >> 1;
	if (data<Seq->array[mid])
	{
		BinarySearch2(Seq,data,left,mid-1);
	}
	else if (data>Seq->array[mid])
	{
		BinarySearch2(Seq, data, mid, right);                     
	}
	else
	{
		return mid;
	}
}

int Size(pSeq Seq)
{//�жϴ�С
	assert(Seq);
	return Seq->size;
}

void Clear(pSeq Seq)
{//���
	asserr(Seq);
	Seq->size = 0;
}
