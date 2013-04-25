#ifndef		INC_TOOLBAR
#define		INC_TOOLBAR
#include	<SFML/Graphics.hpp>
#include	"Container.h"
#include	"Unit.h"
#include	"Player.h"
#include	"Level.h"
#include	"UIItemContainer.h"

typedef	Container<Unit>		UnitContainer;
typedef	Container<Player>	PlayerContainer;

using namespace sf;

class	Editor;

class Toolbar
{
public:
	Toolbar	(Vector2f Position=Vector2f(1080,50),Vector2f Size=Vector2f(200,728),Color BackColor=Color(150,150,150),Vector2f MiniViewSize=Vector2f(200,120));
	~Toolbar(void);
	void		render	(Editor*);
	Vector2f	getSize	();
	void		setUnit	(Unit*);
	bool		checkHit(const Vector2f&)const;
	void		setPlayer	(Player*);
	void		setSelect	(const	bool&);
	void		unIniUnit	();
	void		unIniPlayer	();
	bool		isSelected	()const;
	Vector2f	getPosition	();
	void		eventHandle	(const	Event&);
	bool		mChange;
	void		resize		(RenderWindow&);
	void		setTargets	(Level&);
	PlayerContainer	getPlayCont();
private:
	void		setUIActives();
	void		update();
	UnitContainer	mCurrUnit;
	PlayerContainer	mCurrPlayer;
	UIItemContainer	mUIItems;
	Color			mBackground;
	Vector2f		mSize,mPosition,mViewSize;
	bool			mSelected,mNewPos,mDelete;
};

#endif