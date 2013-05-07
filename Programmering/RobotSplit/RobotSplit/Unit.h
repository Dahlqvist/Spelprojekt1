#ifndef INC_UNIT
#define INC_UNIT

#include "GameObject.h"
#include "TextureManager.h"
#include "Animation.h"

#include <SFML/Graphics/RenderWindow.hpp>

class Unit: public GameObject
{
public:
	Unit(sf::Vector2f position, std::string id, std::string spriteName, bool solid=true, bool behind=false, float speed=0, int distance=-1, int direction=RIGHT);
	Unit(sf::Vector2f position, std::string id, Animation* animation, bool solid=true, bool behind=false, float speed=0, int distance=-1, int direction=RIGHT);
	Unit(sf::Vector2f position, sf::Vector2f size, sf::Vector2f offset, std::string id, std::string spriteName, bool solid=true, bool behind=false, float speed=0, int distance=-1, int direction=RIGHT);
	Unit(sf::Vector2f position, sf::Vector2f size, sf::Vector2f offset, std::string id, Animation* animation, bool solid=true, bool behind=false, float speed=0, int distance=-1, int direction=RIGHT);
	virtual ~Unit();

	virtual sf::Vector2f getPosition(){return mPosition;};
	virtual void setPosition(sf::Vector2f position)
	{
		mPosition=position;
		mSprite.setPosition(mPosition);
	};

	virtual sf::Sprite getSprite(){return mSprite;};
	virtual void setSprite(sf::Sprite sprite){mSprite=sprite;};

	virtual void setCurrentFrame(int anim){mAnimation->setCurrentFrame(anim);};

	virtual sf::Vector2f getSize(){return mSize;};

	virtual sf::Vector2f getOffset(){return mOffset;};

	virtual std::string getId(){return mId;};
	virtual void setId(std::string id){mId=id;};

	virtual bool isHit(){return mHit;};
	virtual void setHit(bool hit){mHit=hit;};

	virtual bool wasHit(){return mWasHit;};
	virtual void setWasHit(bool hit){mWasHit=hit;};

	virtual bool isHitThisFrame(){return mHitThisFrame;};
	virtual void setHitThisFrame(bool hit){mHitThisFrame=hit;};

	virtual	void setSolid(bool	Solid){mSolid=Solid;}
	virtual bool isSolid(){return mSolid;};

	virtual bool isBehind(){return mBehind;};

	virtual void rotate(float r){mSprite.rotate(r);}

	virtual void update();
	virtual void draw();
	virtual void hit(){};
	virtual void hitOnce(){};
	virtual void activate(){};
	virtual void deactivate(){};
	virtual void reset(){};
	virtual void setReset(){};
	virtual	void setBehind(bool Behind){mBehind=Behind;}

	enum directions
	{
		MIN_VALUE_DIR,
		UP,
		DOWN,
		RIGHT,
		LEFT,
		MAX_VALUE_DIR
	};

protected:
	sf::Vector2f mSize, mOffset;
	
	sf::Sprite mSprite;
	Animation* mAnimation;
	bool mSolid, mHit, mHitThisFrame, mWasHit, mBehind;

	float mSpeed; 
	int mDistance;
	sf::Vector2f mStartPosition;
	int mDirection;

private:
	void changeDirection(int distance);
};

#endif