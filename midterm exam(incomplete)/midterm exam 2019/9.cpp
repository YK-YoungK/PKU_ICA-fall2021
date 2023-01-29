/*
9. 流感
题目描述
    学校里一共有n个学生。这n个学生里一共有m对朋友关系。
    在流感发作期，每个健康学生都要看望当天他生病的朋友（如果有的话），并在第二天被传染上疾病（除非他在免疫期内）；
    每个生病的学生在第二天都会痊愈，并在这一天具有免疫性。从第三天起，看望生病的朋友将再次使他染上流感。
    初始时（第一天），只有一个学生患有流感。试问多少天后流感会自动结束。

关于输入
第一行输入两个正整数n和m。
接下来m行每行两个正整数x,y，表示编号为x的学生和编号为y的学生是一对朋友。输入数据保证每一对朋友关系只描述一次。
最后一行输入一个正整数，代表初始时患有流感的学生的编号。

n,m <= 100,000。

关于输出
输出多少天后流感会结束。

如果天数超过2,000,000,000，则视为流感不会结束，输出-1。

例子输入
4 4
1 2
2 3
3 4
2 4
1
例子输出
3
提示信息
第一天1号学生生病，2号学生访问他；
第二天2号学生生病，其它三个学生访问他，由于1号处于免疫期，未患流感；
第三天3、4号学生生病，2号学生访问他们。
第四天3、4号学生痊愈，流感结束。


*/
#include <iostream>
using namespace std;
int main()
{
	int n = 0, m = 0;
	cin >> n >> m;
	static int fri[100005][2] = { 0 };
	for (int i = 0; i < m; i++)
	{
		cin >> fri[i][0] >> fri[i][1];
	}
	int first = 0;
	cin >> first;

	static int health[100005] = { 0 };//所有人健康状况，0健康1患病2免疫力
	static int healthtmp[100005] = { 0 };//临时存放下一天的健康状况，记得循环最后要重置
	health[first] = 1;
	int day = 0;
	for (day = 1; day <= 2000000000; day++)
	{
		for (int i = 0; i < m; i++)//遍历朋友关系
		{
			//只有当天看望才会被传染
			if (health[fri[i][0]] == 1 && health[fri[i][1]] == 0)
				healthtmp[fri[i][1]] = 1;
			if (health[fri[i][1]] == 1 && health[fri[i][0]] == 0)
				healthtmp[fri[i][0]] = 1;
		}
		//处理痊愈的
		for (int i = 1; i <= n; i++)
		{
			if (health[i] == 1)
				healthtmp[i] = 2;
		}

		//复制回去，并清空临时数组
		for (int i = 1; i <= n; i++)
		{
			health[i] = healthtmp[i];
			healthtmp[i] = 0;
		}

		int flag = 1;
		for (int i = 1; i <= n; i++)
		{
			if (health[i] == 1)
			{
				flag = 0; break;
			}
		}
		if (flag == 1)
			break;
	}
	if (day != 2000000000)
		cout << day << endl;
	else
		cout << "-1" << endl;
	return 0;
}