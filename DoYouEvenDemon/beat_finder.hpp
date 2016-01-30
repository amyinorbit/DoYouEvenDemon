//
//  beat finder.hpp
//  DoYouEvenDemon
//
//  Created by Cesar Parent on 30/01/2016.
//  Copyright © 2016 PixelSpark. All rights reserved.
//

#ifndef beat_finder_hpp
#define beat_finder_hpp

#include <stdio.h>

struct beat_finder {
    
    const int beat_avg = 20;
    
    beat_finder();
    
    ~beat_finder();
    
    void update(double delta);
    
    double beat();
    
private:
    
    double _time;
    
    bool _recording;
    
    double _accumulator;
    
};

#endif /* beat_finder_hpp */
