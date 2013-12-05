//
//  B2Utils.cpp
//  BoxDemoProjects
//
//  Created by cesc on 13-12-5.
//
//

#include "B2Utils.h"

#define PIM_ITO  32
CCPoint B2Utils::convertToCCPoint(b2Vec2 world_point){
    
    
    return  ccp( world_point.x * PIM_ITO , world_point.y * PIM_ITO  );
    
}

b2Vec2 B2Utils::convertToB2Point(cocos2d::CCPoint point){
    
    return b2Vec2(point.x / PIM_ITO , point.y / PIM_ITO );
}

b2World* B2Utils::createWorldWithEdge(){
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    b2Vec2 gravity( 0.0f, -10.0f);
    
   b2World* world = new b2World( gravity );
    
    world->SetAllowSleeping( true );
    world->SetContinuousPhysics( true );
    
    b2BodyDef worlddef;
    worlddef.position.SetZero();
    
    b2Body* world_body = world->CreateBody( &worlddef);

    
    b2EdgeShape edge;
    edge.Set( b2Vec2(0, 0 ), b2Vec2( s.width / 2 / PIM_ITO , 0  ));
    
    world_body->CreateFixture(&edge, 0 );
    
    edge.Set( b2Vec2(0, s.height / PIM_ITO   ), b2Vec2( s.width / 2 / PIM_ITO , s.height / PIM_ITO  ));
    
    world_body->CreateFixture(&edge, 0 );
    
    edge.Set( b2Vec2(0, s.height / PIM_ITO ), b2Vec2( 0 , 0  ));
    
    world_body->CreateFixture(&edge, 0 );
    
    edge.Set( b2Vec2( s.width / PIM_ITO , 0 ), b2Vec2( s.width / 2 / PIM_ITO , s.height / PIM_ITO  ));
    
    world_body->CreateFixture(&edge, 0 );
    
    
    
    return world;
}