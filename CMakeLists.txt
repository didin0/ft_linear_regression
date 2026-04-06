# Version minimum de CMake requise
cmake_minimum_required(VERSION 3.10)

# Nom de ton projet et langage (C++)
project(ft_linear_regression CXX)

# Spécifier le standard C++ (C++20 ici)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ajouter les flags de compilation stricts
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
# Ne fonctionne pas avec les bonus
# set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

# Ajouter le dossier "include" pour trouver nos headers (comme csv.h)
include_directories(include)

# Déclarer le premier exécutable (le programme de prédiction)
add_executable(predict src/predict.cpp)

# --- Configuration Python pour le Bonus ---
find_package(Python3 COMPONENTS Development NumPy REQUIRED)

# Déclarer le deuxième exécutable (le programme d'entraînement)
add_executable(train src/train.cpp)
target_link_libraries(train PRIVATE Python3::Python Python3::NumPy)