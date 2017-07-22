cmake_minimum_required(VERSION 3.6)

set(CMAKE_C_STANDARD 99)

add_library(fast_blur SHARED
	src/main/jni/gaussian_blur.c
	src/main/jni/recursive_blur.c
	src/main/jni/com_android_gaussianblur_BlurNative.c
	src/main/jni/blur.c)
target_link_libraries(fast_blur log jnigraphics)