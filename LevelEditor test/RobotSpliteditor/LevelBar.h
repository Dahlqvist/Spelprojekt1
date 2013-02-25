#ifndef	INC_LEVELBAR
#define	INC_LEVELBAR
#include	<SFML/Graphics.hpp>
#include	"Level.h"
#include	"UIItemContainer.h"

using namespace sf;

class LevelBar
{
public:
	LevelBar	(Level*,Vector2f Position=Vector2f(0,0),Vector2f Size=Vector2f(1280,50),Color BackColor=Color(150,150,150));
	~LevelBar	(void);
	void		render	(RenderWindow&);
	Vector2f	getSize	();
	bool		checkHit(const Vector2f&)const;
	void		setSelect	(const	bool&);
	bool		isSelected	()const;
	Vector2f	getPosition	();
	void		eventHandle	(const	Event&);
private:
	void			execute();
	bool			mChange;
	Level*			mLevel;
	UIItemContainer	mUIItems;
	Color			mBackground;
	Vector2f		mSize,mPosition;
	bool			mSelected;
};

#endif