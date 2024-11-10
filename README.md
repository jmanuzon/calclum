# calclum
calculate min, max, mean and median luminance for video files using ffmpeg

The pre-built ffmpeg libraries are for Windows. Please let me know if you need a unix version. Linker will fail under unix atm.

Build Steps:
1.) install cmake
2.) install gcc
3.) cd into calclum directory
4.) using shell, Run cmake .
5.) using shell, cmake --build . --target calclum --config Release
6.) Release folder will be created under calclum directory
7.) cd in to Release folder.
8.) Run calclum.exe ..\videos\ 4

Alternative:
1.) install cmake
2.) cd into calclum directory
3.) Modify CMakePresets compiler of choice.
4.) using shell, Run cmake --preset=release
5.) using shell, cmake --build --preset=release
6.) build\Release folder will be created under calclum directory
7.) cd in to Release folder.
8.) Run calclum.exe ..\..\videos\ 4
