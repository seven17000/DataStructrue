#define _CRT_SECURE_NO_WARNINGS
#include"SList.h"

void InitList(PNode* PHead)//初始化
{
	assert(PHead);
	*PHead = NULL;
}

PNode ByeNode(DataType data)//申请一个结点
{
	PNode newNode = NULL;
	newNode = (PNode)malloc(sizeof(Node));
	if (NULL == newNode)
	{
		printf("out of memory.\n");
		exit(1);
	}
	else
	{
		newNode->data = data;
		newNode->next = NULL;
	}
	return newNode;
}

void PopBack(PNode* PHead)//尾删
{
	assert(PHead);
	if (NULL == *PHead)
	{
		return;
	}
	else if(NULL == (*PHead)->next)
	{
		free(*PHead);
		*PHead = NULL;
	}
	else
	{
		PNode PCur = *PHead;
		while (PCur->next->next)
		{
			PCur = PCur->next;
		}
		free(PCur->next);
		PCur->next = NULL;
	}
}

void PushBack(PNode* PHead, DataType data)//尾插
{
	assert(PHead);
	if (NULL == *PHead)
	{
		*PHead = ByeNode(data);
	}
	else
	{
		PNode PCur = NULL;
		PCur = *PHead;
		while (PCur->next)
		{
			PCur = PCur->next;
		}
		PCur->next = ByeNode(data);
	}
}

void PushFront(PNode *PHead, DataType data)//头插
{
	assert(PHead);
	PNode PreNode = NULL;
	PNode Node = ByeNode(data);
	PreNode = *PHead;
	Node->next = PreNode;
	*PHead = Node;
}

void PopFront(PNode *PHead)//头删
{
	assert(PHead);
	PNode PreNode = *PHead;
	if (NULL == *PHead)
	{
		return;
	}
	else if (NULL == (*PHead)->next)
	{
		free(*PHead);
		*PHead = NULL;
	}
	else
	{
		*PHead = PreNode->next;
		free(PreNode);
		PreNode = NULL;
	}
}

PNode Find(PNode* PHead, DataType data)//查找
{
	assert(PHead);
	PNode PCur = *PHead;
	while (PCur)
	{
		if (data == PCur->data)
			break;
		PCur = PCur->next;
	}
	return PCur;
}

void Destroy(PNode* PHead)//销毁
{
	assert(PHead);
	PNode PCur = *PHead;
	while (PCur->next)
	{
		PNode Dnode = PCur;
		PCur = PCur->next;
		free(Dnode);
		Dnode = NULL;
	}
}

int Empty(PNode PHead)//判空
{
	if (NULL == PHead)
		return 0;
	else
		return 1;
}

int Size(PNode PHead)//求链表中结点的个数
{ 
	PNode Node = PHead;
	DataType num = 0;
	while (Node)
	{
		num++;
		Node = Node->next;
	}
	return num;
}

void PrintList(PNode* PHead)//打印单链表
{
	PNode PCur = *PHead;
	assert(PHead);
	while (PCur)
	{
		printf("%d->",PCur->data);
		PCur = PCur->next;
	}
	printf("NULL\n");
}

void Insert(PNode pos, DataType data)//在data后插入结点
{
	PNode newNode = ByeNode(data);
	PNode PreNode = pos;
	newNode->next = PreNode->next;
	PreNode->next = newNode;
}

void EraseNotTail(PNode pos)//删除无头单链表的非尾结点
{
	if ((NULL == pos) || (NULL == pos->next))
	{
		return 0;
	}

	PNode NextNode = pos->next;
	pos->data = NextNode->data;
	pos->next = NextNode->next;
	free(NextNode);
	NextNode = NULL;

}

void InsertFrontNode(PNode pos, DataType data)//在当前节点前插入一个数据data
{
	if (NULL == pos)
	{
		return 0;
	}

	DataType temp = NULL;
	PNode PCur = ByeNode(data);
	PCur->next = pos->next;
	pos->next = PCur;
	temp = pos->data;
	pos->data = PCur->data;
	PCur->data = temp;

}

void Erase(PNode* pHead, PNode pos)//删除pos位置结点
{
	PNode CurNode = *pHead;
	assert(pHead);
	if (NULL == CurNode)  
		return;
	else if (NULL == CurNode->next)  
	{
		if (CurNode == pos)
		{
			free(CurNode);
			*pHead = NULL;
		}
		else
		{
			return;
		}
	}
	else
	{
		PNode PreNode = *pHead;
		if (*pHead == pos)//第一个元素即为pos  
		{
			CurNode = CurNode->next;
			PreNode = CurNode;
			free(pos);
			pos = NULL;
			*pHead = PreNode;
			return;
		}
		while ((CurNode != pos) && CurNode)
		{
			PreNode = CurNode;
			CurNode = CurNode->next;
		}
		if (CurNode == NULL)
		{
			printf("没找到需要删除的位置\n");
			return;
		}
		else
		{
			PreNode->next = CurNode->next;
			free(pos);
			pos = NULL;
		}
	}
}

