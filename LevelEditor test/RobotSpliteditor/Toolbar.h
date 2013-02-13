#ifndef		INC_TOOLBAR
#define		INC_TOOLBAR
#include	<SFML/Graphics.hpp>
#include	<vector>
#include	"UIItem.h"
#include	"Container.h"
#include	"Unit.h"
#include	"Player.h"
#include	"Level.h"

typedef	Container<Unit>		UnitContainer;
typedef	Container<Player>	PlayerContainer;

using namespace sf;

class	Editor;

class Toolbar
{
public:
	void	render(Editor*);
	Toolbar(Vector2f	Position=Vector2f(1080,50),Vector2f	Size=Vector2f(200,728),Color BackColor=Color(150,150,150),Vector2f MiniViewSize=Vector2f(200,120));
	~Toolbar(void);
	void	setUnit(Unit*);
	void	setPlayer(Player*);
	bool	checkHit(const Vector2f&);
	Vector2f	getSize();
	Vector2f	getPosition();
private:
	UnitContainer		mCurrUnit;
	PlayerContainer		mCurrPlayer;
	std::vector<UIItem*>mMenu;
	Color				mBackground;
	Vector2f			mSize,mPosition,mViewSize;
};

#endif