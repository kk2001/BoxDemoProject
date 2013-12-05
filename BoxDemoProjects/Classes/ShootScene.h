//
//  ShootScene.h
//  BoxDemoProjects
//
//  Created by cesc on 13-12-5.
//
//

#ifndef __BoxDemoProjects__ShootScene__
#define __BoxDemoProjects__ShootScene__

#include "cocos2d.h"
#include "Box2D.h"
#include "B2Utils.h"

USING_NS_CC;


class  ShootScene : public CCLayer {
    
    
public:
    
    ShootScene();
    ~ShootScene();
    virtual bool init();
    
    static CCScene* scene();
    
    CREATE_FUNC( ShootScene );
    
    void init_b2();
    
    void update( float dt );
    
    void init_shoot();
    // default implements are used to call script callback if exist
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    void onEnter();
    void onExit();
private:
    b2Body* shoot_base_body; // 底座body
    
    b2Body* banshouBody; // 扳手body
    
    b2Body* world_body;
    
    b2World* world;
    
    b2RevoluteJoint* revoleJoint;
    
    b2MouseJoint* mouseJoint;
};

#endif /* defined(__BoxDemoProjects__ShootScene__) */
