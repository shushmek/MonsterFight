#pragma once
#include "Slider.h"
class Bet: public Button
{
public:
	Bet();
	void setActive(bool state);
	bool getActive();
	void setSliderText(const string& txt);
	float getSliderNum();
	void draw(RenderWindow& window) const;
	void handleEvent(Event const& event, RenderWindow const& window);
	//Button* _okBTN;// = Button({ 500, 640 }, "Sprite/move.png", "ok", "Font/BankGothic.otf", "");
private:
	bool _isActive = false;
	Slider* _slider;// = Slider({ 500, 640 }, "Sprite/square.jpg", AssetManager::GetTexture("Sprite/SliderFront.png"), "", "Font/BankGothic.otf");
};

