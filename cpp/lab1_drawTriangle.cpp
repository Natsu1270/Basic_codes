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

int main()
{
    drawFoo(5, false);
    drawSolidTriangle(4);
    drawSolidTriangle2(4);
    drawSolidTriangle3(4);
    drawEmptyTriangle(20);

    return 0;
}