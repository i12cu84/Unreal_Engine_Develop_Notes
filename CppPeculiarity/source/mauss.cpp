//摩斯电码转换(英/码互转)
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

int main()
{
    vector<pair<string, char>> psc;
    {
        psc.push_back(pair<string, char>(".-", 'a'));
        psc.push_back(pair<string, char>("-...", 'b'));
        psc.push_back(pair<string, char>("-.-.", 'c'));
        psc.push_back(pair<string, char>("-..", 'd'));
        psc.push_back(pair<string, char>(".", 'e'));
        psc.push_back(pair<string, char>("..-.", 'f'));
        psc.push_back(pair<string, char>("--.", 'g'));
        psc.push_back(pair<string, char>("....", 'h'));
        psc.push_back(pair<string, char>("..", 'i'));
        psc.push_back(pair<string, char>(".---", 'j'));
        psc.push_back(pair<string, char>("-.-", 'k'));
        psc.push_back(pair<string, char>(".-..", 'l'));
        psc.push_back(pair<string, char>("--", 'm'));
        psc.push_back(pair<string, char>("-.", 'n'));
        psc.push_back(pair<string, char>("---", 'o'));
        psc.push_back(pair<string, char>(".--.", 'p'));
        psc.push_back(pair<string, char>("--.-", 'q'));
        psc.push_back(pair<string, char>(".-.", 'r'));
        psc.push_back(pair<string, char>("...", 's'));
        psc.push_back(pair<string, char>("-", 't'));
        psc.push_back(pair<string, char>("..-", 'u'));
        psc.push_back(pair<string, char>("...-", 'v'));
        psc.push_back(pair<string, char>(".--", 'w'));
        psc.push_back(pair<string, char>("-..-", 'x'));
        psc.push_back(pair<string, char>("-.--", 'y'));
        psc.push_back(pair<string, char>("--..", 'z'));
        psc.push_back(pair<string, char>(".----", '1'));
        psc.push_back(pair<string, char>("..---", '2'));
        psc.push_back(pair<string, char>("...--", '3'));
        psc.push_back(pair<string, char>("....-", '4'));
        psc.push_back(pair<string, char>(".....", '5'));
        psc.push_back(pair<string, char>("-....", '6'));
        psc.push_back(pair<string, char>("--...", '7'));
        psc.push_back(pair<string, char>("---..", '8'));
        psc.push_back(pair<string, char>("----.", '9'));
        psc.push_back(pair<string, char>("-----", '0'));
        psc.push_back(pair<string, char>("..--..", '?'));
        psc.push_back(pair<string, char>("-..-.", '/'));
        psc.push_back(pair<string, char>("-....-", '-'));
        psc.push_back(pair<string, char>(".-.-.-", '.'));
    }

    vector<char> cb;
    vector<string> cd;
    string st;
    int pd;
    while (1)
    {
        cout << "请输入您需要的功能\n1、摩尔斯电码->英语(空格隔开)\n2、摩尔斯电码->英语( / 隔开)\n3、英语->莫尔斯电码(每段用空格隔开)：\n4、英语->莫尔斯电码(每段用 / 隔开)：\n";
        cin >> pd;
        if (pd == 1)
        {
            cout << "请输入摩尔斯电码(输入 “end”结束 ；每段电码请用空格隔开):\n";
            string str = "";
            int bol = 0;
            string strend = "end";
            while (str != strend)
            {
                cin >> str;
                for (auto psc_t : psc)
                    if (psc_t.first == str)
                        cb.push_back(psc_t.second);
                if (str == "-.--.-")
                {
                    bol == 0 ? cout << '(' : cout << ')';
                    bol = 1 - bol;
                }
                if (str == strend)
                {
                    if (cb.empty())
                        cout << "请输入正确电码。\n";
                    vector<char>::iterator it;
                    for (it = cb.begin(); it < cb.end(); it++)
                        cout << *it;
                    cout << endl;
                }
            }
        }
        else if (pd == 2)
        {
            cout << "请输入您要转换的电码(每段用 / 隔开)" << endl;
            cin >> st;
            unsigned int s1 = 0, s2 = 0, index = 0,end = st.size();
            char x = 0;
            int bol = 0;
            string temp = "";
            while (index < end)
            {
                s1 = index;
                while (index < end && st[index] != '/')
                    index++;
                s2 = index;
                temp = st.substr(s1, s2 - s1);
                for (auto psc_t : psc)
                    if (psc_t.first == temp)
                        cout << psc_t.second;
                if (temp == "-.--.-")
                {
                    bol == 0 ? cout << '(' : cout << ')';
                    bol = 1 - bol;
                }
                index++;
            }
        }
        else if (pd == 3)
        {
            string temp;
            cout << "请输入需要转换的内容(英语)(每段用空格隔开):\n";
            cin >> temp;
            char tem[sizeof(temp)];
            memset(tem, '0', sizeof(tem));
            strcpy_s(tem, temp.c_str());
            for (int i = 0; i < temp.length(); i++)
            {
                for (auto psc_t : psc)
                    if (psc_t.second == tem[i])
                        cd.push_back(psc_t.first);
                if (tem[i] == '(' || tem[i] == ')')
                    cd.push_back("-.--.-");
            }
            vector<string>::iterator it;
            for (it = cd.begin(); it != cd.end(); it++)
                cout << *it << ' ';
        }
        else if (pd == 4)
        {
            string temp;
            cout << "请输入需要转换的内容(英语)(每段用 / 隔开):\n";
            cin >> temp;
            char tem[sizeof(temp)];
            memset(tem, '0', sizeof(tem));
            strcpy_s(tem, temp.c_str());
            for (int i = 0; i < temp.length(); i++)
            {
                for (auto psc_t : psc)
                    if (psc_t.second == tem[i])
                        cd.push_back(psc_t.first);
                if (tem[i] == '(' || tem[i] == ')')
                    cd.push_back("-.--.-");
            }
            vector<string>::iterator it;
            for (it = cd.begin(); it != cd.end(); it++)
                cout << *it << '/';
        }
        cout << endl
             << endl;
        cb.clear();
        cd.clear();
    }
    return 0;
}
