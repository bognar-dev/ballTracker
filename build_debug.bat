if not exist "\build_debug" mkdir build_debug
cd build_debug
conan install .. -pr win.x86.msvc2019.debug
conan build ..