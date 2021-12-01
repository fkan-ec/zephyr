cmake_minimum_required(VERSION 3.13.1)
set_property(GLOBAL PROPERTY CSTD c11)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(experiments)

add_compile_options(-Wall -Werror -O2 -Wno-format -std=c11 -fomit-frame-pointer -ffast-math)
target_include_directories(app PUBLIC .)

target_sources(
        	app 
               	PRIVATE 
                main.c 
                threads.c 
                timers.c
              )

list(APPEND EXTRA_LIBS zephyr kernel)
target_link_libraries(app PUBLIC ${EXTRA_LIBS})
