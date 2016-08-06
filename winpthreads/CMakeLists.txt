# CMAKE project file for building winpthreads with MSVC compiler

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
SET(PROJECT_NAME winpthreads)
PROJECT(${PROJECT_NAME} C)

# TODO: handle static/shared
OPTION(enable_shared "Build shared (dll) winpthreads.dll" OFF)
OPTION(enable_test "Build pthread tests" OFF)

INCLUDE(CheckIncludeFile)
CHECK_INCLUDE_FILE(limits.h HAVE_LIMITS_H)
CHECK_INCLUDE_FILE(sys/timeb.h HAVE_SYS_TIMEB_H)

include_directories(${CMAKE_SOURCE_DIR}/include/)

add_definitions(-DIN_WINPTHREAD)
add_definitions(-DWINPTHREAD_DBG=1)
add_definitions(-DWIN32_LEAN_AND_MEAN)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)

# base pthread library
SET(pthread_SOURCES
	src/barrier.c
	src/cond.c
	src/misc.c
	src/mutex.c
	src/rwlock.c
	src/spinlock.c
	src/thread.c
	src/ref.c
	src/sem.c
	src/sched.c
	src/clock.c
	src/nanosleep.c
	src/libgcc/dll_dependency.S
	src/libgcc/dll_math.c
	src/version.rc
)
SET(pthread_HEADERS
	src/barrier.h
	src/cond.h
	src/misc.h
	src/mutex.h
	src/rwlock.h
	src/thread.h
	src/ref.h
	src/sem.h
	src/wpth_ver.h
	src/winpthread_internal.h
)
SET(pthread_include_HEADERS
	include/pthread.h
	include/sched.h
	include/semaphore.h
	include/pthread_unistd.h
	include/pthread_time.h
	include/pthread_compat.h
	include/pthread_signal.h
)
SET(pthread_TESTS
tests_pthread/barrier1.c
tests_pthread/barrier2.c
tests_pthread/barrier3.c
tests_pthread/barrier4.c
tests_pthread/barrier5.c
tests_pthread/barrier6.c
tests_pthread/cancel1.c
tests_pthread/cancel2.c
tests_pthread/cancel3.c
tests_pthread/cancel4.c
tests_pthread/cancel5.c
tests_pthread/cancel6a.c
tests_pthread/cancel6d.c
tests_pthread/cancel7.c
tests_pthread/cancel8.c
tests_pthread/cancel9.c
tests_pthread/cleanup0.c
tests_pthread/cleanup1.c
tests_pthread/cleanup2.c
tests_pthread/cleanup3.c
tests_pthread/condvar1.c
tests_pthread/condvar1_1.c
tests_pthread/condvar1_2.c
tests_pthread/condvar2.c
tests_pthread/condvar2_1.c
tests_pthread/condvar3.c
tests_pthread/condvar3_1.c
tests_pthread/condvar3_2.c
tests_pthread/condvar3_3.c
tests_pthread/condvar4.c
tests_pthread/condvar5.c
tests_pthread/condvar6.c
tests_pthread/condvar7.c
tests_pthread/condvar8.c
tests_pthread/condvar9.c
tests_pthread/context1.c
tests_pthread/count1.c
tests_pthread/create1.c
tests_pthread/create2.c
tests_pthread/create3.c
tests_pthread/delay1.c
tests_pthread/delay2.c
tests_pthread/detach1.c
tests_pthread/equal1.c
tests_pthread/errno1.c
tests_pthread/exception1.c
tests_pthread/exception2.c
tests_pthread/exception3.c
tests_pthread/exit1.c
tests_pthread/exit2.c
tests_pthread/exit3.c
tests_pthread/exit4.c
tests_pthread/exit5.c
tests_pthread/eyal1.c
tests_pthread/inherit1.c
tests_pthread/join0.c
tests_pthread/join1.c
tests_pthread/join2.c
tests_pthread/join3.c
tests_pthread/kill1.c
tests_pthread/loadfree.c
tests_pthread/mutex1.c
tests_pthread/mutex1e.c
tests_pthread/mutex1n.c
tests_pthread/mutex1r.c
tests_pthread/mutex2.c
tests_pthread/mutex2e.c
tests_pthread/mutex2r.c
tests_pthread/mutex3.c
tests_pthread/mutex3e.c
tests_pthread/mutex3r.c
tests_pthread/mutex4.c
tests_pthread/mutex5.c
tests_pthread/mutex6.c
tests_pthread/mutex6e.c
tests_pthread/mutex6es.c
tests_pthread/mutex6n.c
tests_pthread/mutex6r.c
tests_pthread/mutex6rs.c
tests_pthread/mutex6s.c
tests_pthread/mutex7.c
tests_pthread/mutex7e.c
tests_pthread/mutex7n.c
tests_pthread/mutex7r.c
tests_pthread/mutex8.c
tests_pthread/mutex8e.c
tests_pthread/mutex8n.c
tests_pthread/mutex8r.c
tests_pthread/once1.c
tests_pthread/once2.c
tests_pthread/once3.c
tests_pthread/once4.c
tests_pthread/priority1.c
tests_pthread/priority2.c
tests_pthread/reuse1.c
tests_pthread/reuse2.c
tests_pthread/rwlock1.c
tests_pthread/rwlock2.c
tests_pthread/rwlock2_t.c
tests_pthread/rwlock3.c
tests_pthread/rwlock3_t.c
tests_pthread/rwlock4.c
tests_pthread/rwlock4_t.c
tests_pthread/rwlock5.c
tests_pthread/rwlock5_t.c
tests_pthread/rwlock6.c
tests_pthread/rwlock6_t.c
tests_pthread/rwlock6_t2.c
tests_pthread/rwlock7.c
tests_pthread/rwlock8.c
tests_pthread/self1.c
tests_pthread/self2.c
tests_pthread/semaphore1.c
tests_pthread/semaphore2.c
tests_pthread/semaphore3.c
tests_pthread/semaphore4.c
tests_pthread/semaphore4t.c
tests_pthread/semaphore5.c
tests_pthread/sizes.c
tests_pthread/spin1.c
tests_pthread/spin2.c
tests_pthread/spin3.c
tests_pthread/spin4.c
tests_pthread/stress1.c
tests_pthread/tryentercs.c
tests_pthread/tryentercs2.c
tests_pthread/tsd1.c
tests_pthread/tsd2.c
tests_pthread/valid1.c
tests_pthread/valid2.c
)
SET(pthread_BENCHMARKS
tests_pthread/benchtest1.c
tests_pthread/benchtest2.c
tests_pthread/benchtest3.c
tests_pthread/benchtest4.c
tests_pthread/benchtest5.c
)


add_library(winpthread STATIC ${pthread_SOURCES} ${pthread_HEADERS})

# Testing option
if(enable_test)
    enable_testing()
foreach(t ${pthread_TESTS})
    get_filename_component(test_name ${t} NAME_WE)

    add_executable(${test_name} ${t})
    add_dependencies(${test_name} winpthread)
    target_link_libraries(${test_name} winpthread)

    # make test work
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
foreach(t ${pthread_BENCHMARKS})
    get_filename_component(test_name ${t} NAME_WE)

    add_executable(${test_name} tests_pthread/benchlib.c ${t})
    add_dependencies(${test_name} winpthread)
    target_link_libraries(${test_name} winpthread)

    # make test work
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()

endif(enable_test)

# install rules
#SET(CMAKE_RELEASE_POSTFIX "")
#SET(CMAKE_DEBUG_POSTFIX "-debug")

#install(TARGETS libfolly
 #           ARCHIVE DESTINATION lib
 #           LIBRARY DESTINATION lib
 #           COMPONENT library)

#install(DIRECTORY ${CMAKE_SOURCE_DIR}/ DESTINATION include/folly
 #         FILES_MATCHING PATTERN "*.h")