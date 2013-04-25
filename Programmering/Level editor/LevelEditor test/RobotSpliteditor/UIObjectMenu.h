#ifndef INC_UIOBJECTMENU
#define INC_UIOBJECTMENU
#include <vector>
#include "UIItem.h"
#include "UnitIcon.h"
#include "Toolbar.h"

using namespace std;

typedef	vector<UnitIcon*>	IconVector;

class UIObjectMenu :
	public UIItem
{
public:
	void		draw(sf::RenderWindow&,sf::Vector2f Position);
	void		addIcon	(UnitIcon *Add);
	void		handleEvent	(const sf::Event&,Vector2f	Position);
	FloatRect	getHitBox	(sf::Vector2f)const;
	UIObjectMenu(string Name,Vector2f& MaxSize,Toolbar*,Color Back=Color(100,100,100,255),int Size=10);
	~UIObjectMenu(void);
private:
	Toolbar*	mHolder;
	int			mBotRow,
				mSize;
	IconVector	mIcons;
	Vector2f	mMaxSize;
	Color		mBackColor;
};

#endif