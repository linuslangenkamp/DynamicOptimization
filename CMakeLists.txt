cmake_minimum_required(VERSION 3.22)
project(gdopt)

set(CMAKE_CXX_STANDARD 17)

include(ExternalProject)

ExternalProject_Add(mumps-ext
        GIT_REPOSITORY https://github.com/coin-or-tools/ThirdParty-Mumps.git
        GIT_TAG releases/3.0.7
        PATCH_COMMAND ${CMAKE_BINARY_DIR}/mumps-ext-prefix/src/mumps-ext/get.Mumps
        CONFIGURE_COMMAND ./configure --enable-shared=no --enable-static=yes --prefix=${CMAKE_BINARY_DIR}/third-party-install/usr/local
        BUILD_COMMAND make -j6
        BUILD_IN_SOURCE true
        )

ExternalProject_Add(ipopt-ext
        GIT_REPOSITORY https://github.com/coin-or/Ipopt.git
        GIT_TAG releases/3.14.16
        CONFIGURE_COMMAND ADD_CFLAGS=-ffast-math ADD_CXXFLAGS=-ffast-math ./configure --enable-shared=no --enable-static=yes --prefix=${CMAKE_BINARY_DIR}/third-party-install/usr/local #--enable-pardisomkl
        BUILD_COMMAND make -j6
        BUILD_IN_SOURCE true
        DEPENDS mumps-ext
        )

set(EXAMPLE_FILES)

include_directories(src examples)

#add_executable(gdopt ${SRC_FILES} ${EXAMPLE_FILES})

add_subdirectory(src)
#add_executable(example_runner EXCLUDE_FROM_ALL src/main.cpp ${EXAMPLE_FILES} )
#target_link_libraries(example_runner gdopt)

#add_executable(batchReactor_example EXCLUDE_FROM_ALL examples/.generated/batchReactor/batchReactorGenerated.cpp )
#target_link_libraries(batchReactor_example gdopt)
