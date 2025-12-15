#include <iostream>
#include "Game.h"
#include "Block.h"
#include <time.h>

/*
一个游戏管理对象：绘制，游戏的创建释放，界面的生成
专门的方块类：管理方块的形状，颜色
交互放到main函数中处理

*/


int main() {
	//1.游戏窗口创建
	HWND hd = initgraph(350, 440);
	SetWindowText(hd, L"俄罗斯方块");

	setbkcolor(WHITE);
	cleardevice();
	setlinecolor(BLACK);

	//2.生成游戏数据
	srand(time(NULL));
	Block::generateBlockData();//类中的静态成员函数，在没有实例化对象的情况下，仍然可以直接调用


	//3.绘制界面

	Game game;
	game.drawView();
	game.drawPrompt();

	Block block(game);
	Block next_block(game, 11, 2);
	
	//时间
	clock_t start = 0;
	clock_t end = 0;

	next_block.draw();


	ExMessage em;
	//4.游戏循环(使用while(true)结构实现)
	BeginBatchDraw();//防止闪屏
	while (true) {
		//1.游戏页面更新
		block.clear();
		clearrectangle(20, 20, 220, 420);
		game.drawView();
		
		//2.按键交互
		while (peekmessage(&em, EX_KEY) && em.message == WM_KEYDOWN) {
			switch (em.vkcode) {
			case VK_UP:
				block.rotate();
				break;
			case VK_DOWN:
				if (block.move()) {
					block.addMap();
					block = next_block;
					block.setPos();
					next_block.clear();
					next_block.setPos(11,2);
					next_block.draw();

					if (block.checkCollision()) {
						MessageBox(GetHWnd(), L"结束", L"提示", MB_ICONWARNING);
						goto exit;
					}
				}
				
				break;
			case VK_LEFT:
				block.move(1);
				break;
			case VK_RIGHT:
				block.move(2);
				break;
			}

		}
		end = clock();
		if (end - start >= 500) {
			if (block.move()) {
				block.addMap();
				block = next_block;
				block.setPos();
				next_block.clear();
				next_block.setPos(11, 2);
				next_block.draw();


				if (block.checkCollision()) {
					MessageBox(GetHWnd(), L"结束", L"提示", MB_ICONWARNING);
					goto exit;
				}
			}
			start = clock();
			game.updateTime();
		}

		//3.方块数据更新


		block.draw();
		game.clearLine();

		FlushBatchDraw();
		Sleep(50);
	}

exit:
	EndBatchDraw();
	closegraph();


	//5.游戏释放

	//6.
	return 0;
}