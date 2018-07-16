if exist %cd%\cmake_temp_x64 (
    rd /q/s cmake_temp_x64
)

md cmake_temp_x64
cd cmake_temp_x64

cmake -G"Visual Studio 12 2013 Win64"  -DWINDOWS_PLATFORM=x64 ../..

