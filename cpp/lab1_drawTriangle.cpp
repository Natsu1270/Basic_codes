#include <iostream>
using namespace std;

void drawFoo(int h, bool invert)
{
    if (!invert)
    {
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j <= i; j++)
            {
                cout << "*";
            }
            cout << "\n";
        }
    }
    else
    {
        for (int i = h; i > 0; i--)
        {
            for (int j = 1; j <= i; j++)
            {
                cout << "*";
            }
            cout << "\n";
        }
    }
}

void drawSolidTriangle(int h)
{
    int c = 2 * h - 1;
    int r = h - 1;
    int l = h - 1;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (j >= l & j <= r)
            {
                cout << "*";
            }
            else
            {
                cout << "-";
            }
        }
        r += 1;
        l -= 1;
        cout << endl;
    }
}

void drawSolidTriangle2(int rows)
{
    for (int i = 1; i <= rows; i++)
    {
        for (int j = 1; j <= rows - i; j++)
        {
            cout << "-";
        }

        for (int k = 1; k <= 2 * i - 1; k++)
        {
            cout << "*";
        }

        cout << endl;
    }
}

void drawSolidTriangle3(int rows)
{
    int c = 2 * rows - 1;
    for (int i = 1; i <= rows; i++)
    {
        for (int j = 1; j <= rows - i; j++)
        {
            cout << "-";
        }

        for (int k = 1; k <= 2 * i - 1; k++)
        {
            cout << "*";
        }

        for (int j = 1; j <= rows - i; j++)
        {
            cout << "-";
        }

        cout << endl;
    }
}

void drawEmptyTriangle(int h)
{
    int c = 2 * h - 1;
    int r = h - 1;
    int l = h - 1;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (i == h - 1)
            {
                cout << "*";
            }
            else
            {
                if (j == l || j == r)
                {
                    cout << "*";
                }
                else
                {
                    cout << " ";
                }
            }
        }
        r += 1;
        l -= 1;
        cout << endl;
    }
}

void drawSquare(int h) {
    for (int i=0;i<h;i++) {
        for(int j =0;j<h;j++) {
            cout<<"* ";
        }
        cout<<endl;
    }
    cout<<endl;
}

void drawSquareFrame(int h) {
    for (int i=0; i < h; i++) {
        for (int j=0; j < h;j++) {
            if (i==0||i==h-1) {
                cout<<"* ";
            } else {
                if (j==0||j==h-1) {
                    cout<<"* ";
                } else {
                    cout<<"  ";
                }
            }
        }
        cout<<endl;
    }
}

void fibonaciWordLoop(int n) {
    string res = "";
    string s0= "0";
    string s1= "01";

    if (n==0) {
        cout<<s0;
        return;
    }
    if (n==1) {
        cout<<s1;
        return;
    }
    for (int i=2; i<=n; i++) {
        res = s1+s0;
        s0=s1;
        s1=res;
    }
    cout<<res<<endl;

}

string fibonacWordRec(int n) {
    if (n==0) return "0";
    if (n==1) return "01";
    return fibonacWordRec(n-1) + fibonacWordRec(n-2);
}

int bin2dec(int num) {
    if (num==0) return 0;
    return num%10 + 2*bin2dec(num/10);
}

int main()
{
    // cout<<fibonacWordRec(3)<<endl;    
    // drawFoo(5, false);
    // drawSolidTriangle(4);
    // drawSolidTriangle2(4);
    // drawSolidTriangle3(4);
    // drawEmptyTriangle(6);
    // drawSquare(7);
    // drawSquareFrame(6);
    // fibonaciWordLoop(3);
    cout<<bin2dec(1101)<<endl;
    return 0;
}