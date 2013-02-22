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
	UnitIcon(string Type,string Sprite);
protected:
	UnitIcon();
private:
	string	mType,mSpriteName;
};

class PlayerIcon
	:public UnitIcon
{
public:
	PlayerIcon();
	void		render	(sf::RenderWindow&,sf::Vector2f,int MaxPixel);
};
#endif