#pragma once
#include "Game.h"
#include "easyx.h"

class Block {
public:
	Block(Game& game, int x = (MAP_WIDTH - 4) / 2, int y = 0);

	
	bool move(int direction = 0);//方块的移动,0向下，1向左，2向右
	void draw();//绘制
	void clear();//清除轨迹
	void addMap();//将方块数据添加到地图中
	void rotate();//方块的旋转
	bool checkCollision() const;//检测碰撞
	static void generateBlockData();//生成方块数据
	void setPos(int x = (MAP_WIDTH - 4) / 2, int y = 0);//设置坐标
	void randType();//随机方块类型
	
	void operator=(const Block& block);//重载=运算符

private:
	int x;
	int y;
	int type;
	COLORREF color;
	Game& game;
	static bool block_data[7][4][4];//存储7种方块的形状数据 **在类中声明的静态成员必须要在类外进行初始化。**
	bool cur_block_data[4][4];//当前使用的是哪个方块形状
	bool direcation;//定义方块旋转的方向：左%右
};
