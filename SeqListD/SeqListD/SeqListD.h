#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifndef  _SEQLISTD_H
#define  _SEQLISTD_H 

/*
*Author：seven17000
*Date：2017.02.28
*Content：实现动态增长单链表
*/


#include <stdio.h>
#include <assert.h>

typedef int DataType;
typedef struct SeqListD
{
	DataType* array;
	int capacity;
	int size;
}Seq, *pSeq;

void InitSeqlist(pSeq Seq);
void PopBack(pSeq Seq);
void PushBack(pSeq Seq, DataType data);
void PopFront(pSeq Seq);
void PushFront(pSeq Seq, DataType data);
void PrintSeq(pSeq Seq);
void BubbleSort1(pSeq Seq);
void BubbleSort2(pSeq Seq);
void BubbleSort(pSeq Seq, void(*op)(pSeq));
void SelectSort(pSeq Seq);
int BinarySearch(pSeq Seq, DataType data);
int BinarySearch(pSeq Seq, DataType data, int left, int right);
int Size(pSeq Seq);
void Clear(pSeq Seq);


#endif _SEQLISTD_H