void Remove(PNode* pHead, DataType data)//删除链表中第一个值为data的结点
{
	PNode CurNode = *pHead;
	assert(pHead);
	if (NULL == CurNode)
		return;
	else
	{
		PNode PreNode = *pHead;
		while (CurNode->data != data)
		{
			PreNode = CurNode;
			CurNode = CurNode->next;
		}
		if (CurNode == NULL)
		{
			printf("没找到需要删除的位置\n");
			return;
		}
		else
		{
			PreNode->next = CurNode->next;
			free(CurNode);
			CurNode = NULL;
		}
	}
}

void RemoveAll(PNode* pHead, DataType data)//删除所有值为data的结点
{
	PNode CurNode = *pHead;
	PNode PreNode = *pHead;
	assert(pHead);
	if (NULL == CurNode)//链表无元素  
		return;
	while (*pHead)//判断第一个元素  
	{
		if (NULL == CurNode->next)//只有一个元素  
		{
			if (CurNode->data == data)
			{
				free(CurNode);
				*pHead = NULL;
				return;
			}
		}
		else if ((*pHead)->data == data)//有多个元素，且第一个元素的值为data  
		{
			*pHead = CurNode->next;
			free(CurNode);
			CurNode = *pHead;
		}
		else
			break;
	}
	CurNode = CurNode->next;
	PreNode = *pHead;
	while (CurNode)
	{
		if (CurNode->data == data)
		{
			PreNode->next = CurNode->next;
			free(CurNode);
			CurNode = PreNode;
		}
		PreNode = CurNode;
		CurNode = CurNode->next;
	}
}

PNode EndNode(PNode *pHead)//返回最后一个节点  
{
	PNode CurNode = *pHead;
	assert(pHead);
	while (CurNode->next)
	{
		CurNode = CurNode->next;
	}
	return CurNode;
}

PNode JosephCycle(PNode* PHead, int num)//约瑟夫环问题
{
	int count = num;
	PNode CurNode = NULL;
	PNode PreNode = NULL;
	assert(PHead);
	if (NULL == *PHead)
		return NULL;
	else
	{
		CurNode = EndNode(PHead);  
		CurNode->next = *PHead;  
		CurNode = *PHead;
		while (CurNode->next != CurNode)
		{
			count = num;
			while (--count)
			{
				PreNode = CurNode;
				CurNode = CurNode->next;
			}
			PreNode->next = CurNode->next;
			free(CurNode);
			CurNode = PreNode->next;
		}
		return CurNode;
	}
}

PNode FindMidNode(PNode PHead)//查找中间结点
{
	PNode pFast = PHead;
	PNode pSlow = PHead;
	while (pFast->next && pFast->next->next)//如果元素个数为偶数，则返回前面的中间值  
	{
		pFast = pFast->next->next;
		pSlow = pSlow->next;
	}
	return pSlow;
}

PNode FindLastK(PNode pHead, int k)//查找链表的倒数第k个节点  
{
	PNode pFast = pHead;
	PNode pSlow = pHead;
	if (NULL == pHead)
		return;
	else
	{
		while (--k)
		{
			pFast = pFast->next;
		}
		while (pFast->next)
		{
			pFast = pFast->next;
			pSlow = pSlow->next;
		}
		return pSlow;
	}
}

PNode ReserseLinkList(PNode *pHead)//逆置单链表  
{
	PNode PreNode = NULL;
	PNode CurNode = NULL;
	PNode NextNode = NULL;
	assert(pHead);
	if (NULL == *pHead || NULL == (*pHead)->next)
		return NULL;
	else
	{
		PreNode = *pHead;
		CurNode = PreNode->next;
		NextNode = CurNode->next;
		(*pHead)->next = NULL;
		while (NextNode->next)
		{
			NextNode = CurNode->next;
			CurNode->next = PreNode;
			PreNode = CurNode;
			CurNode = NextNode;
		}
		NextNode->next = PreNode;//将最后一个元素连接上  
		return NextNode;
	}
}

