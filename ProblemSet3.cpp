#include <iostream>
#include <algorithm>
#include <time.h>

using namespace std;

void printArray(int* pArr, int ARR_SIZE);
void fillArray(int* pArr, int ARR_SIZE);

int* insertionSort(int* pArr, int ARR_SIZE);
int* shellSort(int* pArr, int ARR_SIZE);
int* heapSort(int* pArr, int ARR_SIZE);

void swap(int* A, int* B);
void heapify(int* pArr, int ARR_SIZE, int index);

int main()
{
	srand(time(0));

	// створення динамічного масиву
	const int ARR_SIZE = 20;
	int* pArr = new int[ARR_SIZE];


	fillArray(pArr, ARR_SIZE);
	//cout << "Original array:";
	//printArray(pArr, ARR_SIZE);

	unsigned long t11, t12, t21, t22, t31, t32;

	t11 = clock();
	int* pSorted_array_insertion = insertionSort(pArr, ARR_SIZE);
	t12 = clock() - t11;
	//cout << "Insertion sorted array:";
	//printArray(pSorted_array_insertion, ARR_SIZE);

	t21 = clock();
	int* pSorted_array_heap = heapSort(pArr, ARR_SIZE);
	t22 = clock() - t21;
	//cout << "Heap sorted array:";
	//printArray(pSorted_array_heap, ARR_SIZE);

	t31 = clock();
	int* pSorted_array_shell = shellSort(pArr, ARR_SIZE);
	t32 = clock() - t31;
	//cout << "Shell sorted array:";
	//printArray(pSorted_array_shell, ARR_SIZE);

	cout << fixed << "Time of INSERTION SORT: " << ((double)t12) / CLOCKS_PER_SEC << endl;
	cout << fixed << "Time of HEAP SORT: " << ((double)t22) / CLOCKS_PER_SEC << endl;
	cout << fixed << "Time of SHELL SORT : " << ((double)t32) / CLOCKS_PER_SEC << endl;

	delete[] pArr;

	return 0;
}


int* insertionSort(int* pArr, int ARR_SIZE)
{
	int* pArrCopy = new int[ARR_SIZE];
	copy(pArr, pArr + ARR_SIZE, pArrCopy); // copying original array;


	int key; // current element

	for (int i = 1; i < ARR_SIZE; i++)
	{
		key = pArrCopy[i];

		int j = i - 1;

		// moving elements before pivot to 1 position ahead 
		// from their current position 
		// if they are greater than pivot
		while (pArrCopy[j] > key && j >= 0)
		{
			pArrCopy[j + 1] = pArrCopy[j];
			j--;
		}
		pArrCopy[j+1] = key;
	}

	return pArrCopy; // returning pointer to a sorted array
}

int* heapSort(int* pArr, int ARR_SIZE)
{
	int* pArrCopy = new int[ARR_SIZE];
	copy(pArr, pArr + ARR_SIZE, pArrCopy); // copying original array

	for (int i = ARR_SIZE / 2 - 1; i >= 0; i--)
	{
		heapify(pArrCopy, ARR_SIZE, i);
	}

	for (int i = ARR_SIZE - 1; i > 0; i--)
	{
		swap(pArrCopy[0], pArrCopy[i]);
		//int temp = pArrCopy[0];
		//pArrCopy[0] = pArrCopy[i];
		//pArrCopy[i] = temp;

		heapify(pArrCopy, i, 0);
	}

	return pArrCopy;
}

int* shellSort(int* pArr, int ARR_SIZE)
{
	int* pArrCopy = new int[ARR_SIZE];
	copy(pArr, pArr + ARR_SIZE, pArrCopy); // copying original array

	// starting with a gap = array size / 2, and dividing by 2 every next step
	for (int gap = ARR_SIZE / 2; gap > 0; gap /= 2)
	{
		// adding one more element to array to sort
		for (int i = gap; i < ARR_SIZE; i++)
		{
			int temp = pArrCopy[i]; // saving an element to shift with
			int j;

			// moving elements up if they are greater than temp
			for (j = i; j >= gap && pArrCopy[j - gap] > temp; j -= gap)
			{
				pArrCopy[j] = pArrCopy[j - gap];
			}
			pArrCopy[j] = temp;
		}
	}

	return pArrCopy; // returning pointer to a sorted array
}

void heapify(int* pArr, int ARR_SIZE, int index)
{
	int largest = index;
	int left = 2 * index + 1;
	int right = 2 * index + 2;

	if (left < ARR_SIZE && pArr[left] > pArr[largest])
	{
		largest = left;
	}

	if (right < ARR_SIZE && pArr[right] > pArr[largest])
	{
		largest = right;
	}

	if (largest != index)
	{
		swap(pArr[largest], pArr[index]);

		//int temp = pArr[index];
		//pArr[index] = pArr[largest];
		//pArr[largest] = temp;

		heapify(pArr, ARR_SIZE, largest);
	}

}

void swap(int* A, int* B)
{
	int temp = *A;
	*A = *B;
	*B = temp;
}

void printArray(int* pArr, int ARR_SIZE)
{
	for (int i = 0; i < ARR_SIZE; i++)
	{
		cout << pArr[i] << " ";
	}
	cout << endl;
	cout << endl;
}

// функція заповнення масиву випадковими числами в діапазоні від 0 до 65535
void fillArray(int* pArr, int ARR_SIZE)
{
	for (int i = 0; i < ARR_SIZE; i++)
	{
		pArr[i] = -(0) + rand() % (2 * 65535 + 1);
	}
}
