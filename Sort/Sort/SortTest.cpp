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

//void AdjustDown(int* arr, size_t root, size_t count)
//{//∂—≈≈–Úµ˜’˚
//	size_t parent = root;
//	size_t child = parent * 2 + 1;
//	while (parent<count)
//	{
//		if (child + 1 < count&&arr[child + 1]>arr[child])
//		{
//			++child;
//		}
//		if (child<count&&arr[child] > arr[parent])
//		{
//			std::swap(arr[child], arr[parent]);
//			parent = child;
//			child = parent * 2 + 1;
//		}
//		else
//		{
//			break;
//		}
//	}
//
//}
//
//void HeapSort(int* arr, size_t size)
//{//∂—≈≈–Ú
//	for (int i = (size - 1) / 2; i >= 0; i--)
//	{
//		AdjustDown(arr, i, size);
//	}
//	size_t end = size - 1;
//	while (end > 0)
//	{
//		swap(arr[0], arr[end]);
//		AdjustDown(arr, 0, end);
//		end--;
//	}
//
//}

//void BubbleSort(int* a, int len)
//{//√∞≈›≈≈–Ú
//	int i = 0;
//	int j = 0;
//	for (i = 0; i < len ; i++)
//	{
//		int flag = 0;
//		for (j = 1; j < len - i; ++j)
//		{
//
//			if (a[j - 1] > a[j])
//			{
//				int tmp = a[j - 1];
//				a[j - 1] = a[j];
//				a[j] = tmp;
//				flag = 1;
//			}
//		}
//		if (flag = 0)
//			return;
//	}
//}

void QuickSort(int* a,int l, int r)
{//øÏ≈≈
	if (l < r)
	{
		
		int i = l, 
		int	j = r, 
		int	x = a[l];
		while (i < j)
		{
			while (i < j && a[j] >= x)
				j--;
			if (i < j)
				a[i++] = a[j];

			while (i < j && a[i] < x)  
				i++;
			if (i < j)
				a[j--] = a[i];
		}
		a[i] = x;

		QuickSort(a, l, i - 1);  
		QuickSort(a, i + 1, r);
	}
}

int main()
{
	int a[] = {1,8,3,6,5,2,4};
	//InsertSort(a, sizeof(a)/sizeof(a[0]));
	//ShellSort(a, sizeof(a) / sizeof(a[0]));
	//SelectSort(a, sizeof(a) / sizeof(a[0]));
	/*HeapSort(a, sizeof(a) / sizeof(a[0]));*/
	/*BubbleSort(a, sizeof(a) / sizeof(a[0]));*/
	QuickSort(a, 0, sizeof(a) / sizeof(a[0])-1);
	for (int i = 0; i < (sizeof(a) / sizeof(a[0]));i++)
		cout << a[i] << ' ';
	return 0;
}