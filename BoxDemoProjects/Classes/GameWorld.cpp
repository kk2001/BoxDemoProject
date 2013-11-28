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
    CC_SAFE_DELETE( arm_fixture );
    
}


bool GameWorld::init(){
    if ( !CCLayer::init() ) {
        return false;
    }
    
    
    init_b2();
    
    init_ui();
    
    scheduleUpdate();
    
    
    
    return true;
}

void GameWorld::init_ui(){
    
    CCSprite* bg = CCSprite::create( "images/bg.png");
    
    bg->setAnchorPoint( CCPointZero );
    
    this->addChild( bg );
    
    
    CCSprite* arm = CCSprite::create( "images/catapult_arm.png");
    this->addChild( arm ,1 );
    
    arm->setPosition( ccp( 230,FLOOR_HEIGHT + 10 ));
    b2BodyDef armBodyDef;
    armBodyDef.type = b2_dynamicBody;
    armBodyDef.position.Set(230/PM_ITO, ( FLOOR_HEIGHT  + 10) /PM_ITO );
    armBodyDef.linearDamping = 1;
    armBodyDef.angularDamping = 1;
    armBodyDef.userData = arm;
    
    arm_body = world->CreateBody( &armBodyDef);
    
    b2PolygonShape armShape;
    armShape.SetAsBox( arm->getContentSize().width /2 /PM_ITO, arm->getContentSize().height / 2 / PM_ITO );
    
    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.3f;
    fixtureDef.shape = &armShape;
    
    arm_fixture = arm_body->CreateFixture( &fixtureDef);
    
    
    
    
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
    
    for (b2Body* b = world->GetBodyList(); b; b = b->GetNext()) {
        
        if ( b->GetUserData() ) {
            CCSprite* sp = (CCSprite*)b->GetUserData();
            sp->setPosition( ccp( b->GetPosition().x * PM_ITO, b->GetPosition().y * PM_ITO  ));
            
            sp->setRotation( -1 *CC_RADIANS_TO_DEGREES(b->GetAngle()  ));
        }
    }
    
    
}

CCScene* GameWorld::scene(){
    
    CCScene* sc = CCScene::create();
    
    sc->addChild(  GameWorld::create() );
    
    return sc;
}