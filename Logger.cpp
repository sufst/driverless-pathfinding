//
// Created by shree on 29/09/2023.
//

#include <unordered_map>
#include "Logger.h"

std::unordered_map<ObjectsToTrack, MemoryTracker> Logger::objectsMap;

void Logger::printObjectsMap(){
    print("MLeaf", objectsMap[MLeaf].created, objectsMap[MLeaf].destroyed);
    print("MBranch", objectsMap[MBranch].created, objectsMap[MBranch].destroyed);
}

void Logger::trackMemory(ObjectsToTrack objectsToTrack, bool state) {
    if (LOG_LEVEL < MEMORY) {
        return;
    }

    if (state) {
        objectsMap[objectsToTrack].created += 1;
    } else {
        objectsMap[objectsToTrack].destroyed += 1;
    }
}
