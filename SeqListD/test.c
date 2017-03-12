#define _CRT_SECURE_NO_WARNINGS
#include"SeqListD.h"

//void test()
//{
//	Seq Seq;
//	InitSeqlist(&Seq);
//	PushFront(&Seq, 1);
//	PushFront(&Seq, 2);
//	PushFront(&Seq, 3);
//	PushFront(&Seq, 4);
//	PrintSeq(&Seq);
//}
test()
{
	Seq Seq;
	InitSeqlist(&Seq);
	PushFront(&Seq, 1);
	PushFront(&Seq, 3);
	PushFront(&Seq, 4);
	PushFront(&Seq, 2);
	PushFront(&Seq, 6);
	PushFront(&Seq, 5);
	PrintSeq(&Seq);
	BubbleSort(&Seq, BubbleSort1);
	printf("%d",BinarySearch2(Seq,2));
}
int main()
{
	test();
	system("pause");
	return 0;
}
