//任意进制转换成任意进制(36进制以内)
#include<bits/stdc++.h>
using namespace std;
const int Max = 100005;
char str[Max];
string arr;
void fun1(int num, int R)//cast to 10
{
    int r,index=0;
	if(num < 0)
	{
		cout << "-";
		num = - num;
	}
    while(num != 0)
    {
        r = num % R;
        num = num / R;
        str[index++] =r <= 9?'0' + r: 'A' + r - 10;
    }
    for(int i = index - 1; i >= 0; i--)
        cout << str[i];
}
int fun2(string num, int R)//cast to n
{
	int len = num.length();
	int ans = 0;
	for(int i = len - 1; i >= 0; i--)
		if(num[i] >= 48 && num[i] <= 57)
			ans += (num[i] - '0') * pow(R, -i - 1 + len);
		else if(num[i] >= 65 && num[i] <= 70)
			ans += (num[i] - 'A' + 10) * pow(R, -i - 1 + len);
	return ans;
}

int main()
{
    while(1)
    {
        cout<<endl;
        int FirstSystem,LastSystem;
        string FirstNum;
        cout<<"input your first system:"<<endl;
        cin>>FirstSystem;
        cout<<"input your last system:"<<endl;
        cin>>LastSystem;
        cout<<"input your first number:"<<endl;
        cin>>FirstNum;
        fun1(fun2(FirstNum,FirstSystem),LastSystem);
    }
}