#include "Option.h"
#include "StateInput.h"

Option::Option(): p(0), mStateInput(StateInput::getInstance())
{}

Option::~Option()
{}

void Option::update()
{
	p++;
	choice();
}

void Option::render()
{}

void Option::choice()
{
	int p;
	std::cin >> p;
	if(p == 1)
		mStateInput.changeState("Last");
}