//
//  NewBox2dWorld.cpp
//  BoxDemoProjects
//
//  Created by cesc on 13-12-4.
//
//

#include "NewBox2dWorld.h"

#define PM_ITO 32

NewBox2dWorld::NewBox2dWorld(){
    
    spriteBacthNode = CCSpriteBatchNode::create( "Icon.png");
    CC_SAFE_RETAIN( spriteBacthNode );
    
    count = 0;
    
}
NewBox2dWorld::~NewBox2dWorld(){
    
    CC_SAFE_RELEASE_NULL( spriteBacthNode );
    delete m_world;
    
}
CCScene* NewBox2dWorld::scene(){
    
    CCScene* s =  CCScene::create();
    
    s->addChild( NewBox2dWorld::create() );
    
    return s;
}


void NewBox2dWorld::init_b2World(){
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    b2Vec2 gravity(0.0f, -10.0f);
    m_world = new b2World(  gravity );
    m_world->SetAllowSleeping( true );
    m_world->SetContinuousPhysics( true );
    m_world->SetContactListener( &contractListener );
    
    b2BodyDef groundbodydef;
    groundbodydef.position.SetZero();
    b2Body* groundbody = m_world->CreateBody( &groundbodydef );
    
    b2EdgeShape edge;
    edge.Set(b2Vec2( 0,0), b2Vec2( size.width/PM_ITO , 0));
    
    groundbody->CreateFixture(&edge, 0 );
    
    edge.Set(b2Vec2( 0,size.height/PM_ITO ), b2Vec2( size.width/PM_ITO , size.height/PM_ITO));
    groundbody->CreateFixture(&edge, 0 );
    
    edge.Set(b2Vec2(0,size.height/PM_ITO), b2Vec2( 0,0));
    groundbody->CreateFixture(&edge, 0 );
    
    edge.Set(b2Vec2( size.width/PM_ITO,size.height/PM_ITO ), b2Vec2( 0,size.height/PM_ITO ));
    groundbody->CreateFixture(&edge, 0 );
}

bool NewBox2dWorld::init(){
    
    if ( !CCLayer::init() ) {
        return false;
    }
    
    init_b2World();
    
    this->addChild( spriteBacthNode ,1 );
    
    this->schedule( schedule_selector(NewBox2dWorld::addsprite), 1.0f);
    
    scheduleUpdate();
    return true;
}

void NewBox2dWorld::addsprite(float dt){
    
    count++;
    
    if ( count > 5) {
        unschedule( schedule_selector( NewBox2dWorld::addsprite));
        return;
    }
    
    init_other();
}

void NewBox2dWorld::init_other(){
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* sp = CCSprite::create( "Icon.png");
    
    spriteBacthNode->addChild( sp );
    
    b2BodyDef spBodyDef;
    spBodyDef.position.Set( size.width /2 /PM_ITO, size.height * 0.7 /PM_ITO );
    spBodyDef.type = b2_dynamicBody;
    spBodyDef.userData = sp;
    
    b2Body* spBody = m_world->CreateBody( &spBodyDef );
    
    
    b2PolygonShape shape;
    shape.SetAsBox( sp->getContentSize().width / 2 /PM_ITO, sp->getContentSize().height / 2 / PM_ITO );
    b2FixtureDef fixtureDef;
    
    fixtureDef.density = 10.0f;
    fixtureDef.shape = &shape;
    fixtureDef.restitution = 0.3f; // 反弹力
    fixtureDef.friction = 0.3f; // 摩擦力
    
    spBody->CreateFixture( &fixtureDef );
    
    
}


void NewBox2dWorld::update(float dt){
    
    m_world->Step(dt, 8, 1 );
    
    
    for (b2Body* b = m_world->GetBodyList(); b; b = b->GetNext()) {
       
        CCSprite* sp = static_cast<CCSprite*>(b->GetUserData() );
        if ( sp) {
            
            sp->setPosition( ccp(b->GetPosition().x * PM_ITO, b->GetPosition().y * PM_ITO ));
            sp->setRotation( -1 * CC_RADIANS_TO_DEGREES( b->GetAngle() ));
            
            
        }
        
            
        
        
            
        }
        
        
    
    
}