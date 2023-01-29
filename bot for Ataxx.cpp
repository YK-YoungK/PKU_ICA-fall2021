#pragma GCC diagnostic error "-std=c++11"
#pragma GCC target("avx")
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <float.h>

using namespace std;

int currBotColor = 0; // 我所执子颜色（1为黑，-1为白，棋盘状态亦同）
int gridInfo[7][7] = { 0 }; // 先x后y，记录棋盘状态
int blackPieceCount = 2, whitePieceCount = 2;
int startX, startY, resultX, resultY;
static int delta[24][2] = { { 1,1 },{ 0,1 },{ -1,1 },{ -1,0 },
{ -1,-1 },{ 0,-1 },{ 1,-1 },{ 1,0 },
{ 2,0 },{ 2,1 },{ 2,2 },{ 1,2 },
{ 0,2 },{ -1,2 },{ -2,2 },{ -2,1 },
{ -2,0 },{ -2,-1 },{ -2,-2 },{ -1,-2 },
{ 0,-2 },{ 1,-2 },{ 2,-2 },{ 2,-1 } };
int delta_near_num[7][7] = { 0 };//与每个位置相邻的个数
int delta_notnear_num[7][7] = { 0 };//与每个位置剪切相邻的个数
int delta_near_place[7][7][8][2] = { 0 };//与每个位置相邻的位置坐标，四个分量分别为原来的x，y；相邻的x，y
int delta_notnear_place[7][7][16][2] = { 0 };//与每个位置剪切的位置坐标，四个分量分别为原来的x，y；剪切的x，y
static int delta_near[8][2] = { { 1,1 },{ 0,1 },{ -1,1 },{ -1,0 },
{ -1,-1 },{ 0,-1 },{ 1,-1 },{ 1,0 } };//复制粘贴，优先搜索
static int delta_notnear[16][2] = { { 2,0 },{ 2,1 },{ 2,2 },{ 1,2 },
{ 0,2 },{ -1,2 },{ -2,2 },{ -2,1 },
{ -2,0 },{ -2,-1 },{ -2,-2 },{ -1,-2 },
{ 0,-2 },{ 1,-2 },{ 2,-2 },{ 2,-1 } };//剪切粘贴，滞后搜索
//以下，用于记录每一轮移动棋子的位置，因为在外面调用的自动落子函数需要，因此将其放到外面！
int place_beforex = -1, place_beforey = -1;//在地图上，进行要移动子的定位
int place_afterx = -1, place_aftery = -1;//在地图上，进行移动子终点的定位
clock_t starttime = 0, nowtime = 0;//记录起始时间和当前时间

// 判断是否在地图内
inline bool inMap(int x, int y)
{
	if (x < 0 || x > 6 || y < 0 || y > 6)
		return false;
	return true;
}

// 向Direction方向改动坐标，并返回是否越界
inline bool MoveStep(int& x, int& y, int Direction)
{
	x = x + delta[Direction][0];
	y = y + delta[Direction][1];
	return inMap(x, y);
}

// 在坐标处落子，检查是否合法或模拟落子
bool ProcStep(int x0, int y0, int x1, int y1, int color)
{
	if (color == 0)
		return false;
	if (x1 == -1) // 无路可走，跳过此回合
		return true;
	if (!inMap(x0, y0) || !inMap(x1, y1)) // 超出边界
		return false;
	if (gridInfo[x0][y0] != color)
		return false;
	int dx, dy, x, y, currCount = 0, dir;
	int effectivePoints[8][2];
	dx = abs((x0 - x1)), dy = abs((y0 - y1));
	if ((dx == 0 && dy == 0) || dx > 2 || dy > 2) // 保证不会移动到原来位置，而且移动始终在5×5区域内
		return false;
	if (gridInfo[x1][y1] != 0) // 保证移动到的位置为空
		return false;
	if (dx == 2 || dy == 2) // 如果走的是5×5的外围，则不是复制粘贴
		gridInfo[x0][y0] = 0;
	else
	{
		if (color == 1)
			blackPieceCount++;
		else
			whitePieceCount++;
	}

	gridInfo[x1][y1] = color;
	for (dir = 0; dir < 8; ++dir) // 影响邻近8个位置
	{
		x = x1 + delta[dir][0];
		y = y1 + delta[dir][1];
		if (!inMap(x, y))
			continue;
		if (gridInfo[x][y] == -color)
		{
			effectivePoints[currCount][0] = x;
			effectivePoints[currCount][1] = y;
			currCount++;
			gridInfo[x][y] = color;
		}
	}
	if (currCount != 0)
	{
		if (color == 1)
		{
			blackPieceCount += currCount;
			whitePieceCount -= currCount;
		}
		else
		{
			whitePieceCount += currCount;
			blackPieceCount -= currCount;
		}
	}
	return true;
}



