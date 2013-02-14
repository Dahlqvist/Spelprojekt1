#ifndef	INC_EDITORBAR
#define	INC_EDITORBAR
#include<SFML/Graphics.hpp>
using namespace sf;
class EditorBar
{
public:
	EditorBar(Vector2f	Position=Vector2f(0,0),Vector2f	Size=Vector2f(200,200));
	~EditorBar(void);
	void	move(Vector2f Position);
	void	reSize(Vector2f Size);
private:
	Vector2f	mSize, mPosition;
	bool		Locked;
};

#endif