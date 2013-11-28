//
//  GameWorld.cpp
//  BoxDemoProjects
//
//  Created by cesc on 13-11-28.
//
//
#define FLOOR_HEIGHT 62
#define PM_ITO  32
#include "GameWorld.h"



GameWorld::GameWorld(){
    
    
    
}
GameWorld::~GameWorld(){
    
    
    CC_SAFE_DELETE( world );
    
}


bool GameWorld::init(){
    if ( !CCLayer::init() ) {
        return false;
    }
    
    init_ui();
    
    init_b2();
    
    
    scheduleUpdate();
    
    
    
    return true;
}

void GameWorld::init_ui(){
    
    CCSprite* bg = CCSprite::create( "images/bg.png");
    
    bg->setAnchorPoint( CCPointZero );
    
    this->addChild( bg );
    
}
void GameWorld::init_b2(){
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    b2Vec2 gravity;
    gravity.Set(0.0f,-10.0f);
    world = new b2World( gravity );
    
    bool doSleeping = true;
    world->SetAllowSleeping( doSleeping );
    world->SetContinuousPhysics( true );
    
    // define groud box
    b2BodyDef groundDef;
    groundDef.position.Set( 0, 0);
    
    worldGroudBody = world->CreateBody( &groundDef );
    
    
    b2EdgeShape edge;
    
    edge.Set( b2Vec2( 0 , FLOOR_HEIGHT / PM_ITO ) , b2Vec2( s.width * 2/ PM_ITO ,FLOOR_HEIGHT / PM_ITO ) );
    worldGroudBody->CreateFixture(&edge, 0 );
    
    
    edge.Set( b2Vec2( 0 , s.height / PM_ITO ) , b2Vec2( s.width * 2/PM_ITO ,s.height / PM_ITO ) );
    worldGroudBody->CreateFixture(&edge, 0 );
    
    
    edge.Set( b2Vec2( 0 , FLOOR_HEIGHT / PM_ITO ) , b2Vec2( 0 ,s.height / PM_ITO ) );
    worldGroudBody->CreateFixture(&edge, 0 );
    
    edge.Set( b2Vec2( s.width *2/ PM_ITO   , FLOOR_HEIGHT / PM_ITO ) , b2Vec2( s.width * 2/ PM_ITO ,FLOOR_HEIGHT / PM_ITO ) );
    worldGroudBody->CreateFixture(&edge, 0 );
}

void GameWorld::logic(){
    
    
}

CCScene* GameWorld::scene(){
    
    CCScene* sc = CCScene::create();
    
    sc->addChild(  GameWorld::create() );
    
    return sc;
}