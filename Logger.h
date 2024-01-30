//
// Created by shree on 29/09/2023.
//

#ifndef CUSTOMQUADTREE_LOGGER_H
#define CUSTOMQUADTREE_LOGGER_H

#include <iostream>
#include <unordered_map>

enum LoggerLevel{
    INFO,
    MEMORY, // Used to check for memory leaks
    DEBUG,
};

enum ObjectsToTrack {
    MLeaf,
    MBranch,
    MPoint,
};

struct MemoryTracker {
public:
    int created = 0;
    int destroyed = 0;
};

class Logger {
private:
    static std::unordered_map<ObjectsToTrack, MemoryTracker> objectsMap;

public:
    static const LoggerLevel LOG_LEVEL = MEMORY;

    template<typename T>
    static void print(T t) {
        std::cout << t << '\n';
    }

    template<typename T, typename ...Params>
    static void print(T t, Params... params) {
        std::cout << t << " ";
        print(params...);
    }

    template<typename ...Params>
    static void print(LoggerLevel level, Params... params) {
        if (level <= LOG_LEVEL) {
            print(params...);
        }
    }

    template<typename ...Params>
    static void print(bool enable, LoggerLevel level, Params... params) { // to easily disable logs without commenting
        if (enable) {
            print(level, params...);
        }
    }

    static void trackMemory(ObjectsToTrack objectsToTrack, bool state);

    static void printObjectsMap();
};


#endif //CUSTOMQUADTREE_LOGGER_H
