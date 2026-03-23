# 1. Version minimum de CMake requise
cmake_minimum_required(VERSION 3.10)

# 2. Nom de ton projet et langage (C++)
project(ft_linear_regression CXX)

# 3. Spécifier le standard C++ (C++20 ici)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. Ajouter les flags de compilation stricts
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
# set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

# Ajouter le dossier "include" pour trouver nos headers (comme csv.h)
include_directories(include)

# 5. Déclarer le premier exécutable (le programme de prédiction)
add_executable(predict src/predict.cpp)

# 6. Déclarer le deuxième exécutable (le programme d'entraînement)
add_executable(train src/train.cpp)