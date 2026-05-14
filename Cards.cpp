#include "Cards.h"

Cards::Cards(Type type, const string& name, int costAP, int costCP, int min, int max, Vector2f const& position, string const& texturePath, string const& buttonText, string const& fontPath, string const& clickSoundPath, Color const& textCol, int const& size)
	:_type(type), _name(name), _costAP(costAP), _costCP(costCP), _minBet(min), _maxBet(max), Button(position, texturePath, buttonText, fontPath, clickSoundPath, textCol, size) 
{
	float x = 1.5f;
	setTextOutline(Color::Black, x );
	_font = AssetManager::GetFont(fontPath);
	_costAPT = new Text(_font);
	
	_costCPT = new Text(_font);
	
	_nameT = new Text(_font);

	_effectT = new Text(_font);
	if (costCP == 0)
	{
		_costCPObj = new Object(AssetManager::GetTexture("Sprite/_ui.png"), IntRect({ 0,0 }, { 32,32 }), 1, 1, 100);
		_costCPT->setString("");
	}
	else
	{
		_costCPObj = new Object(AssetManager::GetTexture("Sprite/_ui.png"), IntRect({ 96,0 }, { 32,32 }), 1, 1, 100);
		_costCPObj->setPosition({ this->getPosition().x+32, this->getPosition().y});
		_costCPT->setPosition({ _costCPObj->getPosition().x + 5, _costCPObj->getPosition().y - 5 });
		_costCPT->setString(to_string(_costCP));
	}
	_effect = new Object(AssetManager::GetTexture("Sprite/_ui.png"), IntRect({ 0 ,0 }, { 32,32 }), 1, 1, 100);
	_effectT->setPosition({ this->getPosition().x + getGlobalSize().x / 2 - _nameT->getGlobalBounds().size.x / 2 + 16, this->getPosition().y + 32 });
	_effect->setPosition({ this->getPosition().x + getGlobalSize().x / 2 - _nameT->getGlobalBounds().size.x / 2 + 16, this->getPosition().y + 32 });
	_costAPT->setPosition({ this->getPosition().x + 5, this->getPosition().y - 5 });
	_costAPT->setString(to_string(_costAP));
	_nameT->setString(_name);
	_nameT->setPosition({this->getPosition().x+ getGlobalSize().x/2 - _nameT->getGlobalBounds().size.x/2 + 16, this->getPosition().y + 32});
	_costAPT->setFillColor(Color::Black);
	_costCPT->setFillColor(Color::Black);
	_nameT->setFillColor(Color::Black);
	_nameT->setCharacterSize(24);
	switch (type)
	{
	case Cards::Attack:
		_typeObj = new Object(AssetManager::GetTexture("Sprite/_ui.png"), IntRect({ 32,0 }, { 32,32 }), 1, 1, 100);
		break;
	case Cards::Defense:
		_typeObj = new Object(AssetManager::GetTexture("Sprite/_ui.png"), IntRect({ 64,0 }, { 32,32 }), 1, 1, 100);
		break;
	case Cards::Utility:
		_typeObj = new Object(AssetManager::GetTexture("Sprite/_ui.png"), IntRect({ 0 ,0 }, { 32,32 }), 1, 1, 100);
		break;
	default:
		_typeObj = new Object(AssetManager::GetTexture("Sprite/_ui.png"), IntRect({ 0 ,0 }, { 32,32 }), 1, 1, 100);
		break;
	}
	_typeObj->setPosition({ this->getPosition().x + 32, this->getPosition().y + 86 });
	this->setTextPosition({this->getTextPosition().x, this->getTextPosition().y - 4 });
	_costAPT->setFillColor(textCol);
	_costAPT->setOutlineColor(Color::Black);
	_costAPT->setOutlineThickness(x);

	_costCPT->setFillColor(textCol);
	_costCPT->setOutlineColor(Color::Black);
	_costCPT->setOutlineThickness(x);

	_nameT->setFillColor(textCol);
	_nameT->setOutlineColor(Color::Black);
	_nameT->setOutlineThickness(x);

	_effectT->setFillColor(textCol);
	_effectT->setOutlineColor(Color::Black);
	_effectT->setOutlineThickness(x);
	_slider.setOnClick([this]() {_slider.setActive(false); Action();}); 
	this->setOnClick([this]() {_slider.setActive(true);});

}

Cards::Type Cards::getType()
{
	return _type;
}

string Cards::getName()
{
	return _name;
}

int Cards::getCostAP()
{
	return _costAP;
}

int Cards::getCostCP()
{
	return _costCP;
}

int Cards::getMinBet()
{
	return _minBet;
}

int Cards::getMaxBet()
{
	return _maxBet;
}

void Cards::draw(RenderWindow& window) const
{
	Button::draw(window);
	_costCPObj->draw(window);
	_typeObj->draw(window);
	window.draw(*_costAPT);
	window.draw(*_costCPT);
	window.draw(*_nameT);
	drawText(window);
	_effect->draw(window);
	window.draw(*_effectT);
	_slider.draw(window);
}

void Cards::setEffect(const string& effect, IntRect const& rect)
{
	_effectT->setString(effect);
	_effect->setRect(rect);
}

void Cards::setEffectPosition(Vector2f pos1, Vector2f pos2)
{
	_effect->setPosition({this->getPosition().x + pos1.x, this->getPosition().y + pos1.y });
	_effectT->setPosition({ this->getPosition().x + pos2.x, this->getPosition().y + pos2.y });
}

void Cards::Action()
{
	_action();
}

void Cards::setAction(function<void()> callback)
{
	_action = move(callback);
}

void Cards::handleEvent(Event const& event, RenderWindow const& window)
{
	if (!active)
		return;
	if (Mouse::isButtonPressed(Mouse::Button::Left))
	{
		Vector2i mousePos = Mouse::getPosition(window);
		FloatRect bounds = sprite->getGlobalBounds();
		if (bounds.contains(static_cast<Vector2f>(mousePos)))
		{
			if (clickSound != nullptr) clickSound->play();
			if (onClickCallback) onClickCallback();
		}
	}
	_slider.handleEvent(event, window);
}

void Cards::setSliderText(const string& txt)
{
	_slider.setSliderText(txt);
}

float Cards::getSliderValue()
{
	return _slider.getSliderNum();
}

void Cards::setActive(bool state)
{
	_active = state;
}

bool Cards::getActive()
{
	return _active;
}
