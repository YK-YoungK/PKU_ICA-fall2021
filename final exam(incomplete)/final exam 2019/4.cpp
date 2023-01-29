/*
4. 购物推荐系统
题目描述
如今的电子商务网站都已经支持“购物推荐系统”。也即，当用户在浏览某一种商品时，该系统会通过分析数据库中的历史订单信息，计算出购买了这种商品的用户还购买了哪些商品，然后通过排序，找到最为相关的产品推荐给用户。

现在希望你能够实现一个最简单的购物推荐系统。我们的输入是网站所有的历史交易记录，按照“用户名 商品编号”这样的二元对给出，表示某用户购买了某商品。
当给定一个商品编号时，你首先需要在所有购买记录中找到购买过该商品的用户，然后再找到他们购买过的所有其他商品，接着对这些商品排序，找到数量最多的那个商品，然后推荐给用户。

两点说明：
（1）一个用户可以反复多次购买同一个商品，计算推荐商品时，须要按照多个计算。
（2）若出现排序后数量一样多的推荐商品，则只需要输出编号最小的那一个即可。

关于输入
第一行为一个整数T，代表该购物网站的每一个订单。
接下来的总共T行，每行就是一个购买记录，按照如下格式：

用户名  商品编号

（其中，用户名是字符串（不含空格），且不会超过20个字符；用户数目小于等于100。
商品编号是整数，且大于等于1、小于1000。
且为了简单起见，我们把输入已经按照用户名进行了排序。）

最后一行输入是一个整数，表示用户正在浏览的商品编号。

关于输出
输出推荐商品的编号

例子输入
7
GuoGuo 21
GuoGuo 23
GuoGuo 987
FaceBro 23
FaceBro 21
FaceBro 748
Nobody 999
23

例子输出
21
提示信息
在示例输入中，根据最后查询的商品编号23，可以发现GuoGuo和FaceBro两名用户都购买了23号商品；他们两个都共同购买了21，所以输出21为推荐商品编号。
*/
#include <iostream>
#include <cstring>
using namespace std;
int main()
{
	int t = 0;
	cin >> t;
	char name[105][25] = {};
	char nametmp[25] = {};
	int choice[105][1005] = { 0 };
	int num = 0;
	int tmp = 0;
	for (int i = 0; i < t; i++)
	{
		cin >> nametmp;
		for (int j = 0; j < 25; j++)
		{
			if (nametmp[j] != name[num][j])
			{
				num++;
				for (int k = 0; k < 25; k++)
				{
					name[num][k] = nametmp[k];
				}
				break;
			}
		}
		cin >> tmp;
		choice[num][tmp]++;
	}

	int want = 0;
	cin >> want;
	int choicetmp[1005] = { 0 };
	for (int i = 1; i <= num; i++)
	{
		if (choice[i][want] != 0)
		{
			for (int j = 1; j <= 1000; j++)
			{
				choicetmp[j] = choicetmp[j] + choice[i][j];
			}
		}
	}

	int max = 0, maxplace = 0;
	for (int i = 1; i <= 1000; i++)
	{
		if (i == want)
			continue;
		if (choicetmp[i] > max)
		{
			max = choicetmp[i];
			maxplace = i;
		}
	}
	cout << maxplace << endl;
}