#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<assert.h>

typedef int DataType;
typedef struct Node
{
	DataType data;
	struct Node* next;   
}Node, *PNode;

void InitList(PNode* PHead);//初始化单链表
void PushBack(PNode* PHead);//尾插
void PopBack(PNode* PHead);//尾删
void PushFront(PNode* PHead);//头插
void PopFront(PNode* PHead);//头删

void Destroy(PNode* PHeaf);//销毁单链表
PNode Find(PNode* PHead,DataType data);//查找
void Insert(PNode pos, DataType data);//插入结点
PNode EndNode(PNode *pHead);//返回最后一个节点
PNode ByeNode(PNode* PHead);//创建一个结点
void PrintList(PNode* PHead);//打印单链表

void EraseNotTail(PNode pos);//删除无头单链表的非尾结点
void InsertFrontNode(PNode pos, DataType data);//在当前节点前插入一个数据data
void Erase(PNode* pHead, PNode pos);//删除pos位置的结点
void Remove(PNode* pHead, DataType data);//删除链表中第一个值为data的结点
void RemoveAll(PNode* pHead, DataType data);//删除所有值为data的结点

PNode EndNode(PNode *pHead);//返回最后一个节点 
PNode JosephCycle(PNode* PHead, int num);//约瑟夫环问题
PNode FindMidNode(PNode PHead);//查找中间结点
PNode FindTailK(PNode PHead);//查找倒数第k个结点 
void PrintListFromT2H(PNode pHead);//逆序打印链表
void DeleteNotTail(PNode pos);//删除非尾结点
void InsertNotHead(PNode pHead, PNode pos, DataType data);//在非头结点前插入结点
PNode FindLastKNode(PNode pHead, int k);//找到最后一个为k的结点
PNode ReverseList(PNode pHead);//逆序单链表

void BubbleSort(PNode pHead);//冒泡排序
PNode MergeList(PNode pList1, PNode pList);//合并单链表
int IsCross(PNode pHead1, PNode pHead2);//判断两链表是否相交
PNode GetCrossNode(PNode pHead1, PNode pHead2);//获取两链表的交点
PNode HasCircle(PNode pHead);//判断链表是否成环
int GetCirclrLen(PNode pMeetNode);//获取环的长度
PNode UnionSet(Node *list1, Node *list2);//求两个已排序单链表中相同的数据----打印出来 
PNode GetInterNode(PNode pHead, PNode pMeetNode);//获取环的入口点  
