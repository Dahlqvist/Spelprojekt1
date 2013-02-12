#include "Option.h"
#include "StateInput.h"

Option::Option(): mStateInput(StateInput::getInstance())
{}

Option::~Option()
{}

void Option::update()
{
	input();
}

void Option::render()
{}

void Option::input()
{}