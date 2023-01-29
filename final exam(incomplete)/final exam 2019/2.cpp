/*
2. 尊老爱幼
题目描述
    4号病房一共住着 n 位病人（n是正整数，且n<100），他们的年纪都在 1~99 之间 ，且任何两人都不同岁。
    今天他们都要进行体检，但同时只能有一个病人接受检查??前一个病人全部检查完了，下一个病人才能开始体检。
    这 n 位病人都特别尊崇老爱幼的传统美德，决定让最老的病人第一个检查，最年轻的病人第二个检查， 接着是第二老的病人 、第二年轻的病人，第三老的病人……以此类推。
    病人们将排序的任务交给了你，他们会告诉你他们各自的年龄，请计算出体检的顺序（顺序的输出年龄即可）

关于输入
输入为两行
第一行为一个正整数n，n<100
第二行是n个正整数，均≤99

关于输出
输出为n行，n个正整数

例子输入
9
1 2 3 4 5 6 7 8 9
例子输出
9
1
8
2
7
3
6
4
5
提示信息
*/
#include <iostream>
using namespace std;
int main()
{
	int age[150] = { 0 };
	int num = 0;
	cin >> num;
	for (int i = 0; i < num; i++)
	{
		cin >> age[i];
	}
	for (int i = 0; i < num; i++)
	{
		for (int j = i + 1; j < num; j++)
		{
			if (age[i] < age[j])
			{
				int tmp = age[i];
				age[i] = age[j];
				age[j] = tmp;
			}
		}
	}
	for (int i = 1; i <= num; i++)
	{
		if (i % 2 == 1)
			cout << age[(i - 1) / 2] << endl;
		else
			cout << age[num - i / 2] << endl;
	}
}