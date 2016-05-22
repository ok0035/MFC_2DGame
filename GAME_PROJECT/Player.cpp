#include "stdafx.h"
#include "Player.h"
#include<iostream>
#include<ctime>


Player::Player(int px, int py, int speed)
	: current_x(0)
	, current_y(0)
	, des_x(0)
	, des_y(0)
	, dx(0)
	, dy(0)
	, isRight(false)
	, isMotion(false)
	, spd(10)
{
	srand((unsigned)time(NULL));
	current_x = px;
	current_y = py;
	this->isRight = false;
	this->isMotion = false;
	spd = speed;
	des_x = rand() % 1000;
	des_y = rand() % 300 + 400;
}


Player::~Player()
{
}

void Player::Move() {
	//ĳ������ ������ ǥ��

	srand((unsigned)time(NULL));
	int rn = rand() % 5;

	if (abs(current_x - des_x) > abs(current_y - des_y)) {
		dx = spd + rn;
		dy = spd;
	}

	else if (abs(current_x - des_x) < abs(current_y - des_y)) {
		dx = spd;
		dy = spd + rn;
	}

	else {
		dx = spd + 2;
		dy = spd + 2;
	}

	if (abs(current_x - des_x) < dx) dx = abs(current_x - des_x);
	if (abs(current_y - des_y) < dy) dy = abs(current_y - des_y);

	if (des_x < current_x && des_y < current_y) {
		current_x -= dx;
		current_y -= dy;
	}

	else if (des_x > current_x && des_y < current_y) {
		current_x += dx;
		current_y -= dy;
	}

	else if (des_x < current_x && des_y > current_y) {
		current_x -= dx;
		current_y += dy;
	}

	else if (des_x > current_x && des_y > current_y) {
		current_x += dx;
		current_y += dy;
	}

	else if (current_x == des_x && des_y > current_y) current_y += dy;
	else if (current_x == des_x && des_y < current_y) current_y -= dy;
	else if (current_y == des_y && des_x > current_x) current_x += dx;
	else if (current_y == des_y && des_x < current_x) current_x -= dx;
	else return;

	//ĳ���Ͱ� ���� ����
	if (des_x > current_x) isRight = TRUE;
	else if (des_x < current_x) isRight = FALSE;
	else return;
}

void Player::Motion() {
	if (isMotion == TRUE) isMotion = FALSE;
	else isMotion = TRUE;
}

//�̵����� �ʾ����� �ȴ� ����� ������ �ʰ��ϱ� ����
bool Player::isMove()
{
	if(dx == 0 && dy == 0)
		return false;
	else 
		return true;
}

//ĳ���� ������ ����
void Player::SetDestination(int destination_x, int destination_y)
{
	des_x = destination_x;
	des_y = destination_y;
}

//x��ǥ ��ȯ
int Player::GetCurrentX()
{
	return current_x;
}

//y��ǥ ��ȯ
int Player::GetCurrentY()
{
	return current_y;
}

//�����ߴ��� Ȯ��
bool Player::isArrive()
{
	if(current_x == des_x && current_y == des_y)
		return true;
	else return false;
}


void Player::SetRandomDesX()
{
	des_x = rand() % 1000;
}


void Player::SetRandomDesY()
{
	des_y = (rand() % 300) + 400;
}


void Player::SetRandomCurrentX()
{
	current_x = rand() % 1000;
}


void Player::SetRandomCurrentY()
{
	current_y = (rand() % 300) + 300;
}
