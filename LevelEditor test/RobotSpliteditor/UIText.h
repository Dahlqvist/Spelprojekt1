#ifndef	INC_UITEXT
#define	INC_UITEXT

#include	<string>
#include	"UIItem.h"
#include	"TextField.h"

using namespace sf;
class UIText:public	UIItem
{
public:
	UIText(std::string Name,Vector2f Position,std::string Default="",Color Back=Color(255,255,255,255),Color Text=Color(0,0,0,255),int Size=10);
	~UIText(void);
	void	draw(RenderWindow&,Uint8 alpha=255);
	void	handleEvent(Event&);
private:
	int			mSize;
	Vector2f	mPosition;
	Color		mBack,mTextColor;
	TextField	mEnter;
	std::string	mName;
};
#endif