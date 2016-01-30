//
//  Messenger.hpp
//  DoYouEvenDemon
//
//  Created by Cesar Parent on 30/01/2016.
//  Copyright © 2016 PixelSpark. All rights reserved.
//

#ifndef Messenger_hpp
#define Messenger_hpp

#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>

class Messenger {
public:
    
    Messenger() = delete;
    
    Messenger(const Messenger&) = delete;
    
    static void addObserver(int message,
                            const char* name,
                            std::function<void()> observer);
    
    static void removeObserver(int message,
                               const char* name);
    
    static void postMessage(int message);
    
private:
    
    struct observer {
        int message;
        const char* name;
        std::function<void()> callback;
    };
    
    static std::vector<observer> _listeners;

};

#endif /* Messenger_hpp */