//记录棋盘当前状态的数组，整个过程构成一个结构体
struct chess_situation
{
	int map[10][10] = { 0 };
	//0代表未下，1代表黑，-1代表白（这一个代表第i回合结束之后棋盘的状态）
	int numblack = 0, numwhite = 0;//棋盘上黑白子的数目（表示的是第i回合结束后的个数）
	int beforex = 0, beforey = 0;//起子位置（第i回合 内 发生的起子）
	int afterx = 0, aftery = 0;//落子位置（第i回合 内 发生的落子）
};


struct chess_situation tmp[10];
//用于函数中调用其状态，每一个数组记录的是搜索深度为i的，由于是深度优先搜索，不用回溯
//与存储实时对战情况的不同，这里tmp[0]存储的是搜索开始时（bot未下）的棋面和the first step of bot，
//tmp[1]存储的是after the first step of bot的棋面，还有正在遍历的下一步person的走法，以此类推


double judge_ab_search(int lunshu, int depth)
//传参：知道要调取哪一个棋盘图来看，调取tmp[depth]
//以黑方角度计算，返回之后根据bot的身份乘currbotcolor
{
	int sum_black = 0, sum_white = 0;//黑白子总数
	int stable_black = 0, stable_white = 0;//黑子稳定子个数（当其周围的所有格子都非空，则其稳定）
	int black_move[10][10] = { 0 };//黑子可以走到哪里
	int white_move[10][10] = { 0 };//白子可以走到哪里
	int move_black = 0, move_white = 0;//黑白子行动力

	for (int x = 0; x < 7; ++x)
	{
		for (int y = 0; y < 7; ++y)
		{
			if (tmp[depth].map[x][y] == 1)
			{
				sum_black++;

				//统计黑子周围，计算黑子是否为稳定子及其行动力
				int count = 0;
				for (int k = 0; k < delta_near_num[x][y]; ++k)
				{
					if (tmp[depth].map[delta_near_place[x][y][k][0]][delta_near_place[x][y][k][1]] == 0)
					{
						black_move[delta_near_place[x][y][k][0]][delta_near_place[x][y][k][1]] = 1;
						count++;
					}
				}

				if (count == 0)
					stable_black++;
			}


			if (tmp[depth].map[x][y] == -1)
			{
				sum_white++;

				//统计白子周围，计算白子是否为稳定子及其行动力
				int count = 0;
				for (int k = 0; k < delta_near_num[x][y]; ++k)
				{
					if (tmp[depth].map[delta_near_place[x][y][k][0]][delta_near_place[x][y][k][1]] == 0)
					{
						white_move[delta_near_place[x][y][k][0]][delta_near_place[x][y][k][1]] = 1;
						count++;
					}
				}

				if (count == 0)
					stable_white++;
			}
		}
	}

	for (int x = 0; x < 7; ++x)
	{
		for (int y = 0; y < 7; ++y)
		{
			if (black_move[x][y] == 1)
				move_black++;
			if (white_move[x][y] == 1)
				move_white++;
		}
	}

	if (lunshu - depth <= 10)
		return 1000 * (sum_black - sum_white);
	else if (tmp[0].numblack + tmp[0].numwhite < 44)//中间
		return 1000 * (sum_black - sum_white) + 750 * (stable_black - stable_white)
		+ 250 * (move_black - move_white);
	else//快结束了
		return 1000 * (sum_black - sum_white);
}



