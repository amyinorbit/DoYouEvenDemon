//
//  main.m
//  DoYouEvenDemon
//
//  Created by Amy Parent on 29/01/2016.
//  Copyright © 2016 cesarparent. All rights reserved.
//

#include <Meteor/Meteor.h>
#include "SplashScreen.hpp"
#include <ctime>
using namespace Meteor;

int main(int argc, char** argv) {
    
    srand((unsigned int)time(nullptr));
    return GameMain<SplashScreen>();
}
