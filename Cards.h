#pragma once
#include "Button.h"
#include "Player.h"
#include "Bet.h"

using namespace sf;
using namespace std;

class Cards:public Button
{
public:
	enum Type {Attack, Defense, Utility};
	Cards(Type type, const string& name, int costAP, int costCP, int min, int max, Vector2f const& position, string const& texturePath, string const& buttonText, string const& fontPath, string const& clickSoundPath = "", Color const& textCol = Color::White, int const& size = 24);
	Type getType();
	string getName();
	int getCostAP();
	int getCostCP();
	int getMinBet();
	int getMaxBet();
	void draw(RenderWindow& window) const;
	void setEffect(const string& effect, IntRect const& rect, int size = 24);
	void setEffectPosition(Vector2f pos1, Vector2f pos2);
	void Action();
	void setAction(function<void()> callback);
	virtual void handleEvent(Event const& event, RenderWindow const& window);
	void setSliderText(const string& txt);
	float getSliderValue();
	void setActive(bool state);
	bool getActive();
	void setPosition(Vector2f pos);
	void setTypeObj(int id);
	void setTextButton(const string& str);
private:
	bool _active = false;
	Bet _slider;
	Type _type;
	string _name;
	int _costAP;
	int _costCP;
	int _minBet;
	int _maxBet;
	Font _font;
	Text* _costAPT;
	Text* _costCPT;
	Text* _nameT;
	Object* _typeObj;
	Object* _costCPObj;
	Object* _effect;
	Text* _effectT;
	function<void()> _action;
};

