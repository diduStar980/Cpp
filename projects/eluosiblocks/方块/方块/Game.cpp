#include "Game.h"

void Game::drawView()
{
	//绘制游戏边框
	roundrect(10, 10, 340, 430, 10, 10);//框的顶点的坐标是从左上角为原点计算的
	rectangle(20, 20, 220, 420);

	//绘制游戏区域
	setfillcolor(LIGHTCYAN);//方块颜色
	for (int i = 0;i < MAP_WIDTH;++i) {
		for (int j = 0;j < MAP_HEIGHT;++j) {
			if (map[i][j]) {
				int left = 20 + i * 20;
				int top = 20 + j * 20;

				fillrectangle(left, top, left + 20, top + 20);//此函数需要左上角和右下角点的坐标，分别是x,y值

			}
		}
	}

}	


void Game::drawPrompt()
{
	//设置字体
	LOGFONT f;
	gettextstyle(&f);//获取当前所有字体属性, 只修改需要改变的属性,其他属性（颜色、粗细、斜体等）保持不变
	f.lfHeight = 30;//字体高度
	wcscpy_s(f.lfFaceName, L"微软雅黑");// wcscpy_s 是一个安全的宽字符串拷贝函数,将宽字符串 L"微软雅黑" 拷贝到 f.lfFaceName 字符数组中
	f.lfQuality = DEFAULT_QUALITY;//lfQuality：控制字体在屏幕上的渲染质量;DEFAULT_QUALITY：使用系统默认的字体渲染质量
	settextstyle(&f);//将配置好的 LOGFONT 结构体中的字体设置应用到当前的图形设备上下文中
	settextcolor(BLACK);//设置字体颜色

	//绘制提示
	outtextxy(235, 20, L"下一个方块");//L 前缀是为了确保中文字符能够正确显示
	rectangle(240, 60, 320, 140);

	f.lfHeight = 25;
	settextstyle(&f);

	//绘制分数
	wchar_t str[10];
	wsprintf(str, L"分数：%d", this->score);//假设 this->score = 100，那么 str = L"分数：100"
	outtextxy(230, 150, str);//位置

	//绘制时间
	wsprintf(str, L"时间：%d", this->game_time/1000);
	outtextxy(230, 175, str);

	//绘制游戏标题
	f.lfHeight = 40;
	settextstyle(&f);
	settextcolor(BLUE);

	outtextxy(234, 250, L"Tetris");

}

bool Game::checkLine(int line) const
{
	for (int i = 0;i < MAP_WIDTH;++i) {
		if (map[i][line] == 0) {
			return false;
		}
	}
	return true;
}

void Game::clearLine()
{
	int line = -1;//记录满的是第几行
	for (int i = 0;i < MAP_HEIGHT;++i) {
		if (checkLine(i)) {
			line = i;
			break;
		}
	}

	if (line != -1) {
		for (int i = line;i > 0;--i) {
			for (int j = 0; j < MAP_WIDTH; ++j) {
				map[j][i] = map[j][i - 1];
			}
		}

		this->score += 10;
	}

	this->drawPrompt();
}

void Game::updateTime()
{
	game_time += 500;//延迟
}

void Game::setMap(int x, int y, bool v)
{
	map[x][y] = v;
}

bool Game::getMap(int x, int y)
{
	return map[x][y];
}


