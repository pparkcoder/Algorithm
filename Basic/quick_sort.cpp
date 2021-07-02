// O(NlogN)

#include<iostream>
using namespace std;
int cnt = 1;
void quick_sort(int arr[], int start, int end) {
	if (start >= end) return;
	int pivot = start;
	int i = pivot + 1;
	int j = end;
	int temp;
	while (i <= j) {
		while (i <= end && arr[i] <= arr[pivot]) i++;  // pivot보다 큰 값 찾기
		while (j > start && arr[j] >= arr[pivot]) j--; // pivot보다 작은 값 찾기
		if (i <= j) {
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
		else {
			temp = arr[pivot];
			arr[pivot] = arr[j];
			arr[j] = temp;
		}
	}
	cout << cnt++ << " : ";
	for (int i = 0; i < 10; ++i)
		cout << arr[i] << " ";
	cout << "\n";
	quick_sort(arr, start, j - 1);
	quick_sort(arr, j + 1, end);
}
int main() {
	int arr[10] = { 4,1,2,3,9,7,8,6,10,5 };
	for (int i = 0; i < 10; ++i)
		cout << arr[i] << " ";
	cout << "\n";
	quick_sort(arr, 0, 9);
	for (int i = 0; i < 10; ++i)
		cout << arr[i] << " ";
	cout << "\n";
}
