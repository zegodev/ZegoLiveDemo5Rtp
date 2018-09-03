cmake --build . --config Release || exit 1
macdeployqt ./ZegoLiveDemo/Release/ZegoLiveDemo.app || exit 1