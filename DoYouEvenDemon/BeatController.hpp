//
//  beatController.hpp
//  DoYouEvenDemon
//
//  Created by Amy Parent on 30/01/2016.
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
extern const int kStartValidNotification;
extern const int kEndValidNotification;


class BeatController final {
public:
    
    static void setBPM(double BPM);
    
    static double timeToNextBeat();
    
    static void setMusicFile(const std::string& file, int loops = 1);
    
    static void update(double delta);
    
    static bool validateTiming();
    
    static void setDelay(double delay);
    
    static void stop();
    
private:
    
    static double _delay;
    
    static void _controlEnterBuffer();
    
    static void _controlExitBuffer();
    
    static const Uint8 precision = 1;
    
    BeatController() = delete;
    BeatController(const BeatController&) = delete;
    
    // beat tracking variables
    static double  _beatTime;
    static Uint8   _beatProgression;
    static double  _prog;
    static double  _beatWindow;
    static bool    _inWindow;
};

#endif /* beatController_hpp */
