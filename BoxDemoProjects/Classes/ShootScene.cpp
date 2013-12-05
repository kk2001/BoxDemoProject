//
//  ShootScene.cpp
//  BoxDemoProjects
//
//  Created by cesc on 13-12-5.
//
//

#include "ShootScene.h"

#define PM_ITO  32

ShootScene::ShootScene(){
    
    mouseJoint = NULL;
    /**
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    b2Vec2 gravity( 0.0f, -10.0f);
    
    world = new b2World( gravity );
    
    world->SetAllowSleeping( true );
    world->SetContinuousPhysics( true );

    b2BodyDef worlddef;
    worlddef.position.SetZero();
    
    b2Body* world_body = world->CreateBody( &worlddef);
    
    b2EdgeShape edge;
    edge.Set( b2Vec2(0, 0 ), b2Vec2( s.width / 2 / PM_ITO , 0  ));
    
    world_body->CreateFixture(&edge, 0 );
    
    edge.Set( b2Vec2(0, s.height / PM_ITO   ), b2Vec2( s.width / 2 / PM_ITO , s.height / PM_ITO  ));
   
    world_body->CreateFixture(&edge, 0 );
    
    edge.Set( b2Vec2(0, s.height / PM_ITO ), b2Vec2( 0 , 0  ));
    
    world_body->CreateFixture(&edge, 0 );
    
    edge.Set( b2Vec2( s.width / PM_ITO , 0 ), b2Vec2( s.width / 2 / PM_ITO , s.height / PM_ITO  ));
    
    world_body->CreateFixture(&edge, 0 );
     **/
    
    world = NULL;
    revoleJoint = NULL;
}
ShootScene::~ShootScene(){
    
    
    world->DestroyJoint( revoleJoint );
    
    world->DestroyBody( banshouBody );
    world->DestroyBody( shoot_base_body );
    
    delete world;
    world = NULL;
    
    
}

CCScene* ShootScene::scene(){
    
    CCScene* s = CCScene::create();
    
    s->addChild( ShootScene::create() );
    
    return s;
}



bool ShootScene::init(){
    
    if ( !CCLayer::init() ) {
        return false;
    }
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* bg = CCSprite::create( "HelloWorld.png");
    
    this->addChild( bg,  -1);
    
    bg->setPosition( ccp( s.width / 2, s.height / 2 ));

    
    init_b2();
    
    init_shoot();
    
    scheduleUpdate();
    
    
    setTouchEnabled( true );
    
    return true;
}


void ShootScene::init_b2(){
    
    
    world = B2Utils::createWorldWithEdge( );
    
    
}

