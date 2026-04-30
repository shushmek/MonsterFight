#pragma once
#include "Button.h"
class Slider:public Button
{
public:
	Slider(Vector2f const& position, string const& texturePath, string const& buttonText, string const& fontPath, string const& clickSoundPath = "", Color const& textCol = Color::Black, int const& size = 24);
	Slider(Vector2f const& position, Texture const& texture, string const& buttonText, Font const& font, SoundBuffer const& clickSoundBuffer, Color const& textCol = Color::Black, int const& size = 24);
	virtual void handleEvent(Event const& event, RenderWindow const& window);
	void setScale(Vector2f scale);
	void setPosition(Vector2f pos);
	Vector2f getPosition();
	void draw(RenderWindow& window);
	float getSliderNum();
private:

	float _slider = 0;
	Sprite* _background;
	void SlideCalculate(int x);

};


