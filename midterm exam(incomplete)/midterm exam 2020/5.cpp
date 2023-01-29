/*
5. 重排空格
题目描述
给你一个字符串 text，该字符串由若干被空格包围的单词组成。每个单词由一个或者多个小写英文字母组成，并且两个单词之间至少存在一个空格。
请你重新排列空格，使每对相邻单词之间的空格数目都  相等  ，并尽可能  最大化  该数目。如果不能重新平均分配所有空格，请  将多余的空格放置在字符串末尾  ，这也意味着输出的字符串应当与原字符串的长度相等。

关于输入
一行由小写英文字母和空格组成的字符串。

字符串长度不超过1000，至少包含一个单词。

关于输出
一行和原字符串长度相等的字符串。

例子输入
  this   is  a sentence 
例子输出
this   is   a   sentence
提示信息
*/
#include <iostream>
using namespace std;
int main()
{
	char text[1050] = {};
	cin.getline(text, 1050);
	int num = 0,word=0;//空格数，单词数
	char each[1010][1010] = {};
	int tmp = 0;//单词下一个字母的位置

	//统计空格数与单词数，存储单词
	if (text[0] != ' ')
		word = 1;
	for (int i = 0; text[i] != '\0'; i++)
	{
		if (text[i] == ' ')
		{
			tmp = 0;
			num++;
			if (text[i + 1] != ' ' && text[i + 1] != '\0')
				word++;
		}
		else
		{
			each[word][tmp] = text[i];
			tmp++;
		}
	}

	if (word > 1)
	{
		int average = 0, rest = 0;
		average = num / (word - 1);
		rest = num - average * (word - 1);

		for (int i = 1; i < word; i++)
		{
			cout << each[i];
			for (int j = 0; j < average; j++)
			{
				cout << " ";
			}
		}
		cout << each[word];
		for (int j = 0; j < rest; j++)
		{
			cout << " ";
		}
	}
	else
	{
		cout << each[1];
		for (int i = 0; i < num; i++)
		{
			cout << " ";
		}
	}
	return 0;
}