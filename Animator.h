#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <unordered_map>
#include<functional>
#include<iostream>
#include <cmath>

using namespace sf;
using namespace std;

class Animator
{
public:
	explicit Animator(Sprite& sprite, IntRect const& rect, int frameCount, int frameTime = 0, float animTime = 0);
	void play();
	void pause();
	void stop();
	bool getPlay();
	void setLoop(bool loop);
	void setFrameTime(int frametime = 100);
	void setAnimTime(float animTime = 1.f);
	void update(Time delta);
	void reset();
	bool isFinished() const;
	void setOnFinished(function<void()> callback);

private:
	Sprite& _sprite;
	int _currentFrame = 0;
	vector<IntRect> _frames;
	Clock _clock;
	int _frameTime;
	float _animTime;
	bool _playing;
	bool _loop;
	bool _finished;
	function<void()> _onFinished;
};

