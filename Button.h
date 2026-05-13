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
	bool isPressed = false; //состояние нажатия. Не используется внутри функций (имеются в виду функции в Button.cpp)
	Clock clock; // время, может работать как таймер
	Button(Vector2f const& position, string const& texturePath, string const& buttonText, string const& fontPath, string const& clickSoundPath = "", Color const& textCol = Color::Black, int const& size = 24);
	//↑ конструктор, где должны быть указаны пути, например: Button btn({200, 200}, "путь к текстуре", "текст кнопки", "путь к шрифту", "путь к звуковому буферу(если его нет, пишите "")", цвет текста, размер текста ); {200, 200}-координаты позиции кнопки
	Button(Vector2f const& position, Texture const& texture, string const& buttonText, Font const& font, SoundBuffer const& clickSoundBuffer, Color const& textCol = Color::Black, int const& size = 24);
	//↑ конструктор, где должны быть указаны объекты, например: Button btn({200, 200}, текстура, "текст кнопки", шрифт, звуковой буфер, цвет текста, размер текста ); {200, 200}-координаты позиции кнопки
	void setOnClick(function<void()> callback); // лямбда-функция, вызываемая при щелчке, т.е. функция, которая может делать что угодно при вызове, например: btn.setOnClick([]() {cout << "привет" << endl; });
												// НЕ ЗАБУДЬТЕ ТОЧКУ С ЗАПЯТОЙ! В этом примере щелчок по кнопке печатает "привет"
	virtual void handleEvent(Event const& event, RenderWindow const& window); //проверка щелчка. Поместите это в Input() в Engine.cpp 
	void draw(RenderWindow& window) const; // отрисовка кнопки. Поместите это в Draw() в Engine.cpp 
	void setText(string const& text); //задать текст кнопки
	void setActive(bool enable); //изменить кликабельность кнопки
	bool isActive() const; //активна ли кнопка; если нет, по ней нельзя щелкнуть
	void setSize(float x, float y); // изменить размер
  void setTextColor(Color const& txt, Color const& outline = Color::Black); // изменить цвет текста
  virtual void setSpriteColor(Color const& color); // изменить цвет спрайта

protected:
	Sprite *sprite = nullptr;
	Text *text = nullptr;
	Sound *clickSound = nullptr;
	bool enable = false;
	function<void()> onClickCallback;
	void centerText();
};
