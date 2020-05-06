#pragma once
#include "DxLib.h"
#include <math.h>

#define width 640	
#define height 480
#define PI 3.141592653
#define ENEMY_NUM 10

int end_f=FALSE;
int point=0;

class Player{
protected:
	double rad;
	int x, y;
	int cnt;
	int info;
	int p1, p2;
public:
	Player();
	void show();
	void move();
    int getp(int);
	void jump();
	bool live;
};

inline Player::Player(){
	cnt = 0;
	live = true,info = 0;
	x = width / 2;
	y = height / 2;
	rad = 0.0;
	p1 = LoadGraph("Image.png", 0);
	p2 = LoadGraph("Image1.png", 0);
}

inline void Player::show(){

	if (live==true) {
		if (info == 0 || info == 2) {
			DrawRotaGraph(x, y, 2.0, 0, p1,TRUE, 0, 0);
		}
		else if (info==1) {
			DrawRotaGraph(x, y, 2.0, 0, p2, TRUE, 0, 0);
		}
	}
}

inline void Player::move(){
	jump();
	if (info!=2&&CheckHitKey(KEY_INPUT_UP)==TRUE) {
		info = 2;
	}
	else if (cnt == 0&& CheckHitKey(KEY_INPUT_DOWN) == TRUE) {
		info = 1;
	}

}

inline int Player::getp(int x){
	if (x==0) {
		return this->x;
	}
	else if (x==1) {
		return this->info;
	}
}

void Player::jump() {
	if (info == 2) {
		cnt++;
		y = (height / 2) - 50;
	}else {
		info = 0;
	}
	if (cnt > 20) {

		cnt = 0;
		info = 0;
		y = height / 2;
	}

	//printfDx("cnt:(%d)\n",y);
}

class enemy :public Player {
public:
	int p3;
	int type=0;
	enemy();
	void move();
	void show();
	void dead(int x,int y);
};

enemy::enemy() {
	live = FALSE;
	type = GetRand(2);
	x = width, y = height / 2;
	cnt = 0;
	p1 = LoadGraph("Image4.png",TRUE);
	p2 = LoadGraph("Image5.png",TRUE);
	p3 = LoadGraph("Image6.png", TRUE);
}

inline void enemy::dead(int x, int info){
	//printfDx("type:%d	info:%d\n",type,info);
	if(x > this->x-20  &&  x < this->x+20){
		if (info!=type) {
		//	printfDx("Game Over!");
			end_f = true;
		}
		else {
			point++;
			//printfDx("SAFE");
		}
	}
}

inline void enemy::move() {
	
	if (x>0&&live==TRUE) {
		x-=10;
	}
	else {
		type = GetRand(2);
		x = width;
		live = FALSE;
	}
}

inline void enemy::show(){
	if (type==1) {
		DrawRotaGraph(x, y+50, 2.0, 0, p1, TRUE, 0, 0);//sneek
		//DrawGraph(x, y, p1, TRUE);
	}else if(type==0){
		DrawRotaGraph(x, y+10, 2.0, 0, p2, TRUE, 0, 0);//default
		//DrawGraph(x, y+20, p1, TRUE);
	}else if (type == 2) {
		DrawRotaGraph(x, y-50, 2.0, 0, p3, TRUE, 0, 0);//jump
		//DrawGraph(x, y-10, p1, TRUE);
	}
}