void Bubbleort(PNode pHead)//冒泡排序  
{
	int flag = 0;
	PNode CurNode = NULL;
	PNode TailNode = NULL;
	assert(pHead);
	if (NULL == pHead || NULL == (pHead)->next)
		return;
	CurNode = pHead;
	while (TailNode != pHead)
	{
		flag = 0;
		CurNode = pHead;
		while (CurNode->next != TailNode)
		{
			if (CurNode->data > CurNode->next->data)
			{
				DataType temp = CurNode->data;
				CurNode->data = CurNode->next->data;
				CurNode->next->data = temp;
				flag = 1;
			}
			CurNode = CurNode->next;
		}
		TailNode = CurNode;
		if (flag == 0)
			break;
	}
}

PNode MergeList(PNode pList1, PNode pList2)//合并两个有序链表
{
	PNode p1 = pList1;
	PNode p2 = pList2;
	PNode NewNode = NULL;
	PNode pNewHead = NewNode;
	if (NULL == pList2)
		return pList1;
	if (NULL == pList1)
		return pList2;
	else
	{
		if (p1->data < p2->data)
		{
			NewNode = p1;
			p1 = p1->next;
		}
		else
		{
			NewNode = p2;
			p2 = p2->next;
		}
		pNewHead = NewNode;
		while (p1 && p2) 
		{
			if (p1->data < p2->data)
			{
				NewNode->next = p1;
				NewNode = p1;
				p1 = p1->next;
			}
			else
			{
				NewNode->next = p2;
				NewNode = p2;
				p2 = p2->next;
			}
		}
		if (NULL == p1)
		{
			NewNode->next = p2;
		}
		if (NULL == p2)
		{
			NewNode->next = p1;
		}
		return pNewHead;
	}
}

int IsCross(PNode pList1, PNode pList2)//判断链表是否相交  
{
	PNode p1 = pList1;
	PNode p2 = pList2;
	if (NULL == pList2 || NULL == pList1)
		return 0;
	while (p1->next)
	{
		p1 = p1->next;
	}
	while (p2->next)
	{
		p2 = p2->next;
	}
	if (p1 == p2)
		return 1;
	else
		return 0;
}

PNode UnionSet(Node *list1, Node *list2)//求两个已排序单链表中相同的数据打印出来  
{
	PNode p1 = list1;
	PNode p2 = list2;
	PNode p3 = NULL;
	PNode newHead = p3;
	if (NULL == list1 || NULL == list2)
		return NULL;
	while (!p3)
	{
		if (p1->data == p2->data)
		{
			p3 = p1;
			newHead = p3;
			while (p1->data == p1->next->data)
			{
				p1 = p1->next;
			}
			p1 = p1->next;
			while (p2->data == p2->next->data)
			{
				p2 = p2->next;
			}
			p2 = p2->next;
		}
		else if (p1->data < p2->data)
			p1 = p1->next;
		else
			p2 = p2->next;
	}

	while (p1 && p2)
	{
		if (p1->data == p2->data)
		{
			p3->next = p1;
			p3 = p3->next;
			if (!p1->next || !p2->next)
				break;
			while (p1->data == p1->next->data)
			{
				p1 = p1->next;
			}
			p1 = p1->next;
			while (p2->data == p2->next->data)
			{
				p2 = p2->next;
			}
			p2 = p2->next;
		}
		else if (p1->data < p2->data)
			p1 = p1->next;
		else
			p2 = p2->next;
	}
	p3->next = NULL;
	return newHead;
}

PNode HasCircle(PNode pHead)//判断链表是否带环  
{
	PNode pFast = NULL;
	PNode pSlow = NULL;
	if (NULL == pHead)
	{
		return NULL;
	}
	pFast = pHead;
	pSlow = pHead;
	while (pFast && pFast->next)
	{
		pFast = pFast->next->next;
		pSlow = pSlow->next;
		if (pFast == pSlow)
			break;
	}
	if (pFast == pSlow && pFast != pHead)
		return pFast;
	else
		return NULL;
}

PNode GetInterNode(PNode pHead, PNode pMeetNode)//获取环的入口点  
{
	PNode pH = pHead;
	PNode pM = pMeetNode;
	if (NULL == pHead || NULL == pMeetNode)
		return NULL;
	while (pH != pM)
	{
		pH = pH->next;
		pM = pM->next;
	}
	return pM;
}

int GetCirclrLen(PNode pMeetNode)//如果带环，求环的长度  
{
	int len = 1;
	PNode CurNode = pMeetNode;
	if (NULL == pMeetNode)
		return 0;
	while (CurNode->next != pMeetNode)
	{
		CurNode = CurNode->next;
		len++;
	}
	return len;
}

