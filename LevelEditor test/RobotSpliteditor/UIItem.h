#ifndef UIITEM
#define UIITEM
#include<SFML/Graphics/RenderWindow.hpp>

using namespace sf;
class UIItem
{
public:
	virtual	~UIItem(void);
	virtual	std::string	getName	();
	virtual bool		selected();
	virtual void		draw	(sf::RenderWindow&,sf::Vector2f Position,sf::Uint8 alpha=255)=0;
	virtual	void		handleEvent	(sf::Event&)=0;
	virtual	void		setChangeablitiy(bool&);
	virtual	bool		getChangeablitiy()const;
	virtual	FloatRect	getHitBox(Vector2f	Position)const=0;
protected:
	UIItem	(void);
	UIItem	(const UIItem&);
	UIItem	(std::string);
	bool		mSelected,mChangeable;
	std::string	mName;
};
#endif