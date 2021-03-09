#include <iostream>

using namespace std;



int fun(int x, int y)
{
    if (x == 0)
        return y;
    return fun(x - 1, x + y);
}

bool isPrime(int num)
{
    if (num < 2)
        return false;
    int i;
    for (i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
            return false;
    }
    return true;
}

void onePrime(int *arr, int n)
{
    if (n < 0)
        return;
    if (isPrime(arr[n]))
    {
        cout << arr[n] << endl;
        return;
    }
    return onePrime(arr, n - 1);
}

void allPrime(int *arr, int n)
{
    if (n < 0)
        return;
    if (isPrime(arr[n]))
    {
        cout << arr[n] << endl;
    }
    return allPrime(arr, n - 1);
}

void loopTriangle(int n)
{
    int temp = n;
    for (int i = 1; i <= n; i++)
    {
        if (i <= n / 2)
        {
            for (int j = 1; j <= n; j++)
            {
                if (j < temp)
                    cout << "_";
                else
                    cout << j;
            }
            temp -= 1;
        }
        else
        {
            if (n % 2 == 0)
            {
                temp += 1;
            }
            for (int j = 1; j <= n; j++)
            {
                if (j < temp)
                    cout << "_";
                else
                    cout << j;
            }
            if (n % 2 != 0)
            {
                temp += 1;
            }
        }
        cout << endl;
    }
}

void loopTriangle2(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i <= n / 2)
            {
                if (j < n - i + 1)
                {
                    cout << "_";
                }
                else
                {
                    cout << j;
                }
            }
            else
            {
                if (j >= i)
                {
                    cout << j;
                }
                else
                {
                    cout << "_";
                }
            }
        }
        cout << endl;
    }
}



void recursiveTriangleHelper(int r, int c, int n)
{
    if (r == 0)
        return;
    if (c==0) {
        recursiveTriangleHelper(r - 1, n, n);
        cout<<endl;
        return;
    }
    recursiveTriangleHelper(r, c - 1, n);
    if (r<=n/2) {
        if (c<n-r+1) {
            cout<<"_";
        } else {
            cout<<c;
        }
    } else {
        if (c>=r) {
            cout<<c;
        } else {
            cout<<"_";
        }
    }

}

void recursiveTriangle(int n)
{
    recursiveTriangleHelper(n,n,n);
}

int main()
{
    // loopTriangle(3);
    // loopTriangle2(9);
    recursiveTriangle(9);
    cout<<endl;

    

    // int a[5] = {1, 11, 6, 8, 7};
    // onePrime(a, 5);
    // allPrime(a, 5);
    // int var1 = 3;
    // int var2 = 4;
    // int *p1, *p2;

    // p1 = &var1;
    // p2 = &var2;

    // int **p3 = &p1;

    // cout << p3 << endl;
    // cout << *p3 << endl;
    // cout << &p3 << endl;

    // cout << p1 << " " << p2 << endl;
    // cout << &p1 << " " << &p2 << endl;
    // cout << *p1 << " " << *p2 << endl;
    // cout << var1 << " " << var2 << endl;

    // int a[3] = {1, 2, 3};
    // cout << *(a + 1) << endl;

    return 0;
}