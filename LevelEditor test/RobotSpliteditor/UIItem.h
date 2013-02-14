#ifndef UIITEM
#define UIITEM
#include<SFML/Graphics/RenderWindow.hpp>
class UIItem
{
public:
	UIItem(void);
	virtual	~UIItem(void);
	virtual bool selected();
	virtual void draw(sf::RenderWindow&,sf::Uint8 alpha=255)=0;
	virtual	void handleEvent(sf::Event&)=0;	
private:
	bool	mSelected;
};
#endif