/*
5. 爱读书的Tim（已选-中）
题目描述
Tim穿越到荒岛时，灯神还给了他一本天书，这本书的某些页十分晦涩难懂，需要阅读完另一页的内容才能完全理解。而有些页则比较通俗易懂，阅读完当前页即可理解。

Tim是一个喜欢钻研的小朋友，他每天都会从这本书中页数最小的从未读过的一页开始读，读到完全理解这一页的内容为止。例如对于当Tim某一天要读这本书的第a页时，这一页要求读完第b页才能理解，于是Tim又要去读第b页，而第b页要求读完第c页才能理解，于是Tim又要去读第c页，而第c页不需要读别的页就可以理解，或是需要读的页在之前已经读过了，最终Tim这一天读了a, b, c这三页内容。

Tim想知道自己需要花多少天才能读完这本书？

关于输入
第一行一个整数n,表示这本书有n页
第二行有n个正整数a1,a2,……,an，其中ai表示要读完第i页的内容要先读完第ai页的内容。（ai>=i）

关于输出
一个正整数，表示读完这本书需要的时间

例子输入
10
3 4 3 4 8 7 8 10 10 10
例子输出
5
提示信息
样例说明：
第一天Tim读了第1, 3页
第二天Tim读了第2, 4页
第三天Tim读了第5, 8, 10页
第四天Tim读了第6, 7页
第五天Tim读了第9页

数据范围
对于所有数据，1 ≤ n ≤ 100000
*/
#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>
using namespace std;
int main()
{
	int n = 0;
	cin >> n;
	int num[100005] = { 0 };
	for (int i = 1; i <= n; i++)
	{
		cin >> num[i];
	}

	int day = 0;
	int visited[100005] = { 0 };
	int visitedsum = 0;
	int notread = 1;
	for (day = 1;; day++)
	{
		int tmp = notread;
		visited[tmp] = 1;
		visitedsum++;
		if (visitedsum == n)
			break;

		
		while (visited[num[tmp]] == 0)
		{
			if (num[tmp] == tmp)
			{
				visited[tmp] = 1; 
				visitedsum++;
				break;
			}
			tmp = num[tmp];
			visited[tmp] = 1;
			visitedsum++;
		}
		if (visitedsum == n)
			break;

		for (int i = notread + 1; i <= n; i++)
		{
			if (visited[i] == 0)
			{
				notread = i; break;
			}
		}
	}
	cout << day << endl;
	return 0;
}