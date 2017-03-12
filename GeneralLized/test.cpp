#define _CRT_SECURE_NO_WARNINGS
#include"GeneralLized.h"

void TestGeneralLized()
{
	char* s = "()";  
	GeneralLized g(s);
	g.PrintGeneralLized();
	cout << "size:" << g.Size() << endl;
	cout << "depth:" << g.Depth() << endl;
	cout << endl;

	char* s1 = "(a,b)";
	GeneralLized g1(s1);
	g1.PrintGeneralLized();
	cout << "size:" << g1.Size() << endl;
	cout << "depth:" << g1.Depth() << endl;
	cout << endl;

	char* s2 = "(a,b,(c,d))";
	GeneralLized g2(s2);
	g2.PrintGeneralLized();
	cout << "size:" << g2.Size() << endl;
	cout << "depth:" << g2.Depth() << endl;
	cout << endl;

	char* s3 = "(a,b,(c,d),(e,(f),h))";
	GeneralLized g3(s3);
	g3.PrintGeneralLized();
	cout << "size:" << g3.Size() << endl;
	cout << "depth:" << g3.Depth() << endl;
	cout << endl;

	char* s4 = "(((),()))";
	GeneralLized g4(s4);
	g4.PrintGeneralLized();
	cout << "size:" << g4.Size() << endl;
	cout << "depth:" << g4.Depth() << endl;
	cout << endl;

	GeneralLized g5(g3);
	g5.PrintGeneralLized();
	cout << "size:" << g5.Size() << endl;
	cout << "depth:" << g5.Depth() << endl;
	cout << endl;

	g4 = g2;
	g4.PrintGeneralLized();
	cout << "size:" << g4.Size() << endl;
	cout << "depth:" << g4.Depth() << endl;
	cout << endl;
}

int main()
{
	TestGeneralLized();
	system("pause");
	return 0;
}