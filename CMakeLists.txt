cmake_minimum_required(VERSION 3.10)
project(Snake)

set(CMAKE_CXX_STANDARD 17) # Или 14, 20 и т.д.

# Найдите Qt5 (toolchain должен был установить пути)
find_package(Qt5 REQUIRED COMPONENTS Core Widgets) # Добавьте нужные компоненты

# Включите автоматическую обработку MOC/UIC/RCC если используете Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON) # Если используете .ui файлы
set(CMAKE_AUTORCC ON) # Если используете .qrc файлы

# Добавьте исполняемый файл
add_executable(${PROJECT_NAME} game.cpp
        back/backend.h
        front/frontend.h
        front/frontend.cpp
        back/backend.cpp
        common.h
)

# Свяжите с библиотеками Qt
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets) # Добавьте нужные ::Target'ы