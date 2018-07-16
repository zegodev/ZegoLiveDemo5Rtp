path=$(dirname $0)
cd $path

if [[ -a cmake_temp ]];then
	rm -r cmake_temp
fi;

mkdir -p cmake_temp
cd cmake_temp

PATH="/usr/local/opt/qt@5.7/bin:/Applications/CMake.app/Contents/bin":"$PATH"
cmake -G"Xcode" ../..

