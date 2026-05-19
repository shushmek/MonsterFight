#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>
#include<functional>

using namespace sf;
using namespace std;

class Action
{
public:
	Action(const string& name) : _name(name) {}
	int action(int x);
	void setFunction(function<void()> callback);
private:
	string _name;
	function<void()> _function;
};

