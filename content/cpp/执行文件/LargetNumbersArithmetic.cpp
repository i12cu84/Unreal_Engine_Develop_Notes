// 大数四则运算(含扩展的小数点运算)
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
#define MAX 1000
int i, len, sum[MAX] = {0};
char num1[MAX] = "3234567891234567891234";
char num2[MAX] = "2345678912345678913345";
char num3[MAX] = "32345678912345678912.34";
char num4[MAX] = "23456789123456789133.45";
char sum2[MAX] = {0};
// 大数加法
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
// 大数减法
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
// 大数乘法
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
// 大数除法(精确个位数)
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
// 用于删除小数点
void Delect_Char(char str1[], char Aim, int len)
{
    for (int i = 0; i < len; i++)
        if (str1[i] == Aim)
        {
            if (i == len - 1)
            {
                len--;
                return;
            }
            for (int j = i; j < len; j++)
                str1[j] = str1[j + 1];
            len--;
            i--;
        }
}
// 用于末尾添加0
void AddZero_Char(char str1[], int len)
{
    int lenth = strlen(str1);
    for (int i = 0; i < len; i++)
    {
        str1[lenth + i] = '0';
    }
}
// 获取小数点位置
int GetPointNum(char str1[])
{
    int Num = 0;
    bool IsFind = false;
    for (int i = 0; i < strlen(str1); i++)
    {
        if (str1[i] == '.')
        {
            Num = i;
            IsFind = true;
            break;
        }
    }
    return IsFind ? strlen(str1) - Num - 1 : Num;
}
// 在指定位置添加小数点
void AddPoint_Char(char str1[], int len)
{
    int lenth = strlen(str1);
    for (int i = 0; i < len + 1; i++)
    {
        str1[lenth + 1] = str1[lenth];
        lenth--;
    }
    str1[lenth + 1] = '.';
}
// 输出打印结果
template <typename T>
void PrintSum(int len, T sum[], bool outputendl = true)
{
    for (int i = len - 1; i >= 0; i--)
        cout << sum[i];
    if (outputendl)
        cout << endl;
}
// 输出打印结果
template <typename T>
void PrintSum(int len, T sum[], int ZeroNum)
{
    for (int i = len - 1; i >= 0; i--)
    {
        cout << sum[i];
        if (i - ZeroNum == 0)
        {
            cout << ".";
        }
    }
    cout << endl;
}
int main()
{
#if 1
    PrintSum(Addition(num1, num2, sum), sum);       // 5580246803580246804579
    PrintSum(Subtraction(num1, num2, sum), sum);    // 888888978888888977889
    PrintSum(Multiplication(num1, num2, sum), sum); // 7587257693019357461682497036550397271117730
    PrintSum(Division(num1, num2, sum2), sum2);     // 1
#elif 1
    // 含小数点大数加法
    int first = GetPointNum(num3);
    int second = GetPointNum(num4);
    Delect_Char(num3, '.', strlen(num3));
    Delect_Char(num4, '.', strlen(num4));
    AddZero_Char(num3, second);
    AddZero_Char(num4, first);
    auto AddtionNum = Addition(num3, num4, sum);
    PrintSum(AddtionNum, sum, first + second); // 5580246803580246804579.0000
#elif 1
    // 含小数点大数减法
    int first = GetPointNum(num3);
    int second = GetPointNum(num4);
    Delect_Char(num3, '.', strlen(num3));
    Delect_Char(num4, '.', strlen(num4));
    AddZero_Char(num3, second);
    AddZero_Char(num4, first);
    auto SubtractionNum = Subtraction(num3, num4, sum);
    PrintSum(SubtractionNum, sum, first + second); // 8888889788888889778.8900
#elif 1
    // 含小数点大数乘法
    int first = GetPointNum(num3);
    int second = GetPointNum(num4);
    Delect_Char(num3, '.', strlen(num3));
    Delect_Char(num4, '.', strlen(num4));
    auto MultiplicationNum = Multiplication(num3, num4, sum);
    PrintSum(MultiplicationNum, sum, first + second); // 758725769301935746168249703655039727111.7730
#elif 1
    // 含小数点大数除法
    char num5[MAX] = "6666.66";
    char num6[MAX] = "11";
    char num7[MAX] = "0.11";
    char num8[MAX] = "0.00011";
    int arg, first, second;
    auto Dc = [&]()
    {
        if (arg == 0)
        {
            PrintSum(Division(num5, num6, sum2), sum2);
        }
        else if (arg > 0)
        {
            auto DivisionNum = Division(num5, num6, sum2);
            PrintSum(DivisionNum, sum2, arg);
        }
        else
        {
            PrintSum(Division(num5, num6, sum2), sum2, false);
            for (; arg; arg++)
                cout << "0";
        }
    };
    // 含小数点大数除法
    first = GetPointNum(num5);

    second = GetPointNum(num6);
    arg = first - second;
    Delect_Char(num5, '.', strlen(num5));
    Delect_Char(num6, '.', strlen(num6));
    Dc(); // 606.06

    second = GetPointNum(num7);
    arg = first - second;
    Delect_Char(num7, '.', strlen(num7));
    Dc(); // 60606

    second = GetPointNum(num8);
    arg = first - second;
    Delect_Char(num8, '.', strlen(num8));
    Dc(); // 60606000

#endif
    return 0;
}
