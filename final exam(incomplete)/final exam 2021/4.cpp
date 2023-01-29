/*
4. 任意K进制长纯小数加法运算
题目描述
任意输入两个K进制纯小数，均为正数，计算其和，其中，1 < K < 11。所谓纯小数是指整数部分为0,一定有小数位（允许小数位都为0）。假定小数部分的长度不超过100位。

关于输入
第1行，是小数对的个数 n；
之后是 n 行，每行格式是：
k m1 m2
其中，k表示后面的 m1 和 m2 是k进制，m1和m2为k进制纯小数。中间均按空格间隔。
注意：输入的纯小数末位可能会带有0

关于输出
输出为对应的 n 行相加的结果。
规定：结果值的小数位末位不能是0，如果小数位都为0，也必须有小数点。

例子输入
4
2 0.1000110111 0.000011111111101
3 0.1210000001 0.210000010001211
2 0.1011 0.00110
10 0.499 0.501
例子输出
0.100111011011101
1.101000010101211
0.111
1.
提示信息
*/
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n = 0;
	cin >> n;
	int k = 0;
	
	while (n > 0)
	{
		
		char ch1[150] = {}, ch2[150] = {};
		int num1[150] = { 0 }, num2[150] = { 0 };
		cin >> k;
		cin >> ch1;
		cin >> ch2;

		for (int i = 0; ch1[i] != '\0'; i++)
		{
			if (ch1[i] == '.')
			{
				continue;
			}
			else
			{
				num1[i] = ch1[i] - '0';
			}
		}
		for (int i = 0; ch2[i] != '\0'; i++)
		{
			if (ch2[i] == '.')
			{
				continue;
			}
			else
			{
				num2[i] = ch2[i] - '0';
			}
		}

		int resulttmp[150] = { 0 };
		for (int i = 149; i >= 1; i--)
		{
			resulttmp[i] = num1[i] + num2[i];
		}

		int result[150] = { 0 };
		//进位
		int jinwei = 0;
		for (int i = 149; i >= 1; i--)
		{
			result[i] = (resulttmp[i]+jinwei) % k;
			jinwei = (resulttmp[i] + jinwei) / k;
		}

		int end = 149;
		for (end = 149; end >= 1; end--)
		{
			if (result[end] == 0 && result[end - 1] != 0)
			{
				end--;
				break;
			}
		}
		
		if (end == 1)
		{
			cout << result[1] << "." << endl;
		}
		else
		{
			cout << result[1] << ".";
			for (int i = 2; i <= end; i++)
				cout << result[i];
			cout << endl;
		}

		n--;
	}



	return 0;
}