//以下为用alpha-beta剪枝算法做的机器落子的程序
double bot_ab_search(int lunshu, int depth, double alpha, double beta, int player)
//形参含义：当前模拟的回合数、搜索深度（当前设置的为做4层）、剪枝判定的两个变量、玩家（黑1白-1）
//倒数第二、一个形参：传递某一个待通过比较确定较优解的位置，上面用数组存指定的参数，这个数要传给评估函数的
//倒数第三个形参：此轮执手方，在递归的时候不变，也是要传给评估函数的
{
	if (tmp[depth].numblack + tmp[depth].numwhite == 49)//加入特判：胜负已分
	{
		if (tmp[depth].numblack > tmp[depth].numwhite)
			return currBotColor * (tmp[depth].numblack - tmp[depth].numwhite) * 3000;
		else
			return (-1) * currBotColor * (tmp[depth].numblack - tmp[depth].numwhite) * 3000;
	}

	//搜索层数到达上限
	if (depth == 4)//到达搜索深度上限
	{
		return currBotColor * judge_ab_search(lunshu, depth);
	}

	//游戏结束
	if (tmp[depth].numblack == 0 || tmp[depth].numwhite == 0 || lunshu == 400)//游戏结束的情形
	{
		if (tmp[depth].numblack > tmp[depth].numwhite)
			return currBotColor * (1 << 30);
		else
			return (-1) * currBotColor * (1 << 30);
	}

	//alpha-beta向后递归
	int near_arrival[10][10] = { 0 };//复制粘贴能到的，就不用剪切粘贴（源头上剪枝）
	int exist = 0;//是否找到第一组解
	double maxium = -DBL_MAX;

	//进行周边的搜索（24格）
	for (int x = 0; x < 7; ++x)
	{
		for (int y = 0; y < 7; ++y)
		{
			if (tmp[depth].map[x][y] == player)
			{
				//进行复制搜索
				for (int k = 0; k < delta_near_num[x][y]; ++k)
				{

					//判断落子是否合法：条件1——是否已有棋子
					if (tmp[depth].map[delta_near_place[x][y][k][0]][delta_near_place[x][y][k][1]] != 0)
						continue;

					//找到第一组可行解
					if (depth == 0 && exist == 0)
					{
						place_beforex = x;
						place_beforey = y;
						place_afterx = delta_near_place[x][y][k][0];
						place_aftery = delta_near_place[x][y][k][1];
						exist = 1;
					}

					//判断是否需要重复搜索（就是前面已经有复制粘贴可以到达这个点位）
					if (near_arrival[delta_near_place[x][y][k][0]][delta_near_place[x][y][k][1]] == 1)
						continue;


					//落子合法之后，将这个点标记为复制粘贴可以到达的点，后续可以进行剪枝（只在复制的8个里面剪掉）
					near_arrival[delta_near_place[x][y][k][0]][delta_near_place[x][y][k][1]] = 1;


					//接下来检查是否在和之前局面重复的时候，进行了相同的起子和落子（合法落子条件2）
					//这里的搜索由于只有5层，所以对于看上去比较无意义的双方反复拉锯暂时不判断

					//没问题，准备进行下一轮的搜索
					//先进行当前局面的起子与落子的保存
					tmp[depth].beforex = x;
					tmp[depth].beforey = y;
					tmp[depth].afterx = delta_near_place[x][y][k][0];
					tmp[depth].aftery = delta_near_place[x][y][k][1];

					//先进行结构体数组的复制以及对应棋盘局面的改变
					tmp[depth + 1] = tmp[depth];
					//1.判断复制粘贴与剪切粘贴，根据搜索规则这里是复制粘贴，所以这一步略去

					//2.将新位置填上棋子，判断颜色
					//在这里，player的含义就是当前的落子方，黑1白-1
					tmp[depth + 1].map[tmp[depth + 1].afterx][tmp[depth + 1].aftery] =
						player;

					if (player == 1)
						tmp[depth + 1].numblack++;
					if (player == -1)
						tmp[depth + 1].numwhite++;

					//3.搜索周边，如果有异色的同化
					for (int nearby = 0; nearby < delta_near_num[tmp[depth + 1].afterx][tmp[depth + 1].aftery]; ++nearby)
					{
						if (tmp[depth + 1].map[delta_near_place[tmp[depth + 1].afterx][tmp[depth + 1].aftery][nearby][0]]
							[delta_near_place[tmp[depth + 1].afterx][tmp[depth + 1].aftery][nearby][1]] == (-1) * player)
						{
							tmp[depth + 1].map[delta_near_place[tmp[depth + 1].afterx][tmp[depth + 1].aftery][nearby][0]]
								[delta_near_place[tmp[depth + 1].afterx][tmp[depth + 1].aftery][nearby][1]] = player;

							if (player == 1)
							{
								tmp[depth + 1].numblack++;
								tmp[depth + 1].numwhite--;
							}
							if (player == -1)
							{
								tmp[depth + 1].numwhite++;
								tmp[depth + 1].numblack--;
							}
						}
					}

					//走下一层的搜索，在此之前先检查时间
					nowtime = clock();
					if ((double)(nowtime - starttime) / CLOCKS_PER_SEC > 0.99)
						return maxium;

					double result_return = (-1) * bot_ab_search(lunshu + 1, depth + 1, (-1) * beta, (-1) * alpha, (-1) * player);
					if (result_return > alpha)
					{
						if (result_return >= beta)
							return result_return;
						alpha = result_return;
					}
					if (result_return > maxium)
					{
						//修改maxium
						maxium = result_return;

						if (depth == 0)//最浅的一层搜索（就是第一层），需要对应修改起子与落子位置
						{
							//更改起子和落子位置
							place_beforex = x;
							place_beforey = y;
							place_afterx = delta_near_place[x][y][k][0];
							place_aftery = delta_near_place[x][y][k][1];
						}
					}
				}

				//进行剪切搜索
				for (int k = 0; k < delta_notnear_num[x][y]; ++k)
				{
					//判断落子是否合法：条件1——该位子尚未有落子
					if (tmp[depth].map[delta_notnear_place[x][y][k][0]][delta_notnear_place[x][y][k][1]] != 0)
						continue;

					//找到第一组可行解
					if (depth == 0 && exist == 0)
					{
						place_beforex = x;
						place_beforey = y;
						place_afterx = delta_notnear_place[x][y][k][0];
						place_aftery = delta_notnear_place[x][y][k][1];
						exist = 1;
					}

					//没问题，准备进行下一轮的搜索
					//先进行当前局面的起子与落子的保存
					tmp[depth].beforex = x;
					tmp[depth].beforey = y;
					tmp[depth].afterx = delta_notnear_place[x][y][k][0];
					tmp[depth].aftery = delta_notnear_place[x][y][k][1];

					//先进行结构体数组的复制以及对应棋盘局面的改变
					tmp[depth + 1] = tmp[depth];
					//1.判断复制粘贴与剪切粘贴，根据搜索规则这里必然是剪切粘贴
					tmp[depth + 1].map[tmp[depth + 1].beforex][tmp[depth + 1].beforey] = 0;
					//2.将新位置填上棋子，判断颜色
					//在这里，player的含义就是当前的落子方，黑1白-1
					tmp[depth + 1].map[tmp[depth + 1].afterx][tmp[depth + 1].aftery] =
						player;
					//3.搜索周边，如果有异色的同化
					for (int nearby = 0; nearby < delta_near_num[tmp[depth + 1].afterx][tmp[depth + 1].aftery]; ++nearby)
					{
						if (tmp[depth + 1].map[delta_near_place[tmp[depth + 1].afterx][tmp[depth + 1].aftery][nearby][0]]
							[delta_near_place[tmp[depth + 1].afterx][tmp[depth + 1].aftery][nearby][1]] == (-1) * player)
						{
							tmp[depth + 1].map[delta_near_place[tmp[depth + 1].afterx][tmp[depth + 1].aftery][nearby][0]]
								[delta_near_place[tmp[depth + 1].afterx][tmp[depth + 1].aftery][nearby][1]] = player;

							if (player == 1)
							{
								tmp[depth + 1].numblack++;
								tmp[depth + 1].numwhite--;
							}
							if (player == -1)
							{
								tmp[depth + 1].numwhite++;
								tmp[depth + 1].numblack--;
							}
						}
					}

					//走下一层的搜索，在此之前先检查时间
					nowtime = clock();
					if ((double)(nowtime - starttime) / CLOCKS_PER_SEC > 0.99)
						return maxium;

					double result_return = (-1) * bot_ab_search(lunshu + 1, depth + 1, (-1) * beta, (-1) * alpha, (-1) * player);
					if (result_return > alpha)
					{
						if (result_return >= beta)
							return result_return;
						alpha = result_return;
					}
					if (result_return > maxium)
					{
						//修改maxium
						maxium = result_return;

						if (depth == 0)//最浅的一层搜索（就是第一层），需要对应修改起子与落子位置
						{
							//更改起子和落子位置
							place_beforex = x;
							place_beforey = y;
							place_afterx = delta_notnear_place[x][y][k][0];
							place_aftery = delta_notnear_place[x][y][k][1];
						}
					}

				}
			}
		}
	}
	return maxium;

}


