#ifndef INC_UIITEM
#define INC_UIITEM
#include<SFML/Graphics/RenderWindow.hpp>

using namespace sf;
class UIItem
{
public:
	virtual	~UIItem(void);
	virtual	std::string	getName	();
	virtual bool		selected();
	virtual void		draw	(sf::RenderWindow&,sf::Vector2f Position)=0;
	virtual	FloatRect	getHitBox	(Vector2f	Position)const=0;
	virtual	void		setSelect	(const bool&);
	virtual	void		handleEvent	(const sf::Event&,Vector2f	Position)=0;
	virtual	void		setChangeablitiy(bool&);
	virtual	bool		getChangeablitiy()const;
protected:
	UIItem	(void);
	UIItem	(const UIItem&);
	UIItem	(std::string,bool Change);
	bool		mSelected,mChangeable;
	std::string	mName;
};
#endif