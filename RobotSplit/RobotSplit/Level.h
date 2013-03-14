#ifndef	INC_BANA
#define	INC_BANA
#include<vector>
#include<string>
#include <SFML/System/Vector2.hpp>

//Inuslated classes
class Unit;
class Background;
class Player;
class DialogueBox;
using namespace std;
typedef vector<Unit*> UnitVector;
typedef	vector<Background*>	BackgroundVector;
//Class is Working 24-01-2013
class	BackgroundWrap
{
public:
	BackgroundVector	getBackground	()const;
	string				getName			()const;
	int					getFrames		()const;
	int					getSpeed		()const;
	void				setBackground	(BackgroundVector);
	void				setName			(const string&);
	void				setFrames		(const int&);
	void				setSpeed		(const int&);
	void				operator=		(const BackgroundWrap&);
	void				deletePointer	();
private:
	BackgroundVector	mBackground;
	string				mName;
	int					mFrames,mSpeed;
};

//Class is Done	(01-27-2013)
class Level
{
public:
	//Uninitiated constructor					(Done)
	Level();
	//Initiated constructor						(Done)
	Level(string FileName);
	//Deconstructor								(Done)
	~Level(void);
	//Reads a Level from a XML-file				(Done)
	virtual	void	loadNewLevel(string FileName);
	//Returns the size of the level
	sf::Vector2f	getSize()const;
	//Returns the Level's objects				(Done)
	UnitVector		getObjects()const;
	//Returns the Level's name					(Done)
	string			getName()const;
	//Returns the Level's background			(Done)
	BackgroundVector		getBackground()const;
	//Returns the Player pointer				(Done)
	Player*			getPlayer()const;
	//Returns the Level's dialog boxes			(Done)
	vector<DialogueBox*> getDialogueBoxes()const;
	//Returns the Backgroundwrap				(Done)
	BackgroundWrap&	getBackgroundWrap();
	//Frees up all the pointers if using the
	//class to manage the different game parts	(Done)
	void			deletePointers	();
protected:
	//Operator for copying Levels				(Done)
	void			operator=(const Level&);
	//Replaces the Levels current object vector	(Done)
	void			setObjects(const UnitVector&);
	//Gives the level a new name				(Done)
	void			setName(const string&);
	//Sets the player pointer					(Done)
	void			setPlayer(Player*);
	//Sets the level's dialogue boxes
	void			addDialogueBox(DialogueBox*);
	//Sets the level's Background
	void			setBackground(vector<Background*>);
	void			setBackground(Background*);
	//Member Variables							(Done)
	string			mName;
	UnitVector		mObjects;
	BackgroundWrap	mBackground;
	Player*			mPlayer;
	vector<DialogueBox*> mDialogueBoxes;
	/*Defines the XmlLoader class as
	a friend allowing XmlLoader to use
	Level's private and protected functions*/
	friend class				LevelLoader;
};
#endif