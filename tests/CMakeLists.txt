# Versión mínima de CMake requerida
cmake_minimum_required(VERSION 3.11)

# Declarar el proyecto
project(ftxui_project LANGUAGES CXX VERSION 1.0.0)

# Configuración estándar de C++ (cambiar a 17 o 20 según necesidades)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Incluir FetchContent para manejar dependencias externas
include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)

# Declarar y descargar FTXUI
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG main # Cambia esto por un commit hash estable para mayor estabilidad
)
FetchContent_MakeAvailable(ftxui)

# Incluir directorios adicionales
include_directories(include)

# Añadir el ejecutable
add_executable(ftxui_app src/main.cpp)

# Vincular las librerías necesarias de FTXUI
target_link_libraries(ftxui_app
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)

