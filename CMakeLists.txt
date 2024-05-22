cmake_minimum_required(VERSION 3.10)

# Проектное имя
project(MyProject)

# Включение стандарта C++17
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавление заголовочных файлов
include_directories(include)

# Добавление исходных файлов
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Добавление библиотеки
add_library(MyLibrary ${SOURCES})

# Добавление исполняемого файла
add_executable(task app/main.cpp)

# Связывание исполняемого файла с библиотекой
target_link_libraries(task MyLibrary)
