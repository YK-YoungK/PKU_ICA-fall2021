/*
1. 甲流病人初筛
题目描述
目前正是甲流盛行时期，为了更好地进行分流治疗，医院在挂号时要求对病人的体温和咳嗽情况进行检查，对于体温超过37.5度（含等于37.5度）并且咳嗽的病人初步判定为甲流病人（初筛）。现需要统计某天前来挂号就诊的病人中有多少人被初筛为甲流病人。

关于输入
第一行是某天前来挂号就诊的病人数n
其后有n行，每行是病人的信息，包括三个信息：姓名（字符串，不含空格，最多8个字符）、体温（float）、是否咳嗽（整数，1表示咳嗽，0表示不咳嗽）

关于输出
行数不确定，但最后一行是一个整数m，表示被初筛为甲流的病人数，之前有m行，每行按输入顺序输出病人的姓名

例子输入
5
Zhang 38.3 0
Li 37.5 1
Wang 37.1 1
Zhao 39.0 1
Liu 38.2 1
例子输出
Li
Zhao
Liu
3
提示信息
*/
#include <iostream>
using namespace std;
int main()
{
	int n = 0;
	cin >> n;
	char name[10] = {};
	float temp=0;
	int kesou=0;
	int count = 0;

	while (n > 0)
	{
		cin >> name >> temp >> kesou;
		if (temp >= 37.5 && kesou == 1)
		{
			count++;
			cout << name << endl;
		}
		n--;
	}
	cout << count << endl;
	return 0;
}