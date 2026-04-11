cmake_minimum_required(VERSION 3.25)
project(Airports C)

add_executable(airports airports.c AVLtree.c)

add_executable(scen1 scenarioTest1.c AVLtree.c list.c)

add_executable(scen2 scenarioTest2.c AVLtree.c list.c)