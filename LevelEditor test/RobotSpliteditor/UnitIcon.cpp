#include "UnitIcon.h"
#include "TextureManager.h"

UnitIcon::UnitIcon(string Type,string Sprite)
	:mType(Type),mSpriteName(Sprite)
{
}

UnitIcon::UnitIcon()
{
}

UnitIcon::~UnitIcon(void)
{
}

void UnitIcon::render(sf::RenderWindow& window,sf::Vector2f Position,int MaxSize)
{
	sf::Sprite	render = TextureManager::getSprite(mSpriteName);
	int i=render.getGlobalBounds().height;
	if(i<render.getGlobalBounds().width)
		i=render.getGlobalBounds().width;
	float Size=MaxSize/i;
	if(Size>1.f)
		Size=1.f;
	render.setScale(Size,Size);
	render.setPosition(Position);
	window.draw(render);
}

sf::FloatRect	UnitIcon::getHitBox(sf::Vector2f& Position)
{
	sf::FloatRect	HitBox(Position,sf::Vector2f(64,64));
	return HitBox;
}

string	UnitIcon::getType()
{
	return	mType;
}

string	UnitIcon::getSpriteName()
{
	return	mSpriteName;
}

void PlayerIcon::render(sf::RenderWindow& window,sf::Vector2f Position,int MaxSize)
{
	sf::Sprite	render1,render2;	
	render1 = TextureManager::getSprite("StixUpper");
	render2 = TextureManager::getSprite("StixLower");
	sf::FloatRect comb=render1.getGlobalBounds();
	comb.height+=render1.getGlobalBounds().height;
	int i=comb.height;
	if(i<comb.width)
		i=comb.width;
	float Size=float(MaxSize)/float(i);
	if(Size>1.f)
		Size=1.f;
	render1.setPosition(Position);
	sf::Vector2f add(0,float(render1.getGlobalBounds().height)*Size);
	render2.setPosition(Position+add);
	render1.setScale(Size,Size);
	render2.setScale(Size,Size);
	window.draw(render2);
	window.draw(render1);
}

PlayerIcon::PlayerIcon()
	:UnitIcon("Player","Player")
{
}