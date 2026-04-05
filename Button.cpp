#include "Button.h"


Button::Button(Vector2f const& position, string const& texturePath, string const& buttonText, string const& fontPath, string const& clickSoundPath, Color const& textCol, int const& size) : enable(true)
{
	Texture& texture = AssetManager::GetTexture(texturePath);
	sprite = new Sprite(texture);
	sprite->setPosition(position);

	Font& font = AssetManager::GetFont(fontPath);
	text = new Text(font);
	text->setString(buttonText);
	text->setCharacterSize(size);
	text->setFillColor(textCol);
	centerText();
	if (!clickSoundPath.empty())
	{
		SoundBuffer& soundBuffer = AssetManager::GetSoundBuffer(clickSoundPath);
		clickSound = new Sound(soundBuffer);
	}
}

Button::Button(Vector2f const& position, Texture const& texture, string const& buttonText, Font const& font, SoundBuffer const& clickSoundBuffer, Color const& textCol, int const& size) : enable(true)
{
	sprite = new Sprite(texture);
	sprite->setPosition(position);
	text = new Text(font);
	text->setString(buttonText);
	text->setCharacterSize(size);
	text->setFillColor(textCol);
	centerText();
	clickSound = new Sound(clickSoundBuffer);
}

void Button::setOnClick(function<void()> callback)
{
	onClickCallback = move(callback);
}

void Button::handleEvent(Event const& event, RenderWindow const& window)
{
	if (!enable)
		return;
	if (Mouse::isButtonPressed(Mouse::Button::Left))
	{
		Vector2i mousePos = Mouse::getPosition(window);
		FloatRect bounds = sprite->getGlobalBounds();
		if (bounds.contains(static_cast<Vector2f>(mousePos)))
		{
			if(clickSound != nullptr) clickSound->play();
			if (onClickCallback) onClickCallback();
		}
	}
}

void Button::draw(RenderWindow& window) const
{
	window.draw(*sprite);
	window.draw(*text);
}

void Button::setText(string const& txt)
{
	text->setString(txt);
	centerText();
}

void Button::setEnable(bool state)
{
	enable = state;
}

bool Button::isEnable() const
{
	return false;
}

void Button::setSize(float x, float y)
{
	sprite->setScale({ x, y });
	centerText();
}

void Button::setTextColor(Color const& txt, Color const& outline)
{
	text->setFillColor(txt);
	text->setOutlineColor(outline);
}

void Button::setSpriteColor(Color const& color)
{
	sprite->setColor(color);
}

void Button::centerText()
{
	FloatRect spriteBounds = sprite->getGlobalBounds();
	FloatRect textBouns = text->getGlobalBounds();
	text->setOrigin({ textBouns.size.x / 2, textBouns.size.y / 2 });
	text->setPosition({ spriteBounds.position.x + spriteBounds.size.x / 2,spriteBounds.position.y + spriteBounds.size.y / 2 });
}
