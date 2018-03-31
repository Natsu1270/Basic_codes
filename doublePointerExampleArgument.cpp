#include <iostream>

using namespace std;
void change(int* a, int* b) {
	a = b;
	cout << "inside function a is " << a << " and b is " << b << endl;
}

void changepp(int** a, int* b) {
	*a = b;
	cout << "inside function a is " << *a << " and b is " << b << endl;
}
int main() {
	int m{ 1 }, n{ 2 }, q{ 3 };
	int* a = &m;
	int* b = &n;
	int* c = &q;
	int** pp = &a;
	cout << a << " " << b << " " << c << endl;
	change(a, b);
	cout << "outside a is " << a <<" so a did not change just like pass a para as a value!"<< endl;
	cout << "Time to use pass para as double pointer(because a is a pointer so if you wanna change a you must use a & or *): " << endl;
	changepp(pp, b);
	cout << "outside a is " << a << endl;
	system("pause");
	return 0;

}