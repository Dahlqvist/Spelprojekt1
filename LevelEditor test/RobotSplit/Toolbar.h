#ifndef		INC_TOOLBAR
#define		INC_TOOLBAR
#include	<SFML/Graphics.hpp>
#include	<vector>
#include	"UIItem.h"
#include	"Container.h"
#include	"Unit.h"
#include	"Player.h"

typedef	Container<Unit>		UnitContainer;
typedef	Container<Player>	PlayerContainer;

using namespace sf;

class Toolbar
{
public:
	void	render(RenderWindow&);
	Toolbar(void);
	~Toolbar(void);
private:
	std::vector<UIItem*>mMenu;
	View				mMiniView;
	Color				mBackground;
	Vector2f			mSize,mPosition;
};

#endif