void ShootScene::init_shoot(){

    CCSize winsize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* shoot_base = CCSprite::create( "images/catapult_base_2.png");
    this->addChild(  shoot_base, 1 );
    
    shoot_base->setPosition( ccp( winsize.width / 2 ,  shoot_base->getContentSize().height / 2  ));
    
    b2BodyDef shoot_base_def;
    
    shoot_base_def.position.Set( shoot_base->getPositionX() / PM_ITO, shoot_base->getPositionY() / PM_ITO );
    shoot_base_def.type = b2_staticBody;
    shoot_base_def.userData =  shoot_base;
    
    CCAssert ( world, "world is null");
    
   
   shoot_base_body= world->CreateBody( &shoot_base_def );
    
    b2FixtureDef shootbody_fixturedef;
    b2PolygonShape shape;
    shape.SetAsBox(  shoot_base->getContentSize().width / 2 /PM_ITO , shoot_base->getContentSize().height / 2 /PM_ITO  );
    shootbody_fixturedef.shape = &shape;
    shootbody_fixturedef.density = 100.0f;
    shootbody_fixturedef.restitution = 0.1;

    shoot_base_body->CreateFixture( &shootbody_fixturedef );
    
    // -------------------  创建扳手 ------------------
    
    CCSprite* banshou = CCSprite::create( "images/catapult_arm.png");
    this->addChild( banshou, 2);
    //banshou->setAnchorPoint( ccp(0.5, 0));
    
    banshou->setPosition( ccp( shoot_base->getPositionX() , shoot_base->boundingBox().getMaxY() +banshou->getContentSize().height / 2 ) );
    
    b2BodyDef shoot_def;
    shoot_def.type = b2_dynamicBody;
    shoot_def.position.Set( banshou->getPositionX() / PM_ITO , banshou->getPositionY() / PM_ITO );
    
    b2FixtureDef shootFixtureDef;
    b2PolygonShape s_shape;
    s_shape.SetAsBox( banshou->getContentSize().width / 2 /PM_ITO, banshou->getContentSize().height / 2 /PM_ITO );
    shootFixtureDef.density = 10.0f;
    shootFixtureDef.shape = &s_shape;
    
    
    banshouBody = world->CreateBody( &shoot_def );
    banshouBody->CreateFixture( &shootFixtureDef );
    
    
    b2RevoluteJointDef _reDefine;
    _reDefine.bodyA = shoot_base_body;
    _reDefine.bodyB = banshouBody;
    _reDefine.localAnchorA.Set(0.5, 1);
    _reDefine.localAnchorB.Set(0.5, 0);
    
    _reDefine.enableLimit = true;
    _reDefine.enableMotor = true;
    _reDefine.lowerAngle = CC_DEGREES_TO_RADIANS( 30 );
    _reDefine.upperAngle = CC_DEGREES_TO_RADIANS( 75 );
    _reDefine.motorSpeed = -10;
    _reDefine.maxMotorTorque = 2000;
    /**
    _reDefine.Initialize(shoot_base_body, banshouBody,B2Utils::convertToB2Point( banshou->getPosition() ) );
    _reDefine.enableMotor = true;
    _reDefine.enableLimit = true;
    _reDefine.lowerAngle = CC_RADIANS_TO_DEGREES( 9);
    _reDefine.upperAngle = CC_RADIANS_TO_DEGREES( 75);
    _reDefine.maxMotorTorque = 1000;
    _reDefine.motorSpeed = -20;
     **/
   
    
    revoleJoint = (b2RevoluteJoint*)world->CreateJoint( &_reDefine);
    
    
    
}

void ShootScene::update(float dt){
    
    world->Step(dt, 8, 1 );
    
    
    b2Body* b = world->GetBodyList();
    
    while ( b ) {
        
        if ( b->GetUserData() ) {
           
            CCSprite* sp =  (CCSprite*)b->GetUserData();
            
            sp->setPosition( B2Utils::convertToCCPoint( b->GetPosition()));
            sp->setRotation( -1 * CC_RADIANS_TO_DEGREES( b->GetAngle() ));
        }
       
        
        b = b->GetNext();
    }
    
    
}

void ShootScene::onEnter(){
    CCLayer::onEnter();
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate( this , 0,  true );
}


void ShootScene::onExit(){
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate( this );
    
    CCLayer::onExit();
    
}

bool ShootScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    
    CCLog("click");
    
    if ( mouseJoint != NULL) {
        return false;
    }
    
    
    b2Vec2 worldPoint = B2Utils::convertToB2Point( pTouch->getLocation());

    
    if ( worldPoint.x <  banshouBody->GetWorldCenter().x + 150 / PM_ITO ) {
        
        CCLog("小于");
        b2MouseJointDef mouseDef;
        mouseDef.bodyA  = shoot_base_body;
        mouseDef.bodyB = banshouBody;
        mouseDef.target = worldPoint;
        mouseDef.maxForce =  2000;
        
        mouseJoint = ( b2MouseJoint*)world->CreateJoint( &mouseDef );
        
        
    }
    
    
    
    return true;
    
    
}

void ShootScene::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    
    if ( mouseJoint == NULL) {
    
        return ;
    }
    
    CCLog("移动");
    
    mouseJoint->SetTarget( B2Utils::convertToB2Point( pTouch->getLocation()));
    
}

void ShootScene::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    
    
    if ( mouseJoint != NULL ) {
        CCLog("销毁");    
        
        world->DestroyJoint( mouseJoint );
        mouseJoint = NULL;
    }
  
    
    
}