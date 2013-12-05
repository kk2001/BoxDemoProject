//
//  MyContractListener.cpp
//  BoxDemoProjects
//
//  Created by cesc on 13-12-4.
//
//

#include "MyContractListener.h"



void MyContractListener::BeginContact(b2Contact *contact){
    
    
    
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    
    
    if ( fixtureA->GetBody()->GetType() != b2_staticBody ) {
        
    CCLOG("fixture A type :%i",  fixtureA->GetBody()->GetType());
    CCLOG("fixture B type :%i",  fixtureB->GetBody()->GetType());
    }
    
    
}


void MyContractListener::EndContact(b2Contact *contact){
    
    CCLOG( "end contract");
    
}