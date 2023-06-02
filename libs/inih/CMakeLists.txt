cmake_minimum_required(VERSION 3.0)
project(inih)

set(HEADER_FILES
    src/ini.h
)

set(SOURCE_FILES
    src/ini.c
)

add_library(inih ${HEADER_FILES} ${SOURCE_FILES})