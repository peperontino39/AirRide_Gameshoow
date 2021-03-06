#include "Enemy.h"

Enemy::Enemy()
{
	is_hit = false;
	mesh = &ObjDataGet.find("Enemy");
}

Enemy::~Enemy()
{


}

void Enemy::setup()
{
	init();

	collision_circle_rad = 1.0f;
}



void Enemy::update()
{
	ai->update();


	move();
	damage();
	updateStageMatrix();
}

void Enemy::draw()
{
	ci::gl::popMatrices();

	ci::gl::pushMatrices();
	ci::gl::multModelView(matrix);
	
	ci::Matrix44f mrotate = ci::Matrix44f::createRotation(transform.angle);
	ci::gl::multModelView(mrotate);
	ci::gl::scale(0.07f, 0.07f, 0.07f);

	ci::gl::draw(*mesh);
	//ci::gl::drawColorCube(ci::Vec3f::zero(), ci::Vec3f::one());
	ci::gl::popMatrices();

	ci::gl::pushMatrices();

}



void Enemy::setPlayer(std::shared_ptr<CharaBase> _player)
{
	player = _player;
}

void Enemy::setTarget(const bool & _is_terget)
{
	ai->setTerget(_is_terget);
}

bool Enemy::getTarget()
{
	return ai->getTerget();
}

bool Enemy::isEnd()
{
	return ai->HP <= 0;
}

void Enemy::inObstacleArea()
{
	isRolling(transform.position.xy().inverse());

}

void Enemy::start()
{
	ai->go();


}

void Enemy::damage()
{

	if (player->isAttack()) {
		if (!isInvincible()) {
			if (player->transform.position.distanceSquared(
				transform.position) <
				(player->getCollisionCirclerad() + collision_circle_rad)
				*(player->getCollisionCirclerad() + collision_circle_rad)
				) {
				if (!is_hit) {
					ai->HP--;
					HitObstacle(2.5f);
				}
					is_hit = true;
					return;
			}
		}
	}
	is_hit = false;
}
