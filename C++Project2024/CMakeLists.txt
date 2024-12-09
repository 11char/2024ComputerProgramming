cmake_minimum_required(VERSION 3.26)
project(C__Project2024 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add paths for Homebrew installations
list(APPEND CMAKE_PREFIX_PATH
        /opt/homebrew/opt/sdl2
        /opt/homebrew/Cellar/sdl2_mixer/2.8.0
        /opt/homebrew/opt/sdl2_gfx
)

# Find SDL2 and SDL2_mixer
find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

find_library(SDL2_GFX_LIBRARY SDL2_gfx PATHS /opt/homebrew/opt/sdl2_gfx/lib REQUIRED)

# Add executable and sources
set(SOURCES
        src/main.cpp
        src/Beat.cpp
        src/BeatSequence.cpp
        src/GameController.cpp
)

set(HEADERS
        src/Beat.h
        src/BeatSequence.h
        src/GameController.h
        src/SequenceGenerator.cpp
        src/SequenceGenerator.h
        src/MainWindow.cpp
        src/MainWindow.h
)

add_executable(C__Project2024 ${SOURCES} ${HEADERS})

# Link libraries and include directories
target_include_directories(C__Project2024 PRIVATE
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_MIXER_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
        /opt/homebrew/opt/sdl2_gfx/include)
target_link_libraries(C__Project2024 PRIVATE
        SDL2::SDL2
        SDL2_mixer::SDL2_mixer
        SDL2_ttf::SDL2_ttf
        ${SDL2_GFX_LIBRARY})
