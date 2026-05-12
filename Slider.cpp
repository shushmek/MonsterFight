#include "Slider.h"

Slider::Slider(Vector2f const& position, string const& texturePath, string const& buttonText, string const& fontPath, string const& clickSoundPath, Color const& textCol, int const& size)
	:Button(position, texturePath, buttonText, fontPath, clickSoundPath, textCol, size)
{
	_background = new Sprite(AssetManager::GetTexture(texturePath));
	sprite->setColor(Color(0, 0, 0));
	_background->setPosition(position);
}

Slider::Slider(Vector2f const& position, string const& texturePath,Texture const& texture, string const& buttonText, string const& fontPath, string const& clickSoundPath, Color const& textCol, int const& size)
	:Button(position, texturePath, buttonText, fontPath, clickSoundPath, textCol, size)
{
	_background = new Sprite(texture);
	_background->setPosition(position);
}

Slider::Slider(Vector2f const& position, Texture const& texture, string const& buttonText, Font const& font, SoundBuffer const& clickSoundBuffer, Color const& textCol, int const& size) 
	:Button(position, texture,buttonText,font, clickSoundBuffer,textCol,size)
{
	_background = new Sprite(*sprite);
	_background->setColor(Color(100, 100, 100));
	_background->setPosition(position);
}

void Slider::handleEvent(Event const& event, RenderWindow const& window)
{
	if (!enable) return;
	if (Mouse::isButtonPressed(Mouse::Button::Left))
	{
		Vector2i mousePos = Mouse::getPosition(window);
		FloatRect bounds = sprite->getGlobalBounds();
		if (bounds.contains(static_cast<Vector2f>(mousePos)))
		{
			if (clickSound != nullptr) clickSound->play();
			if (onClickCallback) onClickCallback();
			SlideCalculate(Mouse::getPosition(window).x);
		}
	}
}

void Slider::setScale(Vector2f scale)
{
	_background->setScale(scale);
	sprite->setScale(scale);
}

void Slider::setPosition(Vector2f pos)
{
	sprite->setPosition(pos);
	_background->setPosition(pos);
}

Vector2f Slider::getPosition()
{
	return _background->getPosition();
}

void Slider::draw(RenderWindow& window)
{
	Button::draw(window);
	window.draw(*_background);
	drawText(window);
}

float Slider::getSliderNum()
{
	return _slider;
}

void Slider::setSliderNum(float x)
{
	_slider = x;
	SetScale(x);
}

void Slider::setBackground(const Texture& texture)
{
	sprite = new Sprite(texture);
	_background->setPosition(sprite->getPosition());
}

void Slider::setColor(const Color& color)
{
	_background->setColor(color);
}

void Slider::SlideCalculate(int x)
{
	_slider = (x - sprite->getPosition().x) / sprite->getGlobalBounds().size.x;
	_background->setScale({_slider * sprite->getScale().x, sprite->getScale().y});
}

void Slider::SetScale(int x)
{
	_background->setScale({ _slider * sprite->getScale().x, sprite->getScale().y });
}


