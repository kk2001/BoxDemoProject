//
//  B2Utils.h
//  BoxDemoProjects
//
//  Created by cesc on 13-12-5.
//
//

#ifndef __BoxDemoProjects__B2Utils__
#define __BoxDemoProjects__B2Utils__

#include "Box2D.h"
#include "cocos2d.h"
USING_NS_CC;

class B2Utils {
    
    
public:
    static b2World*  createWorldWithEdge();
    static b2Vec2  convertToB2Point( CCPoint point  );
    static CCPoint convertToCCPoint( b2Vec2 world_point );

};

#endif /* defined(__BoxDemoProjects__B2Utils__) */
