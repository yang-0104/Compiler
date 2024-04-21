cmake_minimum_required(VERSION 3.22)
project(BianYi)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(BianYi
        compile.cpp
        compile.h
        LL1.cpp
        lookup.cpp
        out.cpp
        readGrammarFromFile.cpp
        report_error.cpp
        scanner.cpp
        SLR1-base.cpp
        SLR1.cpp readCSV.cpp
        Semantic.cpp
        )
