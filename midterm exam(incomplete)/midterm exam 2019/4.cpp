/*
4. 回型加密-十进制版
题目描述
计算概论班的同学发明了一种新的文本加密算法--将文本转化为十进制数并回型存放到矩阵里。
使用者事先约定好矩阵的行数与列数，并且规定文本中仅有大写字母和空格。他们事先按照这样的方法对文本进行编码：
空格 = 00
A = 01
B = 02
C = 03
......
Y = 25
Z = 26
然后，然后按照回型遍历的方法，将每个字符对应编码的2位十进制数依次填入矩阵中，多出来的位置使用0补充。例如，对于信息“PKU”，在矩阵行列数均是3的情况下，填充结果为：

1 -> 6 -> 1
                |
0 -> 0      1
|              |
0 <- 1 <- 2

再逐行将矩阵中的数字连起来，完成加密过程。也就是上述例子中的信息最终会被加密为：
161001012

关于输入
第一行为两个整数R和C，中间用一个空格隔开，分别表示行数和列数，其中1≤R≤10，1≤C≤10。
第二行为一个只包含大写字母和空格的字符串，不会以空格开头。1≤字符串长度≤(R * C) / 2。

关于输出
一行，为加密后的十进制串

例子输入
3 3
PKU
例子输出
161001012
提示信息
注意：前导0也要输出
*/
#include <iostream>
using namespace std;
int main()
{
	int r = 0, c = 0;
	cin >> r >> c;
	cin.get();
	char ch[100] = {};
	cin.getline(ch, 100);

	int chnum[150] = { 0 };//多余的0没关系
	for (int i = 0; ch[i] != '\0'; i++)
	{
		if (ch[i] == ' ')
			chnum[i] = 0;
		else
			chnum[i] = ch[i] - 'A' + 1;
	}

	int writenum[150] = { 0 };
	for (int i = 0; ch[i] != 0; i++)
	{
		writenum[2 * i] = chnum[i] / 10;
		writenum[2 * i + 1] = chnum[i] % 10;
	}

	//填充
	int table[15][15] = { 0 };
	int visited[15][15] = { 0 };//填充过为1
	int hang = 0, lie = 0, fangxiang = 1;//右1下2左3上4
	for (int i = 0; i < r * c; i++)
	{
		table[hang][lie] = writenum[i];
		visited[hang][lie] = 1;
		if (fangxiang == 1)
		{
			if (lie != c - 1 && visited[hang][lie + 1] == 0)
				lie++;
			else
			{
				fangxiang = 2;
				hang++;
			}
		}
		else if (fangxiang == 2)
		{
			if (hang != r - 1 && visited[hang+1][lie] == 0)
				hang++;
			else
			{
				fangxiang = 3;
				lie--;
			}
		}
		else if (fangxiang == 3)
		{
			if (lie != 0 && visited[hang][lie-1] == 0)
				lie--;
			else
			{
				fangxiang = 4;
				hang--;
			}
		}
		else if (fangxiang == 4)
		{
			if (hang != 0 && visited[hang-1][lie] == 0)
				hang--;
			else
			{
				fangxiang = 1;
				lie++;
			}
		}
	}

	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			cout << table[i][j];
		}
	}
	return 0;
}
