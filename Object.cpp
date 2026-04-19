#include "Object.h"

Object::Object(Texture const& texture, IntRect const& rect, int frameCount, int Ycount, int frameTime, float animTime)
{
	_sprite = new Sprite(texture);
	_anim = new Animator(*_sprite, rect, frameCount, Ycount, frameTime,animTime);
}

void Object::AnimPlay()
{
	_anim->play();
}

void Object::AnimPause()
{
	_anim->pause();
}

bool Object::AnimGetPlay()
{
	return _anim->getPlay();
}

void Object::AnimSetLoop(bool loop)
{
	_anim->setLoop(loop);
}

void Object::AnimSetFrameTime(int frametime)
{
	_anim->setFrameTime(frametime);
}

void Object::AminSetAnimTime(float animTime)
{
	_anim->setAnimTime(animTime);
}

void Object::AnimReset()
{
	_anim->reset();
}

bool Object::AnimIsFinished() const
{
	return _anim->isFinished();
}

void Object::AnimSetOnFinished(function<void()> callback)
{
	_anim->setOnFinished(callback);
}

void Object::AnimUpdate(Time dt)
{
	_anim->update(dt);
}

void Object::AnimStop()
{
	_anim->stop();
}

void Object::draw(RenderWindow& window) const
{
	window.draw(*_sprite);
}

Vector2f Object::getPosition()
{
	return _sprite->getPosition();
}

void Object::setPosition(Vector2f pos)
{
	_sprite->setPosition(pos);
}
