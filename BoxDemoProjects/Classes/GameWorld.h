//
//  GameWorld.h
//  BoxDemoProjects
//
//  Created by cesc on 13-11-28.
//
//

#ifndef __BoxDemoProjects__GameWorld__
#define __BoxDemoProjects__GameWorld__

#include "cocos2d.h"
using namespace cocos2d;

#include "Box2D.h"

class GameWorld : public CCLayer {
    
    
public:
    
    GameWorld();
    ~GameWorld();
    virtual bool init();
    
    CREATE_FUNC( GameWorld );
    
    void init_b2();
    
    static CCScene* scene();
    
    
    void init_ui();
    
    void update( float dt ){
        
        world->Step(dt, 8,  1);
        logic();
        
    }
    
    void logic();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void onEnter();
    virtual void onExit();
    
    b2Body* getBullet(); // 获取子弹 
    
    
private:
    b2World* world;
    
    b2Body* worldGroudBody;
    
    b2Body* arm_body;
    
    b2Fixture* arm_fixture;
    
    b2RevoluteJoint* m_armJoint;
    
    b2MouseJoint* m_mouseJoint;
    
};

#endif /* defined(__BoxDemoProjects__GameWorld__) */
