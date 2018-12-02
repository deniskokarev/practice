cmake_minimum_required(VERSION 3.8)
project(practice_c)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(alg)
include_directories(draft)
ADD_SUBDIRECTORY(googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_custom_command(
	OUTPUT ilog.c ilog.h
	COMMAND ${PROJECT_SOURCE_DIR}/alg/genilog.sh
)

include_directories(${PROJECT_BINARY_DIR})
add_executable(ilog_test alg/ilog_test.cc ilog.c ilog.h)
target_link_libraries(ilog_test gtest gtest_main)

add_executable(par_test alg/par_test.cc alg/par.cc)
target_link_libraries(par_test gtest gtest_main)

add_executable(heap_test alg/heap_test.cc)
target_link_libraries(heap_test gtest gtest_main)

add_executable(binomial_test alg/binomial_test.cc alg/binomial.hh alg/comb.cc alg/comb.hh)
target_link_libraries(binomial_test gtest gtest_main)

add_test(NAME ilog_test COMMAND ilog_test)
add_test(NAME par_test COMMAND par_test)
add_test(NAME heap_test COMMAND heap_test)
add_test(NAME binomial_test COMMAND binomial_test)

add_executable(a a.cc)
add_executable(b b.cc)
add_executable(c c.cc)
add_executable(d d.cc)
add_executable(e e.cc)
add_executable(f f.cc)
