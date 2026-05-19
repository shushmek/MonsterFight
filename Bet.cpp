#include "Bet.h"

void Bet::draw(RenderWindow& window) const
{
	if (_isActive)
	{
		_slider->draw(window);
		Button::draw(window);
	}
}

void Bet::handleEvent(Event const& event, RenderWindow const& window)
{
	_slider->handleEvent(event, window);
	Button::handleEvent(event, window);
}


void Bet::setActive(bool state)
{
    _isActive = state;
	if (_isActive)
	{
		_slider->setActive(true);
		Button::setActive(true);
	}
	else
	{
		_slider->setActive(false);
		Button::setActive(false);
	}
}

bool Bet::getActive()
{
    return _isActive;
}


void Bet::setSliderText(const string& txt)
{
	_slider->setText(txt);
}

float Bet::getSliderNum()
{
    return _slider->getSliderNum();
}

Bet::Bet()
	:Button({ 875, 300 }, "Sprite/move.png", "ok", "Font/BankGothic.otf", "")
{
	Button::setSize(2,2);
	Button::setTextPosition({ Button::getTextPosition().x, Button::getTextPosition().y - 8 });
	_slider = new Slider({ 350, 300 }, "Sprite/square.jpg", "100000", "Font/BankGothic.otf", "");
	_slider->setScale({ 2,1 });
	_slider->setColor(Color(255,235,0));
	_slider->setSliderNum(0.f);
}
