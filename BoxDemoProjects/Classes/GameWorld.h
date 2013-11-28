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


class GameWorld : public CCLayer {
    
    
public:
    
    virtual bool init();
    
    CREATE_FUNC( GameWorld );
    
    
    static CCScene* scene();
    
};

#endif /* defined(__BoxDemoProjects__GameWorld__) */
