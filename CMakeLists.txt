cmake_minimum_required(VERSION 3.14)
project(LFSR VERSION 1.0 LANGUAGES CXX)

# Встановлення стандарту C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Додаємо каталог заголовкових файлів
include_directories(include)

# Додаємо вихідні файли
add_executable(LFSR 
	src/LFSR.cpp 
	src/LFSRCore.cpp 
	src/Test.cpp 
	include/LFSR.h 
	include/Test.h)

# Указуємо каталог для виконуваних файлів після збірки
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
