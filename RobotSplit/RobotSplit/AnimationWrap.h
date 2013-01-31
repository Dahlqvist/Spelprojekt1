#ifndef INC_ANIMATIONWRAP
#define INC_ANIMATIONWRAP
#include"Animation.h"
class AnimationWrap:public Animation
{
public:
	AnimationWrap(Animation&);
	~AnimationWrap(void);
};
#endif