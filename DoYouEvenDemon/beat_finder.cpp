//
//  beat finder.cpp
//  DoYouEvenDemon
//
//  Created by Cesar Parent on 30/01/2016.
//  Copyright © 2016 PixelSpark. All rights reserved.
//

#include "beat_finder.hpp"


beat_finder::beat_finder():
_time(0),
_recording(false),
_accumulator(0) {
}

beat_finder::~beat_finder() {
    
}

void beat_finder::update(double delta) {
    if(!_recording) return;
    _time += delta;
}

double beat_finder::beat() {
    
    if(_time == 0) {
        _recording = true;
        return 0;
    }
    
    double avg = (1.0/_time) * 60.0;
    _time = 0;
    
    _accumulator = (.5 * avg) + (.5 * _accumulator);
    return _accumulator;
}