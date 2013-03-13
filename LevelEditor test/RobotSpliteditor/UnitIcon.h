#ifndef	INC_UNITICON
#define INC_UNITICON
#include <SFML\Graphics\RenderWindow.hpp>
#include <string>

using namespace std;

class UnitIcon
{
public:
	virtual	void	render(sf::RenderWindow&,sf::Vector2f,int MaxPixel=64);
	virtual ~UnitIcon(void);
	sf::FloatRect	getHitBox(sf::Vector2f&	position);
	string			getType();
	string			getSpriteName();
	int				getFrames();
	int				getSpeed();
	sf::Vector2f	getOffset();
	sf::Vector2f	getSize();
	UnitIcon(string Type,string Sprite,sf::Vector2f Size=sf::Vector2f(0,0),sf::Vector2f Offset=sf::Vector2f(0,0),int Frames=1,int Speed=60);
protected:
	UnitIcon();
private:
	sf::Vector2f	mOffset,mSize;
	string	mType,mSpriteName;
	int mFrames,mSpeed;
};

class PlayerIcon
	:public UnitIcon
{
public:
	PlayerIcon();
	void		render	(sf::RenderWindow&,sf::Vector2f,int MaxPixel);
};
#endif