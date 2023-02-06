cmake_minimum_required(VERSION 3.25)
project(lzham_api)

option(BUILD_X64 "build 64-bit" TRUE)
include_directories(../lzhamcomp
                    ../lzhamdecomp)

set(CMAKE_CXX_STANDARD 14)


set(GCC_COMPILE_FLAGS "-fno-strict-aliasing -D_LARGEFILE64_SOURCE=1 -D_FILE_OFFSET_BITS=64 ")
if (NOT BUILD_X64)
	set(GCC_COMPILE_FLAGS "${GCC_COMPILE_FLAGS} -m32")
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE} ${GCC_COMPILE_FLAGS} -Wall -Wextra -O3 -fomit-frame-pointer -fexpensive-optimizations")

set(SRC_LIST 
    ../include/lzham_static_lib.h
    ../include/lzham.h
    ../include/zlib.h
    ../include/lzham_exports.inc)

add_library(lzhamlib STATIC ../lzhamlib/lzham_lib.cpp ${SRC_LIST})
add_library(lzhamdecomp STATIC
../lzhamdecomp/lzham_assert.cpp       
../lzhamdecomp/lzham_assert.h         
../lzhamdecomp/lzham_checksum.cpp     
../lzhamdecomp/lzham_checksum.h       
../lzhamdecomp/lzham_config.h         
../lzhamdecomp/lzham_core.h           
../lzhamdecomp/lzham_decomp.h
../lzhamdecomp/lzham_helpers.h        
../lzhamdecomp/lzham_huffman_codes.cpp
../lzhamdecomp/lzham_huffman_codes.h  
../lzhamdecomp/lzham_lzdecompbase.cpp 
../lzhamdecomp/lzham_lzdecompbase.h   
../lzhamdecomp/lzham_lzdecomp.cpp     
../lzhamdecomp/lzham_math.h           
../lzhamdecomp/lzham_mem.cpp          
../lzhamdecomp/lzham_mem.h            
../lzhamdecomp/lzham_platform.cpp     
../lzhamdecomp/lzham_platform.h       
../lzhamdecomp/lzham_prefix_coding.cpp
../lzhamdecomp/lzham_prefix_coding.h  
../lzhamdecomp/lzham_symbol_codec.cpp 
../lzhamdecomp/lzham_symbol_codec.h   
../lzhamdecomp/lzham_timer.cpp        
../lzhamdecomp/lzham_timer.h          
../lzhamdecomp/lzham_traits.h         
../lzhamdecomp/lzham_types.h          
../lzhamdecomp/lzham_utils.h          
../lzhamdecomp/lzham_vector.cpp       
../lzhamdecomp/lzham_vector.h)

add_library(lzhamcomp STATIC
../lzhamcomp/lzham_lzbase.cpp
../lzhamcomp/lzham_lzbase.h
../lzhamcomp/lzham_lzcomp.cpp
../lzhamcomp/lzham_lzcomp_internal.cpp
../lzhamcomp/lzham_lzcomp_internal.h
../lzhamcomp/lzham_lzcomp_state.cpp
../lzhamcomp/lzham_match_accel.cpp
../lzhamcomp/lzham_match_accel.h
../lzhamcomp/lzham_null_threading.h
../lzhamcomp/lzham_pthreads_threading.cpp
../lzhamcomp/lzham_pthreads_threading.h
../lzhamcomp/lzham_threading.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

add_library(${PROJECT_NAME} SHARED
            ${SRC_LIST}
            api.cpp)


target_link_libraries(${PROJECT_NAME} lzhamlib lzhamcomp lzhamdecomp)
