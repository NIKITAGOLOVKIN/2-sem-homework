cmake_minimum_required(VERSION 3.25)
project(Airports C)

set(COMMON_SOURCES
    AVLtree.c
    list.c
)

add_executable(airports airports.c AVLtree.c)


add_executable(test1_avl scenarioTest1.c ${COMMON_SOURCES})
add_executable(test1_list scenarioTest1.c ${COMMON_SOURCES})


add_executable(test2_avl scenarioTest2.c ${COMMON_SOURCES})
add_executable(test2_list scenarioTest2.c ${COMMON_SOURCES})


add_executable(tests tests.c ${COMMON_SOURCES})