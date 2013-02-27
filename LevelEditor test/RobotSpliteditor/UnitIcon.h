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
	string	getType();
	string	getSpriteName();
	int		getFrames();
	int		getSpeed();
	UnitIcon(string Type,string Sprite,int Frames=1,int Speed=60);
protected:
	UnitIcon();
private:
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