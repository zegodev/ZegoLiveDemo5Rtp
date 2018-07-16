cmake --build . --config Release || exit 1
macdeployqt ./cmake_temp/ZegoLiveDemo/Release/ZegoLiveDemo.app || exit 1