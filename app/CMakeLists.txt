# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

include_directories("src/main/cpp" "src/main/cpp/common" "src/main/cpp/jni"
                    "src/main/cpp/shapes" ${ANDROID_NDK}/sources/android/native_app_glue/
                    "src/main/external/glm")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/cpp/native-lib.cpp )
add_library(GLESNative SHARED
            src/main/cpp/common/glesNative.cpp
            src/main/cpp/jni/glesContextActivity.cpp
            src/main/cpp/jni/CubeActivity.cpp
            src/main/cpp/jni/myGLRenderer.cpp
            src/main/cpp/jni/gestures.cpp
            src/main/cpp/shapes/triangle.cpp
            src/main/cpp/common/myShader.cpp
            src/main/cpp/common/MyJNIShaderHelper.cpp
            src/main/cpp/common/MyCamera.cpp
            src/main/cpp/shapes/cube.cpp)
add_library( app-glue
             STATIC
             ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-lib
                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )
target_link_libraries(GLESNative android log app-glue GLESv2)