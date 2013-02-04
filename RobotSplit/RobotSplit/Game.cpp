#include "Game.h"
#include "StateInput.h"

Game::Game(): q(0), mStateInput(StateInput::getInstance())
{}

Game::~Game()
{
	std::cout << "Game DELETE" << std::endl;
}

void Game::update()
{
	q++;
	choice();
}

void Game::render()
{
	std::cout << "Game" << std::endl;
}

void Game::choice()
{
	int p;
	std::cin >> p;
	if(p == 1)
		mStateInput.changeState("InGameMenu");
	else
		std::cout << "Error" << std::endl;
}