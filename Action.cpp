#include "Action.h"

using namespace std;

int Action::action(int x)
{
	_function();
	return x;
}

void Action::setFunction(function<void()> callback)
{
	_function = move(callback);
}
