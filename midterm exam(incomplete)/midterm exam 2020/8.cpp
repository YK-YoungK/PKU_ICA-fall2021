/*
8. 1140 最短前缀
题目描述
一个字符串的前缀是从该字符串的第一个字符起始的一个子串。例如 "carbon"的字串是: "c", "ca", "car", "carb", "carbo", 和 "carbon"。注意到这里我们不认为空串是子串, 但是每个非空串是它自身的子串. 我们现在希望能用前缀来缩略地表示单词。例如, "carbohydrate" 通常用"carb"来缩略表示. 现在给你一组单词, 要求你找到唯一标识每个单词的最短前缀
在下面的例子中，"carbohydrate" 能被缩略成"carboh", 但是不能被缩略成"carbo" (或其余更短的前缀) 因为已经有一个单词用"carbo"开始
一个精确匹配会覆盖一个前缀匹配，例如，前缀"car"精确匹配单词"car". 因此 "car" 是 "car"的缩略语是没有二义性的 , “car”不会被当成"carriage"或者任何在列表中以"car"开始的单词.

关于输入
输入包括至少2行，至多1000行. 每行包括一个以小写字母组成的单词，单词长度至少是1，至多是20.

关于输出
输出的行数与输入的行数相同。每行输出由相应行输入的单词开始，后面跟着一个空格接下来是相应单词的没有二义性的最短前缀标识符。

例子输入
carbohydrate
cart
carburetor
caramel
caribou
carbonic
cartilage
carbon
carriage
carton
car
carbonate
例子输出
carbohydrate carboh
cart cart
carburetor carbu
caramel cara
caribou cari
carbonic carboni
cartilage carti
carbon carbon
carriage carr
carton carto
car car
carbonate carbona
提示信息
*/
#include <iostream>
using namespace std;
int main()
{
	char ch[1050][25] = {};
	int num = 0;
	for (num = 0;; num++)
	{
		cin.getline(ch[num], 25);
		if (cin.fail() == 1)
			break;
	}

	//循环
	for (int i = 0; i < num; i++)
	{
		int flag[1050] = { 0 };//0代表尚未区分出来，1代表已经区分出来
		int geshu = 0;//区分出来的个数，到num-1代表已经结束
		for (int j = 0;; j++)
		{
			for (int k = 0; k < num; k++)
			{
				if (flag[k] == 1)
					continue;
				else
				{
					if (ch[k][j] != ch[i][j])
					{
						flag[k] = 1;
						geshu++;
					}
				}
			}
			if (geshu == num - 1||ch[i][j+1]=='\0')//区分出来了，输出
			{
				cout << ch[i] << " ";
				for (int k = 0; k <= j; k++)
				{
					cout << ch[i][k];
				}
				cout << endl;
				break;
			}
		}
	}
	return 0;
}