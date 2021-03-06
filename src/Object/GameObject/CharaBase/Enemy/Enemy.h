#pragma once
#include "../CharaBase.h"
#include "../../SignPost/SignPostManager.h"
#include "EnemyAI/EnemyAIBase.h"
#include "EnemyAI/EnemyAI.h"
#include "../Player/Player.h"
#include "cinder/TriMesh.h"


class Enemy : public CharaBase
{
public:
	Enemy();
	~Enemy();
	void setup() override;
	void update() override;
	void draw() override;

	void setPlayer(std::shared_ptr<CharaBase>);
	void setTarget(const bool&);
	bool getTarget();


	bool isEnd();

	template<class T>
	void setAI();
	void inObstacleArea();

	void start();


private:
	void damage();
	std::shared_ptr<EnemyAIBase> ai;
	std::shared_ptr<CharaBase> player;
	bool is_hit;

	ci::TriMesh* mesh;
	
};

template<class T>
void Enemy::setAI()
{
	ai = std::make_shared<T>(T(static_cast<CharaBase*>(this), player.get()));
	ai->stert();
}
