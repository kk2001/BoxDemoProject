//
//  TestBird.h
//  BoxDemoProjects
//
//  Created by cesc on 13-12-9.
//
//

#ifndef __BoxDemoProjects__TestBird__
#define __BoxDemoProjects__TestBird__

#include "cocos2d.h"
#include "Box2D.h"
USING_NS_CC;


class TestBird : public CCLayer {
    
    
public:
    
    TestBird();
    ~TestBird();
   
    bool init();
    virtual void onEnter();
    virtual void onExit();
    
    // default implements are used to call script callback if exist
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    static CCScene* scene();
    
    void update( float dt );
    
    CREATE_FUNC( TestBird );
    
private:
    
    CCSprite* ballSprite;
    CCSprite* baseSprite;
    b2Body* ballBBody;
    
    b2MouseJoint* mouseJoint;
    b2World* world;
    b2Body* worldBody;
    
    b2WeldJoint*  weldJoint;
    
    b2DistanceJoint* disJoint; // 距离关节
    
    bool isPulling;
};

#endif /* defined(__BoxDemoProjects__TestBird__) */
