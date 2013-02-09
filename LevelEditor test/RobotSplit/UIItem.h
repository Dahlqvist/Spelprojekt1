#ifndef UIITEM
#define UIITEM
#include<SFML/Graphics/RenderWindow.hpp>
class UIItem
{
public:
	UIItem(void);
	virtual	~UIItem(void);
	virtual void draw(sf::RenderWindow&)=0;
private:
};
#endif