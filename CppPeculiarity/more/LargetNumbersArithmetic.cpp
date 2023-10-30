// 大数四则运算
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
#define MAX 1000
int i, len, sum[MAX] = {0};
char num1[MAX] = "3234567891234567891234";
char num2[MAX] = "2345678912345678913345";
char sum2[MAX] = {0};
// 大数加法
int Addition(char num1[], char num2[], int sum[]);
// 大数减法
int Subtraction(char num1[], char num2[], int sum[]);
// 大数乘法
int Multiplication(char num1[], char num2[], int sum[]);
// 大数除法(精确个位数)
int Division(char num1[], char num2[], char sum[]);

template <typename T>
void PrintSum(int len, T sum[])
{
    for (int i = len - 1; i >= 0; i--)
        cout << sum[i];
    cout << endl;
}
int main()
{
#if 1
    PrintSum(Addition(num1, num2, sum),sum);
    PrintSum(Subtraction(num1, num2, sum),sum);
    PrintSum(Multiplication(num1, num2, sum),sum);
    PrintSum(Division(num1, num2, sum2),sum2);
#elif 1
#endif
    return 0;
}

int Addition(char num1[], char num2[], int sum[])
{
    int i, j, len, n2[MAX] = {0}, len1 = strlen(num1), len2 = strlen(num2);
    len = len1 > len2 ? len1 : len2;
    for (i = len1 - 1, j = 0; i >= 0; i--, j++)
        sum[j] = num1[i] - '0';
    for (i = len2 - 1, j = 0; i >= 0; i--, j++)
        n2[j] = num2[i] - '0';
    for (i = 0; i <= len; i++)
    {
        sum[i] += n2[i];
        if (sum[i] > 9)
        {
            sum[i] -= 10;
            sum[i + 1]++;
        }
    }
    if (sum[len] != 0)
        len++;
    return len;
}

int Subtraction(char num1[], char num2[], int sum[])
{
    int i, j, len, blag = 0, n2[MAX] = {0}, len1 = strlen(num1), len2 = strlen(num2);
    if (len1 < len2)
    {
        blag = 1;
        swap(num1, num2);
        swap(len1, len2);
    }
    else if (len1 == len2)
    {
        for (i = 0; i < len1; i++)
        {
            if (num1[i] == num2[i])
                continue;
            if (num1[i] > num2[i])
            {
                blag = 0;
                break;
            }
            else
            {
                blag = 1;
                swap(num1, num2);
                break;
            }
        }
    }
    len = len1 > len2 ? len1 : len2;
    for (i = len1 - 1, j = 0; i >= 0; i--, j++)
        sum[j] = num1[i] - '0';
    for (i = len2 - 1, j = 0; i >= 0; i--, j++)
        n2[j] = num2[i] - '0';
    for (i = 0; i <= len; i++)
    {
        sum[i] = sum[i] - n2[i];
        if (sum[i] < 0)
        {
            sum[i] += 10;
            sum[i + 1]--;
        }
    }
    for (i = len1 - 1; i >= 0 && sum[i] == 0; i--)
        ;
    len = i + 1;
    if (blag == 1)
    {
        sum[len] = -1;
        len++;
    }
    return len;
}

int Multiplication(char num1[], char num2[], int sum[])
{
    int i, j, len, len1 = strlen(num1), len2 = strlen(num2), a[MAX + 10] = {0}, b[MAX + 10] = {0}, c[MAX * 2 + 10] = {0};
    for (j = 0, i = len1 - 1; i >= 0; i--)
        a[j++] = num1[i] - '0';
    for (j = 0, i = len2 - 1; i >= 0; i--)
        b[j++] = num2[i] - '0';
    for (i = 0; i < len2; i++)
        for (j = 0; j < len1; j++)
            c[i + j] += b[i] * a[j];
    for (i = 0; i < MAX * 2; i++)
        if (c[i] >= 10)
        {
            c[i + 1] += c[i] / 10;
            c[i] %= 10;
        }
    for (i = MAX * 2; c[i] == 0 && i >= 0; i--)
        ;
    len = i + 1;
    for (; i >= 0; i--)
        sum[i] = c[i];
    return len;
}

int Division(char num1[], char num2[], char sum[])
{
    auto SubStract = [](int *p1, int len1, int *p2, int len2) -> int
    {
        int i;
        if (len1 < len2)
            return -1;
        if (len1 == len2)
            for (i = len1 - 1; i >= 0; i--)
                if (p1[i] > p2[i])
                    break;
                else if (p1[i] < p2[i])
                    return -1;
        for (i = 0; i <= len1 - 1; i++)
        {
            p1[i] -= p2[i];
            if (p1[i] < 0)
            {
                p1[i] += 10;
                p1[i + 1]--;
            }
        }
        for (i = len1 - 1; i >= 0; i--)
            if (p1[i])
                return (i + 1);
        return 0;
    };
    int k, i, j, len1 = strlen(num1), len2 = strlen(num2), len = 0, dValue, nTemp, num_a[MAX] = {0}, num_b[MAX] = {0}, num_c[MAX] = {0};
    for (j = 0, i = len1 - 1; i >= 0; j++, i--)
        num_a[j] = num1[i] - '0';
    for (j = 0, i = len2 - 1; i >= 0; j++, i--)
        num_b[j] = num2[i] - '0';
    if (len1 < len2)
        return -1;
    dValue = len1 - len2;
    for (i = len1 - 1; i >= 0; i--)
        if (i >= dValue)
            num_b[i] = num_b[i - dValue];
        else
            num_b[i] = 0;
    len2 = len1;
    for (j = 0; j <= dValue; j++)
        while ((nTemp = SubStract(num_a, len1, num_b + j, len2 - j)) >= 0)
        {
            len1 = nTemp;
            num_c[dValue - j]++;
        }
    for (i = MAX - 1; num_c[i] == 0 && i >= 0; i--)
        ;
    if (i >= 0)
        len = i + 1;
    for (j = 0; i >= 0; i--, j++)
        sum[j] = num_c[i] + '0';
    sum[j] = '\0';
    return len;
}