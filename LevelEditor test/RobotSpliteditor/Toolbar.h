#ifndef		INC_TOOLBAR
#define		INC_TOOLBAR
#include	<SFML/Graphics.hpp>
#include	<set>
#include	"UIItem.h"
#include	"Container.h"
#include	"Unit.h"
#include	"Player.h"
#include	"Level.h"

typedef	Container<Unit>		UnitContainer;
typedef	Container<Player>	PlayerContainer;

using namespace sf;

class	Editor;

class	UIItemContainer
{
public:
	UIItemContainer	();
	void				activate	(std::string);
	void				deActivate	(std::string);
	std::set<UIItem*>&	accessActive();
	std::set<UIItem*>&	accessInactive();
private:
	std::set<UIItem*>mActive,mInActive;
};

class Toolbar
{
public:
	void	render(Editor*);
	void	setUnit(Unit*);
	void	setPlayer(Player*);
	bool	checkHit(const Vector2f&);
	Toolbar	(Vector2f	Position=Vector2f(1080,50),Vector2f	Size=Vector2f(200,728),Color BackColor=Color(150,150,150),Vector2f MiniViewSize=Vector2f(200,120));
	~Toolbar(void);
	Vector2f	getSize();
	Vector2f	getPosition();
private:
	UnitContainer		mCurrUnit;
	PlayerContainer		mCurrPlayer;
	UIItemContainer		mUIItems;
	Color				mBackground;
	Vector2f			mSize,mPosition,mViewSize;
};

#endif