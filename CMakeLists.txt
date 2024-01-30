cmake_minimum_required(VERSION 3.23)
project(CustomQuadTree)

set(CMAKE_CXX_STANDARD 20)

set(SDL2_INCLUDE_DIR C:/Main_folder/SDL2/x86_64-w64-mingw32/include)
set(SDL2_LIB_DIR C:/Main_folder/SDL2/x86_64-w64-mingw32/lib)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(CustomQuadTree main.cpp View/Draw.cpp View/Draw.h View/View.cpp View/View.h QuadTree/Region.h QuadTree/Point.h QuadTree/Leaf.h QuadTree/Leaf.cpp QuadTree/Branch.cpp QuadTree/Branch.h Config.h QuadTree/Point.cpp Logger.h Logger.cpp Test/ClosestPointTest.cpp Test/ClosestPointTest.h QuadTree/Region.cpp Graph/Node.cpp Graph/Node.h PathFinding/RRT.cpp PathFinding/RRT.h Graph/CordMap.cpp Graph/CordMap.h)
#add_executable(CustomQuadTree main.cpp QuadTree/Region.h QuadTree/Point.h QuadTree/Leaf.h QuadTree/Leaf.cpp QuadTree/Branch.cpp QuadTree/Branch.h Config.h QuadTree/Point.cpp View/Draw.cpp View/Draw.h View/View.cpp View/View.h Logger.h Logger.cpp Test/ClosestPointTest.cpp Test/ClosestPointTest.h QuadTree/Region.cpp)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2)