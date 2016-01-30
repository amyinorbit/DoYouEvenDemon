//
//  beatController.hpp
//  DoYouEvenDemon
//
//  Created by Cesar Parent on 30/01/2016.
//  Copyright © 2016 PixelSpark. All rights reserved.
//

#ifndef beatController_hpp
#define beatController_hpp


#include <Meteor/Meteor.h>
using namespace Meteor;

extern const int kBeatNotification;
extern const int kOffBeatNotification;
extern const int kBeatCanceledNotification;
extern const int kSongFinishedNotification;


class BeatController final {
public:
    
    static void setBPM(double BPM);
    
    static void setMusicFile(const std::string& file, int loops = 1);
    
    static void update(double delta);
    
    static void validateTiming();
    
private:
    
    static const Uint8 precision = 2;
    
    BeatController() = delete;
    BeatController(const BeatController&) = delete;
    
    // beat tracking variables
    static double  _beatTime;
    static Uint8   _beatProgression;
    static double  _prog;
    static double  _beatWindow;
};

#endif /* beatController_hpp */
