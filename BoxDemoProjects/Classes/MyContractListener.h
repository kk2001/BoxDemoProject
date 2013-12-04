//
//  MyContractListener.h
//  BoxDemoProjects
//
//  Created by cesc on 13-12-4.
//
//

#ifndef __BoxDemoProjects__MyContractListener__
#define __BoxDemoProjects__MyContractListener__

#include "Box2D.h"
#include "cocos2d.h"
USING_NS_CC;


class MyContractListener : public b2ContactListener {
    
    
public:
    virtual void BeginContact(b2Contact* contact);
    
    /// Called when two fixtures cease to touch.
    virtual void EndContact(b2Contact* contact);
};

#endif /* defined(__BoxDemoProjects__MyContractListener__) */
