/*
6. 括号配对
题目描述
小凡同学在学习C语言时无意间发现括号的配对是件很有意思的事。对于不同数量的括号，似乎有很多种不同但是合法的组合方式。对于小凡给出的括号总对数N，你能告诉他总共有多少种不同的括号组合方式吗？

关于输入
输入有一行，为括号的总对数N，N为不超过10的正整数。

关于输出
按左括号优先的顺序排列出所有合法的组合方式。

例子输入
3
例子输出
((()))
(()())
(())()
()(())
()()()
提示信息
*/
#include <iostream>
using namespace std;
int n = 0;
char kuohao[50] = {};
void use(int i, int j)//用了几个左，右括号
{
	if (i == n && j == n)
	{
		cout << kuohao<<endl;
		return;
	}
	if (i < j||i>n||j>n)//不符合规则
		return;
	if (i >= j)
	{
		kuohao[i + j] = '(';
		use(i + 1, j);
		kuohao[i + j] = ')';
		use(i, j + 1);
		return;
	}
}
int main()
{
	cin >> n;
	use(0, 0);
}