#include <iostream>
#include <string>
#include <cmath>

using namespace std;

void nhapmang(int a[], int n) {
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
}
int binarySearch2(int a[], int value,int n) {
	int right = n-1;
	cout << right << endl;
	int left = 0;
	int mid;
	while (left < right) {
		mid = left + (right - left) / 2;
		if (value == a[mid]) return mid;
		else if (value < a[mid]) {
			right = mid - 1;
		}
		else {
			left = mid + 1;
		}
	}
	return -1;
}
int binarySearch(int a[], int value,int n) {
	int right=n;
	int left = 0;
	int mid;
	int vitri = -1;
	while (left<right) {
		mid = (left + right) / 2;
		if (value < a[mid]) {
			right = mid - 1;
		}
		else if (value > a[mid]) {
			left = mid + 1;
		}
		if (value == a[mid]){
			vitri = mid;
			break;
		}
			
	}
	return vitri;
}

int recBinarySearch(int a[], int l, int r, int value) {
	if (r >= 1) {
		int mid = l + (r - l) / 2;
		if (a[mid] == value) return mid;
		else if (a[mid] < value) {
			return recBinarySearch(a, l, mid - 1, value);
		}
		else {
			return recBinarySearch(a, mid + 1, r, value);
		}
	}
	return -1;
}
int main() {
	int arr[5];
	nhapmang(arr, 5);
	cout << binarySearch(arr, 3, 5) << endl;
	cout << recBinarySearch(arr, 0, 4, 3) << endl;
	cout << binarySearch2(arr, 3,5) << endl;
	system("pause");
	return 0;
}