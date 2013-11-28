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
private:
    b2World* world;
    
    b2Body* worldGroudBody;
    
    b2Body* arm_body;
    
    b2Fixture* arm_fixture;
    
    b2RevoluteJoint* m_armJoint;
    
    
};

#endif /* defined(__BoxDemoProjects__GameWorld__) */
