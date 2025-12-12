cmake_minimum_required(VERSION 4)
project(sufa)

set(CMAKE_CXX_STANDARD 17)

add_executable(sufa
        main.cpp
        home.cpp
        home.h
        cmd/command.h
        cmd/cd_command.cpp
        cmd/cd_command.h
        cmd/cmd_cache.cpp
        cmd/cmd_cache.h
        cmd/command.cpp
        managers/command_manager.cpp
        managers/command_manager.h
        signal.cpp
        signal.h
        args.cpp
        args.h
        structs/trie.h
        completion.h
        completion.cpp
        structs/trie.cpp
)

target_link_libraries(sufa PRIVATE readline history ncurses)
