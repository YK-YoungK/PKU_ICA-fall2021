/*
7. 盗宝
题目描述
有个财主收藏了大量的宝物。为防止被盗，他将宝物藏在离家不太远一个海岛上的不同洞穴内，有些洞内放了一件宝物，有些洞存放了多件，并绘制了藏宝图。但藏宝图不慎被一个海盗发现，他详细知道了每件宝物所在的洞穴。好在财主事先做了进一步的防范措施：万一有人进入一个洞内窃取宝物，最多只能取走洞内的一件宝物，而且不能让其再进入同一个洞内。海盗决定驾着他的小船去盗宝，但船承载货物的重量受限。已知每件宝物的重量和价值，请你根据船的载重量，推算海盗在每个洞只能进去一次的情况下，这一趟盗走宝物可能导致财主最大价值的损失是多少？

关于输入
第一行两个整数m,n（1<=m,n<=1000），分别是船的载货重量（海盗自身的重量忽略不计）和宝物总件数。两个整数以空格间隔
接下来n行，每行3个数，分别表示各件宝物的重量、价值和所在洞的编号。均为整数，且以空格间隔。

关于输出
一个整数值，为所盗宝物可能的最大总价值。

例子输入
30 3
15 8 1
10 5 1
48 400 2
例子输出
8
提示信息
*/
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;
int weight = 0, num = 0;
int treasure[10100][1010][2] = { 0 };//i号坑，第j个，重量和价值
int number[10100] = { 0 };
int solution[10100][1010] = { 0 };//start,best
int search(int start,int rest)
{
	if (solution[start][rest] != -1)
		return solution[start][rest];
	solution[start][rest] = max(solution[start][rest], search(start + 1, rest));
	for (int i = 0; i < number[start]; i++)
	{
		if (treasure[start][i][0] <= rest)
		{
			solution[start][rest] = max(solution[start][rest], search(start+1,rest- treasure[start][i][0])+ treasure[start][i][1]);
		}
	}
	
	return solution[start][rest];
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> weight >> num;
	int tmpplace = 0, tmpweight = 0, tmpvalue = 0;
	for (int i = 0; i < num; i++)
	{
		cin >> tmpweight >> tmpvalue >> tmpplace;
		treasure[tmpplace][number[tmpplace]][0] = tmpweight;
		treasure[tmpplace][number[tmpplace]][1] = tmpvalue;
		number[tmpplace]++;
	}

	for (int i = 0; i < 1010; i++)
	{
		for (int j = 0; j < 1010; j++)
			solution[i][j] = -1;
	}

	search(0, weight);

	cout << solution[0][weight] << endl;
	return 0;
}