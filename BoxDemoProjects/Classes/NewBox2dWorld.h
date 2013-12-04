//
//  NewBox2dWorld.h
//  BoxDemoProjects
//
//  Created by cesc on 13-12-4.
//
//

#ifndef __BoxDemoProjects__NewBox2dWorld__
#define __BoxDemoProjects__NewBox2dWorld__

#include "Box2d.h"
#include "MyContractListener.h"
#include "cocos2d.h"
USING_NS_CC;

class NewBox2dWorld : public CCLayer {
    
    
public:
    NewBox2dWorld();
    ~NewBox2dWorld();
    
    static CCScene* scene();
   
    virtual bool init();
    
    
    void init_b2World();
    
    void init_other();
    
    CREATE_FUNC( NewBox2dWorld );
    
    void addsprite( float dt );
    
    void update(float dt );
    
    CCSpriteBatchNode* spriteBacthNode;
    
private:
    b2World* m_world;
    
    MyContractListener contractListener;
    int count;
    
};

#endif /* defined(__BoxDemoProjects__NewBox2dWorld__) */
