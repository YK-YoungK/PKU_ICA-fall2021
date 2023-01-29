/*
7. n-gram串频统计
题目描述
在文本分析中常用到n-gram串频统计方法，即，统计相邻的n 个单元（如单词、汉字、或者字符）在整个文本中出现的频率。假设有一个字符串，请以字符为单位按n-gram 统计长度为 n 的子串出现的频度，并输出最高频度以及频度最高的子串。设定所给的字符串不多于500个字符，且 1 < n <5。 如果有多个子串频度最高，则根据其在序列中第一次出现的次序输出多个，每行输出一个，如果最高频度不大于1，则输出 NO

例如，n=3，所给的串是：abcdefabcd，
则，所有的 3-gram是：abc,bcd,cde,def,efa,fab,abc,bcd。最后面的cd不足以形成3-gram，则不考虑。这样，abc 和 bcd 都出现了2次，其余的只出现了1次，于是，输出结果应该是：
2
abc
bcd

关于输入
第一行为n
第二行为字符串

关于输出
输出最高频度以及频度最高的所有子串。

例子输入
3
abcdefabcd
例子输出
2
abc
bcd
提示信息
*/
#include <iostream>
using namespace std;
int main()
{
	int n = 0;
	cin >> n;
	cin.get();
	char ch[510] = {};
	cin.getline(ch, 510);

	//拆开
	char each[510][10] = {};
	for (int i = 0; ch[i + n - 1] != '\0'; i++)
	{
		for (int j = 0; j < n; j++)
		{
			each[i][j] = ch[i + j];
		}
	}


	int count[510] = { 0 };//记录某个位置开始的字串是否被记录过了，记录过为1
	struct chuan
	{
		char name[10] = {};
		int times=0;
	}gram[510];

	int num = 0;//当前统计到的不同字串的个数
	for (int i = 0; ch[i + n - 1] != '\0'; i++)
	{
		if (count[i] == 1)
			continue;
		
		for (int j = 0; j < n; j++)
		{
			gram[num].name[j] = each[i][j];
		}
		
		//统计后面和它相同的个数，并标记为1
		for (int j = i; ch[j + n - 1] != '\0'; j++)
		{
			int flag = 1;
			for (int k = 0; k < n; k++)
			{
				if (each[j][k] != gram[num].name[k])
				{
					flag = 0;
					break;
				}
			}
			if (flag == 1)
			{
				gram[num].times++;
				count[j] = 1;
			}
		}

		num++;
	}

	int good = 0;
	for (int i = 0; i < num; i++)
	{
		if (gram[i].times > 1)
			good++;
	}

	if (good == 0)
		cout << "NO" << endl;
	else
	{
		int max = 0;
		for (int i = 0; i < num; i++)
		{
			if (gram[i].times > max)
				max = gram[i].times;
		}
		cout << max << endl;
		for (int i = 0; i < num; i++)
		{
			if (gram[i].times ==max)
				cout << gram[i].name << endl;
		}
	}

	return 0;
}