#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <time.h>
#include <math.h>
using namespace std;
const int maxs = 10000;

void readem(int a[])
{
	int i;
	ifstream inf("p4.dat");
	i = 0;
	while (!inf.eof())
	{
		inf >> a[i];
		i++;
		
	}
}
void printem(int a[], ofstream& outf, string name, int count, double difftime)
{
	int inc = maxs / 10;
	int j = 1;

	outf << setw(32) << name << endl << endl;
	outf << setw(27) << "Steps =  " << count << endl << endl;
	outf << setw(25) << "Time =  " << difftime/CLOCKS_PER_SEC << " seconds" << endl << endl;
	
	for (int i = 0; i < maxs; i+= inc)
	{
		outf << setw(10) << a[i];
		j++;
		if (j >= 6)
		{
			outf << endl;
			j = 1;
		}

	}
	for (int i = 0; i < 51; i++) outf << '-';
	outf << endl << endl;

}
void swapem(int &a, int &b, int &count)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
	count += 3;
}
void bblsort(int a[], int numc, int &count)
{
	int i, j;
	for (j = 0; j < numc - 1; j++)
		for (i = 0; i < numc - 1; i++)
			if (a[i] > a[i + 1]) swapem(a[i], a[i + 1], count);
	
}
void merge(int x[], int z[], int L, int m, int n, int &count) {
	int i, j, k, t;
	i = L;
	k = L;
	j = m + 1;
	while ((i <= m) && (j <= n))
		if (x[i] <= x[j])
			z[k++] = x[i++];
		else
			z[k++] = x[j++];
	if (i > m)
		for (t = j; t <= n; t++) {
			z[k + t - j] = x[t];
			count++;
		}

	else
		for (t = i; t <= m; t++)
		{
			z[k + t - i] = x[t];
			count++;
		}

}
void mergepass(int x[], int y[], int &n, int &L, int &count) {
	int i, t;
	i = 0;
	while (i <= n - 2 * L + 1) {
		merge(x, y, i, i + L - 1, i + 2*L -1 , count);
		i = i + 2 * L;
	}
	if ((i + L - 1) < n)
		merge(x, y, i, i + L -1, n, count);
	else
		for (t = i; t <= n; t++) y[t] = x[t];
}
void mergesort(int x[], int n, int &count)
{
	int L, y[maxs];
	L = 1;
	while (L < n)
	{
		mergepass(x, y, n, L, count);
		L = 2 * L;
		mergepass(y, x, n, L, count);
		L = 2 * L;
	}
}

int partition(int a[], int low, int high, int &count)
{
	int pivot = a[high]; 
	int i = (low - 1);  

	for (int j = low; j <= high - 1; j++)
	{
		if (a[j] < pivot)
		{
			i++;  
			swapem(a[i], a[j], count);
		}
	}
	swapem(a[i + 1], a[high], count);
	return (i + 1);
}
void quickSort(int arr[], int low, int high, int &count)
{
	if (low < high)
	{

		int pi = partition(arr, low, high, count);
 
		quickSort(arr, low, pi - 1, count);
		quickSort(arr, pi + 1, high, count);
	}
}
int getmax(int a[], int n) {
	int max = a[0];
	for (int i = 1; i < n; i++)
		if (a[i] > max)
			max = a[i];
	return max;
}
void radixsort(int a[], int n, int &count) {

	int i;
	int l[maxs];
	int f = 1;
	int j = getmax(a, maxs);

	while (j / f > 0) {

		int bucket[10] = { 0 };

		for (i = 0; i < maxs; i++)
			bucket[(a[i] / f) % 10]++;

		for (i = 1; i < 10; i++)
			bucket[i] += bucket[i - 1];

		for (i = maxs - 1; i >= 0; i--)
			l[--bucket[(a[i] / f) % 10]] = a[i];


		for (i = 0; i < maxs; i++)
		{
			a[i] = l[i];
			count++;
		}

		f *= 10;

	}
}
void shellsort(int arr[], int N, int count)
{
	int h[10];
	int i;
	for (int i = 1; i < 9; i++) {
		h[i] = pow(4, i) + 3 * pow(2, i - 1);
		{
			for (int k = h[i]; k < N; k++)
			{

				int temp = arr[k];

				int j;
				for (j = k; j >= h[i] && arr[j - h[i]] > temp; j -= h[i])
					arr[j] = arr[j - h[i]];

				arr[j] = temp;
			}
		}
	}
}

void seq(int h[])
{
	for (int i = 1; i < 8; i++)
	{
		h[i] = pow(4, i) + 3 * pow(2, i - 1);
		cout << h[i] << endl;
	}
}
void initem(int a[]) {
	for (int i = 0; i < maxs; i++) a[i] = 0;
}
int main()
{
	int h[7];
	int a[maxs];
	int count;
	const int numsorts = 5;
	clock_t begin, end;
	double difftime;
	ofstream outf("program4.ot");

	for (int i = 0; i < numsorts; i++) {
		count = 0;
		switch (i)
		{
		case 0:
			initem(a);
			readem(a);
			begin = clock();
			bblsort(a, maxs, count);
			end = clock();
			difftime = (end - begin);
			printem(a, outf, "Bubble Sort", count, difftime);
			difftime = 0;
			count = 0;
			break;
		case 1:
			initem(a);
			readem(a);
			begin = clock();
			quickSort(a, 0, maxs - 1, count);
			end = clock();
			difftime = (end - begin);
			printem(a, outf, "Quick Sort", count, difftime);
			difftime = 0;
			count = 0;
			break;
		case 2:
			initem(a);
			readem(a);
			begin = clock();
			mergesort(a, maxs - 1, count);
			end = clock();
			difftime = (end - begin);
			printem(a, outf, "Merge Sort", count, difftime);
			difftime = 0;
			count = 0;
			break;

		case 3:
			initem(a);
			readem(a);
			begin = clock();
			radixsort(a, maxs - 1, count);
			end = clock();
			difftime = (end - begin);
			printem(a, outf, "Radix Sort", count, difftime);
			difftime = 0;
			count = 0;
			break;

		case 4:
			initem(a);
			readem(a);
			begin = clock();
			shellsort(a, maxs - 1, count);
			end = clock();
			difftime = (end - begin);
			printem(a, outf, "Shell Sort", count, difftime);
			difftime = 0;
			count = 0;
			break;
		}
	
	}


		return 0;
}