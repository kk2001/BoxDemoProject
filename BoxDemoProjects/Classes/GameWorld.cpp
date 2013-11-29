//
//  GameWorld.cpp
//  BoxDemoProjects
//
//  Created by cesc on 13-11-28.
//
//
#define FLOOR_HEIGHT 62.0f
#define PM_ITO  32
#include "GameWorld.h"

GameWorld::GameWorld(){


    m_mouseJoint = NULL;

}
GameWorld::~GameWorld(){}


void GameWorld::logic(){
    
    
    
    for (b2Body* b = world->GetBodyList(); b ; b = b->GetNext()) {
       
        if (b->GetUserData() ) {
           
            CCSprite* sp = (CCSprite*)b->GetUserData();
            
            sp->setPosition( ccp( b->GetPosition().x * PM_ITO, b->GetPosition().y * PM_ITO ));
            
            sp->setRotation( CC_RADIANS_TO_DEGREES( b->GetAngle()) * -1);
        }
        
        
    }
    
}
 CCScene* GameWorld::scene(){
    
     CCScene* s = CCScene::create();
     
     s->addChild( GameWorld::create() );
    
    return s;
}


bool GameWorld::init(){
    if ( !CCLayer::init() ) {
        return false;
    }
    
    init_ui();
    
    init_b2();
    
    setTouchEnabled( true );
    
    scheduleUpdate();
    
    return true;
}

void GameWorld::init_b2(){
    b2Vec2 gravity;
    gravity.Set(0, -10.0f);
    
    world = new b2World( gravity );
    
    world->SetAllowSleeping( true );
    world->SetContinuousPhysics( true );
    
    b2BodyDef groundDef;
    groundDef.position.Set(0, 0);
    
    worldGroudBody = world->CreateBody( &groundDef );
    
    CCSize size = CCDirector::sharedDirector()->getVisibleSize();
    
    b2EdgeShape shape;
    // bottom
    shape.Set( b2Vec2(0, FLOOR_HEIGHT / PM_ITO), b2Vec2( size.width * 2 / PM_ITO , FLOOR_HEIGHT / PM_ITO ));

    worldGroudBody->CreateFixture(&shape, 0);
    
    // top
    shape.Set(b2Vec2( 0, size.height / PM_ITO), b2Vec2( size.width * 2 / PM_ITO,size.height / PM_ITO ));
    worldGroudBody->CreateFixture(&shape, 0);
    
    // left
    shape.Set(b2Vec2(0,FLOOR_HEIGHT / PM_ITO), b2Vec2(0, size.height / PM_ITO ));
    worldGroudBody->CreateFixture(&shape, 0);
    
    // right
    shape.Set(b2Vec2( size.width * 2 /PM_ITO, size.height / PM_ITO ), b2Vec2( size.width * 2 /PM_ITO , FLOOR_HEIGHT /PM_ITO  ));
    worldGroudBody->CreateFixture(&shape, 0);
    
    CCSprite* arm= CCSprite::create("catapult_arm.png");
    this->addChild(arm, 1);
    
    b2BodyDef armBodyDef;
    armBodyDef.userData = arm;
    armBodyDef.linearDamping = 1;
    armBodyDef.angularVelocity = 1;
    armBodyDef.type = b2_dynamicBody;
    armBodyDef.position.Set( 230.0f/PM_ITO, (FLOOR_HEIGHT + 91.0f)/PM_ITO   );
    arm_body = world->CreateBody( &armBodyDef );
    
    b2PolygonShape box;
    box.SetAsBox(11.0f/PM_ITO, 91.0f/PM_ITO );
    
    b2FixtureDef fixdef;
    fixdef.shape = &box;
    fixdef.density = 0.3f;
    
    arm_fixture = arm_body->CreateFixture( &fixdef );
    
    
    
    b2RevoluteJointDef rJointDef;
    rJointDef.Initialize(worldGroudBody, arm_body, b2Vec2(233.0f/PM_ITO, FLOOR_HEIGHT/PM_ITO));
    rJointDef.enableLimit = true;
    rJointDef.enableMotor = true;
    rJointDef.maxMotorTorque =  700;
    rJointDef.motorSpeed =  -10;
    rJointDef.upperAngle = CC_DEGREES_TO_RADIANS( 75);
    rJointDef.lowerAngle = CC_DEGREES_TO_RADIANS( 9 );
    m_armJoint = (b2RevoluteJoint*)world->CreateJoint( &rJointDef );
    
    
    
}

void GameWorld::init_ui(){
    
    CCSprite* bg = CCSprite::create( "images/bg.png");
    bg->setAnchorPoint( CCPointZero );
    this->addChild( bg,-1 );
    
    CCSprite* bottom = CCSprite::create( "images/catapult_base_2.png");
    this->addChild( bottom ,1 );
    bottom->setAnchorPoint( CCPointZero );
    bottom->setPosition( ccp( 181.0f, FLOOR_HEIGHT ));
    
    CCSprite* bottom2 = CCSprite::create("catapult_base_1.png");   //投射器底部前面那块
    bottom2->setAnchorPoint(CCPointZero);
    bottom2->setPosition(CCPointMake(181.0f, FLOOR_HEIGHT));
    this->addChild(bottom2, 9);
    
    CCSprite* ice = CCSprite::create("fg.png");    //带冰的地面
    ice->setAnchorPoint(CCPointZero);
    this->addChild(ice, 10);
    
    
    CCSprite* songshu1 = CCSprite::create("squirrel_1.png");        //左边松鼠
    songshu1->setAnchorPoint(CCPointZero);
    songshu1->setPosition(CCPointMake(11.0, FLOOR_HEIGHT));
    this->addChild(songshu1, 0);
    
    
    CCSprite* songshu2 = CCSprite::create("squirrel_2.png");    //右边松鼠
    songshu2->setAnchorPoint(CCPointZero);
    songshu2->setPosition(CCPointMake(240.0, FLOOR_HEIGHT));
    this->addChild(songshu2, 9);
}


void GameWorld::onEnter(){
    
    CCLayer::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true );
    
}

void GameWorld::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    
    
    world->DestroyJoint(m_mouseJoint );
    m_mouseJoint = NULL;
    
}


void GameWorld::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    
    if ( m_mouseJoint == NULL ) {
        return ;
    }
    CCPoint p = pTouch->getLocation();
    
    b2Vec2 v  = b2Vec2( p.x /PM_ITO,p.y/ PM_ITO );
    
    m_mouseJoint->SetTarget( v );
    
    
    
}


bool GameWorld::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    
    if ( m_mouseJoint != NULL ) {
        return  false;
    }
    
    
    CCPoint p = pTouch->getLocation();
    
    b2Vec2 locationWorld  = b2Vec2( p.x / PM_ITO , p.y /PM_ITO );
    if ( locationWorld.x < arm_body->GetWorldCenter().x + 150/PM_ITO) {
        b2MouseJointDef mouseDef;
        mouseDef.bodyA = worldGroudBody;
        mouseDef.bodyB = arm_body;
        mouseDef.maxForce = 2000;
        mouseDef.target = locationWorld;
        
        m_mouseJoint = (b2MouseJoint*)world->CreateJoint(&mouseDef);
        
        return true;
        
    }
        
    
    return false;
}

void GameWorld::onExit(){
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate( this );
    CCLayer::onExit();
}