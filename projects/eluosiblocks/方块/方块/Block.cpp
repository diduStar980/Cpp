#include "Block.h"

bool Block::block_data[7][4][4] = { 0 };

Block::Block(Game& game, int x, int y)
	:x(x), y(y), game(game)
{
	type = rand() % 7;

	switch (type) {
	case 0:
		color = LIGHTBLUE;
		break;
	case 1:
		color = GREEN;
		break;
	case 2:
		color = LIGHTGREEN;
		break;
	case 3:
		color = YELLOW;
		break;
	case 4:
		color = RED;
		break;
	case 5:
		color = CYAN;
		break;
	case 6:
		color = MAGENTA;
		break;
	}

	for (int i = 0;i < 4;++i) {
		for (int j = 0;j < 4;++j) {
			cur_block_data[i][j] = block_data[type][i][j];
		}
	}
	direcation = true;
}

bool Block::move(int direction)
{
	switch(direction){
	case 0:
		y++;
		if (checkCollision()){
			y--;
			return true;
		}
		break;
	case 1:
		x--;
		if (checkCollision()) {
			x++;
		}
		break;
	case 2:
		x++;
		if (checkCollision()) {
			x--;
		}
		break;
	}
	return false;//说明没有撞到方块
}

void Block::draw()
{
	for (int i = 0;i < 4;++i) {
		for (int j = 0;j < 4;++j) {
			if (cur_block_data[i][j]) {
				if (j + y >= 0) {
					setfillcolor(this->color);
					int left = 20 + 20 * (x + i);
					int top = 20 + 20 * (y + j);

					fillrectangle(left, top, left + 20, top + 20);
				}
			}
		}
	}
}

void Block::clear()
{
	for (int i = 0;i < 4;++i) {
		for (int j = 0;j < 4;++j) {
			if (cur_block_data[i][j]) {
					int left = 20 + 20 * (x + i);
					int top = 20 + 20 * (y + j);

					clearrectangle(left, top, left + 20, top + 20);
			}
		}
	}

}

void Block::addMap()
{
	for (int i = 0;i < 4;++i) {
		for (int j = 0;j < 4;++j) {
			if (cur_block_data[i][j]) {
				game.setMap(x + i, y + j, cur_block_data[i][j]);
			}
		}
	}

}

void Block::rotate()
{
	if (type == 4)
		return;

	bool temp=0;

	if (!direcation) {
		
		//角旋转
		temp = cur_block_data[0][0];
		cur_block_data[0][0] = cur_block_data[0][2];
		cur_block_data[0][2] = cur_block_data[2][2];
		cur_block_data[2][2] = cur_block_data[2][0];
		cur_block_data[2][0] = temp;

		//十字中心旋转
temp = cur_block_data[1][0];
cur_block_data[1][0] = cur_block_data[0][1];
cur_block_data[0][1] = cur_block_data[1][2];
cur_block_data[1][2] = cur_block_data[2][1];
cur_block_data[2][1] = temp;
	}
	else {
		//角旋转
		temp = cur_block_data[0][0];
		cur_block_data[0][0] = cur_block_data[2][0];
		cur_block_data[2][0] = cur_block_data[2][2];
		cur_block_data[2][2] = cur_block_data[0][2];
		cur_block_data[0][2] = temp;

		//十字中心旋转
		temp = cur_block_data[1][0];
		cur_block_data[1][0] = cur_block_data[2][1];
		cur_block_data[2][1] = cur_block_data[1][2];
		cur_block_data[1][2] = cur_block_data[0][1];
		cur_block_data[0][1] = temp;
	}

	switch (type) {
		//长条方块
	case 0:
		if (cur_block_data[1][3]) {
			cur_block_data[1][3] = false;
			cur_block_data[3][1] = true;
		}
		else {
			cur_block_data[1][3] = true;
			cur_block_data[3][1] = false;
		}
		break;

		//z形方块
	case 5:

	case 6:
		if (!checkCollision()) {
			direcation = !direcation;
		}
	}

	if (checkCollision()) {
		if (direcation == true) {
			//角旋转
			temp = cur_block_data[0][0];
			cur_block_data[0][0] = cur_block_data[0][2];
			cur_block_data[0][2] = cur_block_data[2][2];
			cur_block_data[2][2] = cur_block_data[2][0];
			cur_block_data[2][0] = temp;

			//十字中心旋转
			temp = cur_block_data[1][0];
			cur_block_data[1][0] = cur_block_data[0][1];
			cur_block_data[0][1] = cur_block_data[1][2];
			cur_block_data[1][2] = cur_block_data[2][1];
			cur_block_data[2][1] = temp;
		}
		else {
			//角旋转
			temp = cur_block_data[0][0];
			cur_block_data[0][0] = cur_block_data[2][0];
			cur_block_data[2][0] = cur_block_data[2][2];
			cur_block_data[2][2] = cur_block_data[0][2];
			cur_block_data[0][2] = temp;

			//十字中心旋转
			temp = cur_block_data[1][0];
			cur_block_data[1][0] = cur_block_data[2][1];
			cur_block_data[2][1] = cur_block_data[1][2];
			cur_block_data[1][2] = cur_block_data[0][1];
			cur_block_data[0][1] = temp;
		}

		if (type == 0) {
			if (cur_block_data[1][3]) {
				cur_block_data[1][3] = false;
				cur_block_data[3][1] = true;
			}
			else {
				cur_block_data[1][3] = true;
				cur_block_data[3][1] = false;
			}
		}
	}

}

