set rootPath=%~dp0
cd vcpkg
vcpkg install --triplet=arm64-android
cd ..
rd /S /Q out\build\arm64-android
md out\build\arm64-android
cd out\build\arm64-android
cmake -DANDROID_NDK_HOME=%ANDROID_NDK_HOME% -DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=%ANDROID_NDK_HOME%/build/cmake/android.toolchain.cmake -DCMAKE_TOOLCHAIN_FILE=%rootPath%..\vcpkg\scripts\buildsystems\vcpkg.cmake -DANDROID_PLATFORM=android-26 -DANDROID_ABI=arm64-v8a -DCMAKE_BUILD_TYPE=Release ..\..\..
cmake --build .
cd %rootPath%\..