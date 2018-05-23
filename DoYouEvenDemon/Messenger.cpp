//
//  Messenger.cpp
//  DoYouEvenDemon
//
//  Created by Amy Parent on 30/01/2016.
//  Copyright © 2016 PixelSpark. All rights reserved.
//

#include "Messenger.hpp"
#include <algorithm>
#include <cstring>


std::vector<Messenger::observer> Messenger::_listeners;



void Messenger::addObserver(int message, const char *name, std::function<void ()> obs) {
    
    auto iter = std::find_if(_listeners.begin(), _listeners.end(), [=](const observer& _obs){
        return (_obs.message == message && (_obs.name == name || std::strcmp(_obs.name, name)));
    });
    if(iter != _listeners.end()) {
        (*iter).callback = obs;
        return;
    }
    
    observer a;
    a.message = message;
    a.name = name;
    a.callback = obs;
    _listeners.push_back(a);
    
}

void Messenger::removeObserver(int message, const char *name) {
    std::remove_if(_listeners.begin(), _listeners.end(), [=](const observer& obs) {
        return (obs.message == message && (obs.name == name || std::strcmp(obs.name, name)));
    });
}

void Messenger::postMessage(int message) {
    std::for_each(_listeners.begin(), _listeners.end(), [message](const observer& obs){
        if(obs.message != message) return;
        if(obs.callback) {
            obs.callback();
        }
    });
}
