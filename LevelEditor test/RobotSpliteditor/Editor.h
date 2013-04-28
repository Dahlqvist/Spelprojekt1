#ifndef	INC_EDITOR
#define	INC_EDITOR
#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "LevelConstructor.h"
#include "Unit.h"
#include "Player.h"
#include "TextField.h"
#include "Container.h"
#include "Toolbar.h"
#include "LevelBar.h"
#include "GameTimer.h"
#include <SFML/Window/WindowHandle.hpp>

typedef	Container<Unit>		UnitContainer;
typedef	Container<Player>	PlayerContainer;

using namespace sf;

class Editor
{
public:
	Editor(void);
	Editor(std::string Level);
	~Editor(void);
	void				run();
	void				renderLevel(View&);
	void				deleteSelected();
	RenderWindow&		getWindow();
	void				setUnit(UnitContainer&);
	void				setPlayer(PlayerContainer&);
	bool				collide(UnitContainer&);
	bool				collide(PlayerContainer&);
private:
	GameTimer			mMouseHoldTimer;
	RenderWindow		mWindow;
	LevelConstructor	mLevel;
	UnitContainer		mSelectedUnit;
	PlayerContainer		mSelectedPlayer;
	View				mCurrView;
	Toolbar				mTools;
	LevelBar			mLevelTool;
	bool				mOpen;
	void				eventHandler(const Event&);
	friend	class		Toolbar;
};

#endif