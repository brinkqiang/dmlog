
rmdir /S /Q build
mkdir build
pushd build
cmake -A win32 -DCMAKE_BUILD_TYPE=relwithdebinfo ..
cmake --build . --config relwithdebinfo
popd

rem pause