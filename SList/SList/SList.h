#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<assert.h>

typedef int DataType;
typedef struct Node
{
	DataType data;
	struct Node* next;   
}Node, *PNode;

void InitList(PNode* PHead);//��ʼ��������
void PushBack(PNode* PHead);//β��
void PopBack(PNode* PHead);//βɾ
void PushFront(PNode* PHead);//ͷ��
void PopFront(PNode* PHead);//ͷɾ

void Destroy(PNode* PHeaf);//���ٵ�����
PNode Find(PNode* PHead,DataType data);//����
void Insert(PNode pos, DataType data);//������
PNode EndNode(PNode *pHead);//�������һ���ڵ�
PNode ByeNode(PNode* PHead);//����һ�����
void PrintList(PNode* PHead);//��ӡ������

void EraseNotTail(PNode pos);//ɾ����ͷ������ķ�β���
void InsertFrontNode(PNode pos, DataType data);//�ڵ�ǰ�ڵ�ǰ����һ������data
void Erase(PNode* pHead, PNode pos);//ɾ��posλ�õĽ��
void Remove(PNode* pHead, DataType data);//ɾ�������е�һ��ֵΪdata�Ľ��
void RemoveAll(PNode* pHead, DataType data);//ɾ������ֵΪdata�Ľ��

PNode EndNode(PNode *pHead);//�������һ���ڵ� 
PNode JosephCycle(PNode* PHead, int num);//Լɪ������
PNode FindMidNode(PNode PHead);//�����м���
PNode FindTailK(PNode PHead);//���ҵ�����k����� 
void PrintListFromT2H(PNode pHead);//�����ӡ����
void DeleteNotTail(PNode pos);//ɾ����β���
void InsertNotHead(PNode pHead, PNode pos, DataType data);//�ڷ�ͷ���ǰ������
PNode FindLastKNode(PNode pHead, int k);//�ҵ����һ��Ϊk�Ľ��
PNode ReverseList(PNode pHead);//��������

void BubbleSort(PNode pHead);//ð������
PNode MergeList(PNode pList1, PNode pList);//�ϲ�������
int IsCross(PNode pHead1, PNode pHead2);//�ж��������Ƿ��ཻ
PNode GetCrossNode(PNode pHead1, PNode pHead2);//��ȡ������Ľ���
PNode HasCircle(PNode pHead);//�ж������Ƿ�ɻ�
int GetCirclrLen(PNode pMeetNode);//��ȡ���ĳ���
PNode UnionSet(Node *list1, Node *list2);//��������������������ͬ������----��ӡ���� 
PNode GetInterNode(PNode pHead, PNode pMeetNode);//��ȡ������ڵ�  
