#pragma GCC optimize("O2")
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC optimize(3)
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include "jsoncpp/json.h"
#define win 1
#define lose 0
#define enermy 1
#define mine -1
using namespace std;

typedef pair<int, int> PII;

int turnID;

const int MaxSize = 81;
const int EdgeLength = 9;
const int INF = 0x3f3f3f3f;
int rootboard[9][9];
bool dfs_air_visit[9][9];
int SimulationSum;
const int cx[] = { -1,0,1,0 };
const int cy[] = { 0,-1,0,1 };

//判断该位置是否在界内
inline bool inBorder(int x, int y) { return x >= 0 && y >= 0 && x < 9 && y < 9; }

// 判断该位置是否有气
inline bool dfs_air(int board[][9], int fx, int fy)
{
	dfs_air_visit[fx][fy] = true;
	bool flag = false;
	for (int dir = 0; dir < 4; dir++)
	{
		int dx = fx + cx[dir], dy = fy + cy[dir];
		if (inBorder(dx, dy))
		{
			if (board[dx][dy] == 0)
				flag = true;
			if (board[dx][dy] == board[fx][fy] && !dfs_air_visit[dx][dy])
				if (dfs_air(board, dx, dy))
					flag = true;
		}
	}
	return flag;
}

// 判断该位置能否落子
inline bool judgeAvailable(int board[][9], int fx, int fy, int col)
{
	if (board[fx][fy]) return false;
	board[fx][fy] = col;
	memset(dfs_air_visit, 0, sizeof(dfs_air_visit));
	if (!dfs_air(board, fx, fy))
	{
		board[fx][fy] = 0;
		return false;
	}
	for (int dir = 0; dir < 4; dir++)
	{
		int dx = fx + cx[dir], dy = fy + cy[dir];
		if (inBorder(dx, dy))
		{
			if (board[dx][dy] && !dfs_air_visit[dx][dy])
				if (!dfs_air(board, dx, dy))
				{
					board[fx][fy] = 0;
					return false;
				}
		}
	}
	board[fx][fy] = 0;
	return true;
}

// 蒙特卡洛树节点
class Node
{
public:
	Node* parent; //父节点
	vector<Node*> Children; //子节点
	int height;//高度，根节点高度为0
	PII curOP;//当前落点
	int board[EdgeLength][EdgeLength]; //当前棋盘状态
	int VictoryNum; //当前节点模拟胜利次数
	int SearchNum; //当前节点搜索次数
	double UCB;
	vector<PII> ValidOp; //所有可行的子节点数
	vector<PII> NoExpansionOp; //未扩展的操作
	int col; //上一步是谁下

	// 构造函数
	Node(int parentBoard[9][9], PII op, Node* Parentptr, int parentheight, int whoturn, int ID)
	{
		for (int i = 0; i < EdgeLength; i++)
			for (int j = 0; j < EdgeLength; j++)
			{
				this->board[i][j] = parentBoard[i][j];
			}
		if (op.first != -1) board[op.first][op.second] = whoturn;
		curOP = op;
		height = parentheight + 1;
		UCB = INF;
		VictoryNum = 0, SearchNum = 0;
		parent = Parentptr;
		col = whoturn;
		findChildren(ID);
		NoExpansionOp = ValidOp;
	}

	double CalculateUCB()//win为模拟后该节点赢的次数，n为该节点模拟次数，N为总模拟次数
	{
		double ucb = 0;
		ucb = (double)VictoryNum / SearchNum + 2.0 * sqrt(log(SimulationSum) / SearchNum);
		return ucb;
	}

	void Update(int res)
	{
		SearchNum++;
		if (res > 0 && col == mine)//我方赢 
		{
			VictoryNum += res;
		}
		if (res < 0 && col == enermy)
			VictoryNum += -res;
		UCB = CalculateUCB();
		if (this->parent) this->parent->Update(res);
	}

	int Simulation()
	{
		int mineCnt = 0; //我方赢的次数
		int enermyCnt = 0;
		bool mineCan = false;
		bool enermyCan = false;
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
			{
				mineCan = judgeAvailable(board, i, j, mine);
				enermyCan = judgeAvailable(board, i, j, enermy);
				if (mineCan ) mineCnt++;
				if (enermyCan) enermyCnt++;
				if (mineCan && !enermyCan) mineCnt+=2;
				else if (!mineCan && enermyCan) enermyCnt+=2;
			}
		return mineCnt - enermyCnt;
	}

