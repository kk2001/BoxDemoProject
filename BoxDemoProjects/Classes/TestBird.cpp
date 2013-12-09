//
//  TestBird.cpp
//  BoxDemoProjects
//
//  Created by cesc on 13-12-9.
//
//

#define PM_ITO  32

#include "TestBird.h"

TestBird::TestBird(){
    isPulling = false;
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    b2Vec2 gravity(0.0f,-10.0f);
    
    world = new b2World( gravity );
    world->SetAllowSleeping( true );
    world->SetContinuousPhysics( true );
    
    b2BodyDef worldDef;
    worldDef.position.SetZero();
    
    worldBody = world->CreateBody( &worldDef );
    
    b2EdgeShape shape;
    
    shape.Set( b2Vec2(0, 0) , b2Vec2( size.width / PM_ITO,  0 ) );
    worldBody->CreateFixture( &shape, 0 );
    
    shape.Set( b2Vec2(0, size.height / PM_ITO) , b2Vec2( size.width / PM_ITO,  size.height / PM_ITO ) );
    worldBody->CreateFixture( &shape, 0 );
    
    shape.Set( b2Vec2(0 , size.height / PM_ITO) , b2Vec2( 0,  0 ) );
    worldBody->CreateFixture( &shape, 0 );
    
    shape.Set( b2Vec2( size.width / PM_ITO , 0 ) , b2Vec2(  size.width / PM_ITO,  size.height /PM_ITO ) );
    worldBody->CreateFixture( &shape, 0 );
}

TestBird::~TestBird(){
    
    
}


bool TestBird::init(){
    
    if ( !CCLayer::init() ) {
        return false;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    baseSprite = CCSprite::create( "Icon-72.png");
    ballSprite = CCSprite::create( "Icon.png");
    
    baseSprite->setPosition( ccp( size.width / 2,  200));
    this->addChild(  baseSprite  , 1 );
    
    ballSprite->setPosition( baseSprite->getPosition());
    this->addChild(  ballSprite  , 2 );

    
    b2BodyDef ballBBodyDef;
    ballBBodyDef.position.Set(ballSprite->getPositionX() / PM_ITO, ballSprite->getPositionY() / PM_ITO);
    ballBBodyDef.userData = ballSprite;
    ballBBodyDef.type = b2_dynamicBody;
    
    ballBBody = world->CreateBody( &ballBBodyDef );
    
    b2FixtureDef ballBFixtureDef;
    ballBFixtureDef.density = 1.0f;
    b2CircleShape circleShapeB;
    circleShapeB.m_radius = 10.0f/PM_ITO;
    ballBFixtureDef.shape = &circleShapeB;
    ballBBody->CreateFixture( &ballBFixtureDef);
    
    // 将B焊接到A上
    b2WeldJointDef weldJointDef;
    weldJointDef.Initialize(worldBody, ballBBody, ballBBody->GetWorldCenter());
    weldJointDef.collideConnected = false;
    weldJoint = (b2WeldJoint*)world->CreateJoint( &weldJointDef );
        
    
    scheduleUpdate();
    
    setTouchEnabled( true );
    return true;
}


CCScene* TestBird::scene(){
    
    CCScene* s = CCScene::create();
    
    s->addChild( TestBird::create() );
    
    return s;
}

void TestBird::update(float dt){
    
    world->Step(dt, 8, 1);
    
    b2Body* b  = world->GetBodyList();
    
    while ( b ) {
        
        if ( b->GetUserData()) {
            CCSprite* sp = static_cast<CCSprite*>(b->GetUserData());
            
            sp->setPosition( ccp( b->GetPosition().x * PM_ITO, b->GetPosition().y * PM_ITO));
            sp->setRotation( -1 * CC_RADIANS_TO_DEGREES( b->GetAngle()));
            
        }
        
        b = b->GetNext();
    }
    
    
}

void TestBird::onEnter(){
    CCLayer::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate( this , 0,  true );
    
    
    
}


void TestBird::onExit(){
    
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate( this );
    CCLayer::onExit();
    
    
}


bool TestBird::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    
    CCLOG("began");
    CCPoint touchPoint = pTouch->getLocation();
    
           if ( weldJoint != NULL) {
            world->DestroyJoint( weldJoint );
            weldJoint = NULL;
           }
    
    
        b2MouseJointDef md;
        md.bodyA = worldBody;
        md.bodyB = ballBBody;
        md.target = b2Vec2( touchPoint.x / PM_ITO,  touchPoint.y / PM_ITO );
        md.collideConnected = true;
        md.maxForce = 1000.0f * ballBBody->GetMass();
        
        mouseJoint = (b2MouseJoint*)world->CreateJoint(&md);
        
        ballBBody->SetFixedRotation( true );
        CCLOG( "create mouse joint ");
        
        
        
        isPulling = true;
        
    
    
    return true;
}


void TestBird::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    
    
    CCPoint touchPoint = pTouch->getLocation();
    
    if ( isPulling ) {
       
        //  距离大于80这个规定的长度之后 创建关节
        if ( ccpDistance( baseSprite->getPosition() , touchPoint ) > 80.0f) {
          
            if ( !disJoint  ) {
                
                b2DistanceJointDef jd;
                jd.Initialize(worldBody, ballBBody, b2Vec2( baseSprite->getPositionX() /PM_ITO, baseSprite->getPositionY() / PM_ITO ), ballBBody->GetWorldCenter() );
                
                jd.collideConnected = true;
                
                
                disJoint = (b2DistanceJoint*)world->CreateJoint( &jd );
                disJoint->SetLength( 80.0f/PM_ITO);
                
                
            }
    
            
        }else{
            
            //  距离小于80这个规定的长度之后 销毁关节
            if ( disJoint) {
               
                world->DestroyJoint( disJoint);
                disJoint = NULL;
            }
            
            
        }
        
        mouseJoint->SetTarget( b2Vec2( touchPoint.x /PM_ITO, touchPoint.y / PM_ITO ));
        
        
        
    } // end if   isPulling

    
    
}


void TestBird::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    
    isPulling = false;
    
    if ( mouseJoint) {
        world->DestroyJoint( mouseJoint );
        mouseJoint = NULL;
    }
    
    if ( disJoint ) {
        world->DestroyJoint( disJoint );
        disJoint = NULL;
    }
    
    ballBBody->SetFixedRotation( false );
    
    
    // 将精灵钉到base上
    /**
    b2WeldJointDef weldJointDef;
    weldJointDef.Initialize(worldBody, ballBBody, ballBBody->GetWorldCenter());
    weldJointDef.collideConnected = false;
    weldJoint = (b2WeldJoint*)world->CreateJoint( &weldJointDef );
     **/
    
    // 注意焊接关节设定之后就不在能移动位置了 所以如果想在焊接之前移动那么就只能在定义焊接关节之前设定位置
    ballBBody->SetTransform( b2Vec2( baseSprite->getPositionX() / PM_ITO , baseSprite->getPositionY() /PM_ITO ) , 0 );
    
    b2WeldJointDef wd;
    wd.Initialize( worldBody, ballBBody, ballBBody->GetWorldCenter());
    wd.collideConnected =false;
    weldJoint = (b2WeldJoint*)world->CreateJoint( &wd);

    CCLOG("ended");
    
}


