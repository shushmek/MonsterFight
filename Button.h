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
	bool isPressed = false; //состояние нажата ли. внутри функций не используется(я имею ввиду за функции в Button.cpp)
	Clock clock; // время, может работать как таймер
	Button(Vector2f const& position, string const& texturePath, string const& buttonText, string const& fontPath, string const& clickSoundPath = "", Color const& textCol = Color::Black, int const& size = 24);
	//↑ конструктор в котором нужно задавать пути, например: Button btn({200, 200}, "путь к текстуре", "текст на кнопке", "путь к шрифту", "путь к звуковому буферу(если нет писать "")", цвет текста, размер текста ); {200, 200}-координаты расположения кнопки
	Button(Vector2f const& position, Texture const& texture, string const& buttonText, Font const& font, SoundBuffer const& clickSoundBuffer, Color const& textCol = Color::Black, int const& size = 24);
	//↑ конструктор в котором нужно задавать объекты, например: Button btn({200, 200}, текстура, "текст на кнопке", шрифт,буфер звука, цвет текста, размер текста ); {200, 200}-координаты расположения кнопки
	void setOnClick(function<void()> callback); // лямбда функция вызываемая при нажатии, т.е. функция при вызове которой происходит что угодно, например: btn.setOnClick([]() {cout << "hello" << endl; });
												// НЕ ЗАБУТЬ ЗА ТОЧКУ С ЗАПЯТОЙ! в данном примере при нажатии на кнопку выводится "hello"
	virtual void handleEvent(Event const& event, RenderWindow const& window); //проверка на нажатие. Нужно засунуть в Input() в Engine.cpp 
	void draw(RenderWindow& window) const; // отрисовка кнопки. Нужно засунуть в Draw() в Engine.cpp 
	void setText(string const& text); //задать текст кнопки
	void setEnable(bool enable); //изменить кликабельность кнопки
	bool isEnable() const; //активна ли кнопка, если нет то на нее нельзя нажать
	void setSize(float x, float y); // изменитиь размер
  void setTextColor(Color const& txt, Color const& outline = Color::Black); // изменить цвет текста
  void setSpriteColor(Color const& color); // изменить цвет спрайта

protected:
	Sprite *sprite;
	Text *text;
	Sound *clickSound;
	bool enable;
	function<void()> onClickCallback;
	void centerText();
};

