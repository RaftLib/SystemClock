cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
project(SystemClock)
set( version 1.1x )
set( CMAKE_INCLUDE_CURRENT_DIR ON )


if( UNIX )
##
# Check for CXX11 or greater
##
include( CheckCXXCompilerFlag )
check_cxx_compiler_flag( "-std=c++11" COMPILER_SUPPORTS_CXX11 )
if( COMPILER_SUPPORTS_CXX11 )
 set( CMAKE_CXX_STANDARD 11 )
else()
 message( FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a newer compiler" )
endif()

##
# Check for c99 or greater
##
include( CheckCCompilerFlag )
check_c_compiler_flag( "-std=c99" COMPILER_SUPPORTS_C99 )
if( COMPILER_SUPPORTS_C99 )
 set( CMAKE_C_STANDARD 99 )
else()
 message( FATAL_ERROR "The compiler ${CMAKE_C_COMPILER} has no c99 support. Please use a newer compiler" )
endif()
set( CXX_STANDARD ON )
set( C_STANDARD ON )
endif( UNIX )

include_directories ( ${PROJECT_SOURCE_DIR}/include )

add_subdirectory( lib )
add_subdirectory( testsuite )


enable_testing()
set( TESTAPPS 
        basicClockUse 
        testclock
        teststop )

foreach( APP ${TESTAPPS} )
    add_test( NAME "${APP}_clock_test"
              COMMAND ${APP} )
endforeach( APP ${TESTAPPS} )
