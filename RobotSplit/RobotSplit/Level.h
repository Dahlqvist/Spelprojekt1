#ifndef	INC_BANA
#define	INC_BANA
#include<vector>
#include<string>

//Inuslated classes
class GameObject;
class Background;
class Player;
using namespace std;
typedef vector<GameObject*> ObjectVector;

//Class is Working 24-01-2013
class	BackgroundWrap
{
public:
	Background*	getBackground	()const;
	string		getName			()const;
	int			getFrames		()const;
	int			getSpeed		()const;
	void		setBackground	(Background*);
	void		setName			(const string&);
	void		setFrames		(const int&);
	void		setSpeed		(const int&);
	void		operator=		(const BackgroundWrap&);
	void		deletePointer	();
private:
	Background*	mBackground;
	string		mName;
	int			mFrames,mSpeed;
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
	void			loadNewLevel(string FileName);
	//Returns the Level's objects				(Done)
	ObjectVector	getObjects()const;
	//Returns the Level's name					(Done)
	string			getName()const;
	//Returns the Level's background			(Done)
	Background*		getBackground()const;
	//Returns the Player pointer				(Done)
	Player*			getPlayer()const;
	//Returns the Backgroundwrap				(Done)
	BackgroundWrap&	getBackgroundWrap();
	//Frees up all the pointers if using the
	//class to manage the different game parts	(Done)
	void			deletePointers	();
protected:
	//Operator for copying Levels				(Done)
	void			operator=(const Level&);
	//Replaces the Levels current object vector	(Done)
	void			setObjects(const ObjectVector&);
	//Gives the level a new name				(Done)
	void			setName(const string&);
	//Sets the player pointer					(Done)
	void			setPlayer(Player*);
	//Sets the level's Background
	void			setBackground(Background*);
private:
	//Member Variables							(Done)
	string			mName;
	ObjectVector	mObjects;
	BackgroundWrap	mBackground;
	Player*			mPlayer;
	/*Defines the XmlLoader class as
	a friend allowing XmlLoader to use
	Level's private and protected functions*/
	friend class				LevelLoader;
};
#endif