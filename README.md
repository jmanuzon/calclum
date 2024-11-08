# calclum
calculate min, max, mean and median luminance for video files using ffmpeg

The pre-built ffmpeg libraries are for Windows. Please let me know if you need a unix version. Linker will fail under unix atm.

Build Steps:
1.) install cmake
2.) install gcc
3.) Configure or create a new CMakePresets files
4.) cd into calclum directory
5.) using shell, Run cmake .
6.) using shell, cmake --build . --target calclum --config Release
7.) Release folder will me created under calclum directory
8.) cd in to Release folder.
9.) Run calclum.exe ..\videos\ 4
