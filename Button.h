#pragma once
#include<iostream>
#include<functional>
#include<SFML/Graphics.hpp>
#include "AssetManager.h"

using namespace sf;
using namespace std;
class Button
{
public:
	bool isPressed = false;
	Clock clock;
	Button(Vector2f const& position, string const& texturePath, string const& buttonText, string const& fontPath, string const& clickSoundPath = "", Color const& textCol = Color::Black, int const& size = 24);
	Button(Vector2f const& position, Texture const& texture, string const& buttonText, Font const& font, SoundBuffer const& clickSoundBuffer, Color const& textCol = Color::Black, int const& size = 24);
	void setOnClick(function<void()> callback);
	void handleEvent(Event const& event, RenderWindow const& window);
	void draw(RenderWindow& window) const;
	void setText(string const& text);
	void setEnable(bool enable);
	bool isEnable() const;
	void setSize(float x, float y);
	void setTextColor(Color const& txt, Color const& outline = Color::Black);
	void setSpriteColor(Color const& color);

private:
	Sprite *sprite;
	Text *text;
	Sound *clickSound;
	bool enable;
	function<void()> onClickCallback;
	void centerText();
};

