if exist %cd%\cmake_temp (
    rd /q/s cmake_temp
)

md cmake_temp
cd cmake_temp

cmake -G"Visual Studio 12 2013"  -DWINDOWS_PLATFORM=x86 ../..

