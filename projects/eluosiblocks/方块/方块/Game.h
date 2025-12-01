#pragma once
//推荐将类名和文件名设置为一致的
#include <easyx.h>

#define MAP_WIDTH 10
#define MAP_HEIGHT 20

class Game {
public:
	// 绘制游戏界面
	void drawView();
	//绘制数据界面
	void drawPrompt();
	//判断是否满行
	bool checkLine(int line)const;
	//消除满行
	void clearLine();

	//更新游戏时间
	void updateTime();
	//设置方块数据
	void setMap(int x, int y, bool v);
	//获取map数据
	bool getMap(int x, int y);




private:
	bool map[MAP_WIDTH][MAP_HEIGHT]{false};//定义一个二维数组，用来存储方块的颜色。真则有颜色，假则为白色
	int score = 0;//score
	int game_time = 0;//游戏时间
	
};