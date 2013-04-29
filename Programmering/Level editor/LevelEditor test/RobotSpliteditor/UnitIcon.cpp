#include "UnitIcon.h"
#include "TextureManager.h"

UnitIcon::UnitIcon(string Type,string Sprite,sf::Vector2f Size,sf::Vector2f Offset,int FPS,int Speed)
	:mType(Type),mSpriteName(Sprite),mFrames(FPS),mSpeed(Speed),mSize(Size),mOffset(Offset)
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
	render.setTextureRect(sf::IntRect(sf::Vector2i(0,0),sf::Vector2i(render.getTextureRect().width/mFrames,render.getGlobalBounds().height)));
	int i=render.getGlobalBounds().height;
	if(i<render.getTextureRect().width)
		i=render.getTextureRect().width;
	float Size=float(MaxSize)/float(i);
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

int	UnitIcon::getFrames()
{
	return	mFrames;
}

int	UnitIcon::getSpeed()
{
	return	mSpeed;
}

sf::Vector2f	UnitIcon::getOffset()
{
	return mOffset;
}

sf::Vector2f	UnitIcon::getSize()
{
	return mSize;
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
