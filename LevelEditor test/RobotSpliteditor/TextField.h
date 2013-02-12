#ifndef INC_TEXTFIELD
#define INC_TEXTFIELD
#include<SFML/System/String.hpp>
#include<SFML/Graphics/Color.hpp>
using namespace sf;
class TextField
{
public:
	TextField(Color color=Color(0,0,0,255),String Base="",int DefaultPosition=0);
	~TextField(void);
	void	insertCharacter(const char&);
	void	setCurrentPosition(const int&);
	void	setColor(const Color&);
	void	deleteCharacter();
	String	getString()const;
	Color	getColor()const;
	int		getCurrentPosition()const;
private:
	String	mText;
	Color	mColor;
	int		mCurrentPosition;
};
#endif