bool Block::checkCollision() const
{
	for (int i = 0;i < 4;++i) {
		for (int j = 0;j < 4;++j) {
			if((game.getMap(x + i, y + j)
				|| 20 + 20 * (x + i) < 20
				|| 20 + 20 * (x + i) + 20 > 220
				|| 20 + 20 * (j + y) + 20 > 420)
				&& cur_block_data[i][j]
				){
				return true;
				}
		}
	}
	return false;
}

void Block::generateBlockData()
{
	//长条方块
	block_data[0][1][0] = block_data[0][1][1] = block_data[0][1][2] = block_data[0][1][3] = true;
	//正7字形方块
	block_data[1][0][0] = block_data[1][1][0] = block_data[1][1][1] = block_data[1][1][2] = true;
	//反7字形方块
	block_data[2][2][0] = block_data[2][1][0] = block_data[2][1][1] = block_data[2][1][2] = true;
	//凸字方块
	block_data[3][1][0] = block_data[3][0][1] = block_data[3][1][1] = block_data[3][2][1] = true;
	//田字方块
	block_data[4][0][0] = block_data[4][0][1] = block_data[4][1][1] = block_data[4][1][0] = true;
	//正z形方块
	block_data[5][0][0] = block_data[5][1][0] = block_data[5][1][1] = block_data[5][2][1] = true;
	//反z形方块
	block_data[6][2][0] = block_data[6][1][0] = block_data[6][1][1] = block_data[6][0][1] = true;
}

void Block::setPos(int x, int y)
{
	this->x = x;
	this->y = y;

}

void Block::randType()
{
	this->type = rand() % 7;
	type = rand() % 7;

	switch (type) {
	case 0:
		color = LIGHTBLUE;
		break;
	case 1:
		color = GREEN;
		break;
	case 2:
		color = LIGHTGREEN;
		break;
	case 3:
		color = YELLOW;
		break;
	case 4:
		color = RED;
		break;
	case 5:
		color = CYAN;
		break;
	case 6:
		color = MAGENTA;
		break;
	}

	for (int i = 0;i < 4;++i) {
		for (int j = 0;j < 4;++j) {
			cur_block_data[i][j] = block_data[type][i][j];
		}
	}
	direcation = true;
}

void Block::operator=(const Block& block)
{
	x = block.x;
	y = block.y;
	type = block.type;
	direcation = block.direcation;
	for (int i = 0;i < 4;++i) {
		for (int j = 0;j < 4;++j) {
			this->cur_block_data[i][j] = block.cur_block_data[i][j];
		}
	}
	color = block.color;

}




