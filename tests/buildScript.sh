set -e
mkdir -p build && cd build
cmake -GNinja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
ninja
./ftxui_app