	void Search()
	{

		if (!ValidOp.size())// 没有可下位置，即终局
		{
			int res = 0;
			if (col == enermy) res = lose;
			else res = win;
			Update(res);
		}
		else
		{
			if (NoExpansionOp.size())
			{
				int RandomOp = rand() % NoExpansionOp.size();
				Node* newnode = new Node(board, NoExpansionOp[RandomOp], this, height, -col, 0);
				Children.push_back(newnode);
				NoExpansionOp.erase(NoExpansionOp.begin() + RandomOp);
				int res = newnode->Simulation();
				Update(res);
			}
			else
			{
				Node* bestChildren = NULL;
				for (auto tmpnode : Children)
				{
					if (!bestChildren) bestChildren = tmpnode;
					if (tmpnode->UCB > bestChildren->UCB) bestChildren = tmpnode;
				}
				bestChildren->Search();
			}
		}
	}

	//计算当前节点所有子节点
	void findChildren(int id)
	{
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
			{
				if (id == 1)
				{
					if (i <= 1 || i >= 7 || j <= 1 || j >= 7)
					{
						if (judgeAvailable(board, i, j, -col))
							ValidOp.push_back({ i,j });
					}
					else continue;
				}
				else if (id == 2)
				{
					if ((i<2&&j<2) || (i<2&&j>6) || (i>6&&j<2) || (i>6&&j>6) )
					{
						if (judgeAvailable(board, i, j, -col))
							ValidOp.push_back({ i,j });
					}
					else continue;
				}
				else if (id == 3)
				{
					if ((i < 3 && j < 3) || (i < 3 && j>5) || (i > 5 && j < 3) || (i > 5 && j > 5))
					{
						if (judgeAvailable(board, i, j, -col))
							ValidOp.push_back({ i,j });
					}
					else continue;
				}
				else if (id == 4)
				{
					if ((i == 0 && j == 0) || (i == 8 && j == 0) || (i == 0 && j == 8) || (i == 8 && j == 8))
					{
						if (judgeAvailable(board, i, j, -col))
							ValidOp.push_back({ i,j });
					}
					else continue;
				}
				else
				{
					if (judgeAvailable(board, i, j, -col))
						ValidOp.push_back({ i,j });
				}
			}
	}

};


int main()
{
	srand((unsigned)time(0));
	string str;
	int x, y;
	// 读入JSON
	getline(cin, str);
	//getline(cin, str);
	Json::Reader reader;
	Json::Value input;
	reader.parse(str, input);
	// 分析自己收到的输入和自己过往的输出，并恢复状态
	turnID = input["responses"].size();
	for (int i = 0; i < turnID; i++)
	{
		x = input["requests"][i]["x"].asInt(), y = input["requests"][i]["y"].asInt();
		if (x != -1) rootboard[x][y] = 1; //对方
		x = input["responses"][i]["x"].asInt(), y = input["responses"][i]["y"].asInt();
		if (x != -1) rootboard[x][y] = -1; //己方
	}
	x = input["requests"][turnID]["x"].asInt(), y = input["requests"][turnID]["y"].asInt();
	if (x != -1) rootboard[x][y] = 1; //对方
	// 输出决策JSON
	Json::Value ret;
	Json::Value action;
	int id = 0;
	if (turnID < 2) id = 4;
	else if (turnID < 6) id = 3;
	else if (turnID < 12) id = 1;
	Node* root = new Node(rootboard, { x,y }, NULL, -1, enermy, id);
	int threshold = 0.975 * (double)CLOCKS_PER_SEC; //CLOCKS_PER_SEC 和 clock()的含义可百度
	int start_time, current_time;
	start_time = current_time = clock();
	while (current_time - start_time < threshold) { //到 0.975 秒立即跳出循环
		SimulationSum++;
		root->Search();
		current_time = clock();
	}

	PII best_op = { 0, 0 };
	int best_Value = -0x3f3f3f3f;
	for (auto child : root->Children)
	{
		if (child->VictoryNum > best_Value)
		{
			best_op = child->curOP;
			best_Value = child->VictoryNum;
		}
	}


	action["x"] = best_op.first; action["y"] = best_op.second;
	ret["response"] = action;
	Json::FastWriter writer;
	char buffer[4096];
	sprintf(buffer, "MCTS搜索次数:%d", SimulationSum);
	ret["debug"] = buffer;

	cout << writer.write(ret) << endl;
	return 0;
}