int main()
{
	starttime = clock();
	istream::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int x0, y0, x1, y1;

	// 初始化棋盘
	gridInfo[0][0] = gridInfo[6][6] = 1;  //|黑|白|
	gridInfo[6][0] = gridInfo[0][6] = -1; //|白|黑|

										  // 分析自己收到的输入和自己过往的输出，并恢复状态
	int turnID;
	currBotColor = -1; // 第一回合收到坐标是-1, -1，说明我是黑方
	cin >> turnID;
	for (int i = 0; i < turnID - 1; ++i)
	{
		// 根据这些输入输出逐渐恢复状态到当前回合
		cin >> x0 >> y0 >> x1 >> y1;
		if (x1 >= 0)
			ProcStep(x0, y0, x1, y1, -currBotColor); // 模拟对方落子
		else
			currBotColor = 1;
		cin >> x0 >> y0 >> x1 >> y1;
		if (x1 >= 0)
			ProcStep(x0, y0, x1, y1, currBotColor); // 模拟己方落子
	}

	// 看看自己本回合输入
	cin >> x0 >> y0 >> x1 >> y1;
	if (x1 >= 0)
		ProcStep(x0, y0, x1, y1, -currBotColor); // 模拟对方落子
	else
		currBotColor = 1;

	//计算所有相邻的坐标及其个数
	int tmpx = 0, tmpy = 0;
	for (int x = 0; x < 7; ++x)
	{
		for (int y = 0; y < 7; ++y)
		{
			//计算相邻的个数及位置
			for (int k = 0; k < 8; ++k)
			{
				tmpx = x + delta_near[k][0];
				tmpy = y + delta_near[k][1];
				if (tmpx >= 0 && tmpx <= 6 && tmpy >= 0 && tmpy <= 6)
				{
					delta_near_place[x][y][delta_near_num[x][y]][0] = tmpx;
					delta_near_place[x][y][delta_near_num[x][y]][1] = tmpy;
					delta_near_num[x][y]++;
				}
			}

			//计算不相邻的个数及位置
			for (int k = 0; k < 16; ++k)
			{
				tmpx = x + delta_notnear[k][0];
				tmpy = y + delta_notnear[k][1];
				if (tmpx >= 0 && tmpx <= 6 && tmpy >= 0 && tmpy <= 6)
				{
					delta_notnear_place[x][y][delta_notnear_num[x][y]][0] = tmpx;
					delta_notnear_place[x][y][delta_notnear_num[x][y]][1] = tmpy;
					delta_notnear_num[x][y]++;
				}
			}
		}
	}

	// 做出决策（你只需修改以下部分）
	memset(tmp, 0, sizeof(tmp));
	for (int x = 0; x < 7; ++x)
	{
		for (int y = 0; y < 7; ++y)
		{
			tmp[0].map[x][y] = gridInfo[x][y];
		}
	}
	tmp[0].numblack = blackPieceCount;
	tmp[0].numwhite = whitePieceCount;

	if (currBotColor == 1)
		bot_ab_search(2 * turnID - 1, 0, -DBL_MAX, DBL_MAX, currBotColor);
	if (currBotColor == -1)
		bot_ab_search(2 * turnID, 0, -DBL_MAX, DBL_MAX, currBotColor);

	//在即将结束的时候，尽量采用复制粘贴的方法
	if (tmp[0].numblack + tmp[0].numwhite >= 47)
	{
		if (abs(place_beforex - place_afterx) >= 2 || abs(place_beforey - place_aftery) >= 2)
		{
			for (int k = 0; k < delta_near_num[place_afterx][place_aftery]; ++k)
			{
				if (tmp[0].map[delta_near_place[place_afterx][place_aftery][k][0]]
					[delta_near_place[place_afterx][place_aftery][k][1]] == currBotColor)
				{
					place_beforex = delta_near_place[place_afterx][place_aftery][k][0];
					place_beforey = delta_near_place[place_afterx][place_aftery][k][1];
					break;
				}
			}
		}
	}

	// 决策结束，输出结果（你只需修改以上部分）

	cout << place_beforex << " " << place_beforey << " " << place_afterx << " " << place_aftery;
	return 0;
}