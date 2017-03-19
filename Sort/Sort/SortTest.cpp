#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//void InsertSort(int* arr,int len)
//{//≤Â»Î≈≈–Ú
//	int i = 0;
//	int j = 0;
//	int key = 0;
//	for (i = 1; i < len; ++i)
//	{
//		key = arr[i];
//		for (j = i - 1; j >= 0; --j)
//		{
//			if (key < arr[j])
//				arr[j+1] = arr[j];
//			else
//				break;
//		}
//		arr[j+1] = key;
//	}
//}
//


//void ShellSort(int* arr,int len)
//{//œ£∂˚≈≈–Ú
//	int i = 0;
//	int j = 0;
//	int gap = len/2;//≤Ω≥§
//	for (gap = len/2; gap > 0; gap /= 2)
//	{
//		for (i = 0; i < gap; i++)
//		{
//			for (j = i + gap; j < len; j += gap)
//			{
//				if (arr[j]<arr[j-gap])
//				{
//					int tmp = arr[j];
//					int k = j - gap;
//					while (k >= 0 && arr[k]>tmp)
//					{
//						arr[k + gap] = arr[k];
//						k -= gap;
//					}
//					arr[k + gap] = tmp;
//				}
//			}
//		}
//
//	}
//}

//void SelectSort(int* a,int len)
//{//—°‘Ò≈≈–Ú
//	int i = 0;
//	int j = 0;
//	for (i = 0; i < len; ++i)
//	{
//		int min = a[i];
//		int index = i;
//		int tmp = 0;
//		for (j = i + 1; j < len; ++j)
//		{
//			if (min > a[j])
//			{
//				min = a[j];
//				index = j;
//			}
//		}
//		tmp = a[i];
//		a[i] = min;
//		a[index] = tmp;;
//	}
//}

int main()
{
	int a[] = {1,8,3,6,5,2,4,9};
	//InsertSort(a, sizeof(a)/sizeof(a[0]));
	//ShellSort(a, sizeof(a) / sizeof(a[0]));
	SelectSort(a, sizeof(a) / sizeof(a[0]));
	for (int i = 0; i < (sizeof(a) / sizeof(a[0]));i++)
		cout << a[i] << ' ';
	return 0;
}