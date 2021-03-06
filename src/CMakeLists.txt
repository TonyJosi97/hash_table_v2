cmake_minimum_required(VERSION 3.18)

project(ht_lib VERSION 2.0)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set (CMAKE_CXX_FLAGS "-Ofast -ggdb3 -pedantic -Wall -Wextra -Wcast-align -Wcast-qual \
-Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self \
-Wmissing-declarations -Wmissing-include-dirs \
-Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow \
-Wsign-conversion -Wsign-promo -Wstrict-overflow=5 \
-Wswitch-default -Wundef -Wno-unused \
-pedantic-errors -Wextra -Waggregate-return -Wcast-align \
-Wcast-qual -Wconversion \
-Wdisabled-optimization \
-Wfloat-equal -Wformat=2 \
-Wformat-nonliteral -Wformat-security  \
-Wformat-y2k \
-Wimplicit  -Wimport  -Winit-self  -Winline \
-Winvalid-pch   \
-Wlong-long \
-Wmissing-field-initializers -Wmissing-format-attribute   \
-Wmissing-include-dirs -Wmissing-noreturn \
-Wpacked -Wpointer-arith \
-Wredundant-decls \
-Wshadow -Wstack-protector \
-Wstrict-aliasing=2 -Wswitch-default \
-Wswitch-enum \
-Wunreachable-code -Wunused \
-Wunused-parameter \
-Wvariadic-macros \
-Wwrite-strings")

SET(SOURCES hash_table_core.cc hash_table_core_util.cc) 

add_library(ht_lib STATIC ${SOURCES})

