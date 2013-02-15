#ifndef	INC_UITEXT
#define	INC_UITEXT

#include	<string>
#include	"UIItem.h"
#include	"TextField.h"
#include	"GameTimer.h"

using namespace sf;
class UIText:public	UIItem
{
public:
	UIText(std::string Name,std::string Default="",Color Back=Color(255,255,255,255),Color Text=Color(0,0,0,255),int Size=10);
	~UIText(void);
	void		draw(RenderWindow&,Vector2f	Position,Uint8 alpha=255);
	void		handleEvent(Event&);
	void		setDefault(std::string&);
	FloatRect	getHitBox(Vector2f	Position)const;
	std::string	getString();
private:
	GameTimer	mLineSwitch;
	int			mSize;
	bool		mLineDraw;
	Color		mBack,mTextColor;
	TextField	mEnter;
};
#endif