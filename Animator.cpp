#include "Animator.h"

Animator::Animator(Sprite& sprite, IntRect const& rect, int frameCount, int Ycount, int frameTime, float animTime) : _sprite(sprite), _playing(true), _loop(true), _finished(false), _animTime(animTime), _frameTime(frameTime), _maxYframe(Ycount)
{
	if (_frameTime == 0)	_frameTime = static_cast<int>(std::round(_animTime * 1000 / frameCount));

	_frames.clear();
	_frames.reserve(frameCount*Ycount);
	for (int j = 0; j < Ycount; j++)
	{
		for (int i = 0; i < frameCount; i++) 
			_frames.emplace_back(IntRect({ rect.position.x + i * rect.size.x, rect.position.y + j * rect.size.y}, { rect.size.x , rect.size.y }));
	}

	_sprite.setTextureRect(_frames[0]);
}

void Animator::play()
{
	if (_finished && !_loop)
		reset();
	_playing = true;
	_finished = false;
}


void Animator::pause()
{
	_playing = false;
}

void Animator::stop()
{
	_playing = false;
	reset();
	_finished = false;
}

bool Animator::getPlay()
{
	return _playing;
}

void Animator::reset()
{
	_currentFrame = 0;
	_sprite.setTextureRect(_frames[0]);
	_clock.restart();
}

void Animator::setLoop(bool loop)
{
	_loop = loop;
}

void Animator::setFrameTime(int frametime)
{
	_frameTime = frametime;
}

void Animator::setAnimTime(float animTime)
{
	_animTime = animTime;
	_frameTime = static_cast<int>(std::round(_animTime * 1000 / _frames.size()));

}


void Animator::update(Time delta)
{
	if (!_playing) return;
	if (_frames.size() == 0) return;
	if (_finished && !_loop) return;

	if (_clock.getElapsedTime() > milliseconds(_frameTime))
	{
		_clock.restart();
		if (_currentFrame == _frames.size() - 1)
		{
			if (_loop) _currentFrame = 0;
			else
			{
				_finished = true;
				_playing = false;
				_onFinished();
			}
		}
		else _currentFrame++;

		_sprite.setTextureRect(_frames[_currentFrame]);
	}
}

bool Animator::isFinished() const
{
	return _finished;
}

void Animator::setOnFinished(function<void()> callback)
{
	_onFinished = move(callback);
}
