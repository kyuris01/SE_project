cmake_minimum_required(VERSION 3.10)
project(SE_Project)

# C 표준 설정
set(CMAKE_C_STANDARD 11)

# 코드 커버리지 플래그 추가
if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

# 메인 프로그램 실행 파일 생성
add_executable(rvc rvc.c shared.c)

# 테스트 실행 파일 생성
add_executable(tester tester.c rvc.c shared.c)
target_compile_definitions(tester PRIVATE TESTING)

# CTest 활성화
enable_testing()

# 개별 테스트 등록
add_test(NAME Test1 COMMAND tester --test1)
add_test(NAME Test2 COMMAND tester --test2)
add_test(NAME Test3 COMMAND tester --test3)
add_test(NAME Test4 COMMAND tester --test4)
add_test(NAME Test5 COMMAND tester --test5)
add_test(NAME Test6 COMMAND tester --test6)
add_test(NAME Test7 COMMAND tester --test7)
add_test(NAME Test8 COMMAND tester --test8)
add_test(NAME Test9 COMMAND tester --test9)
add_test(NAME Test10 COMMAND tester --test10)
add_test(NAME Test11 COMMAND tester --test11)

add_test(NAME Test12 COMMAND tester --test12)
add_test(NAME Test13 COMMAND tester --test13)
add_test(NAME Test14 COMMAND tester --test14)
add_test(NAME Test15 COMMAND tester --test15)
add_test(NAME Test16 COMMAND tester --test16)
add_test(NAME Test17 COMMAND tester --test17)
add_test(NAME Test18 COMMAND tester --test18)
add_test(NAME Test19 COMMAND tester --test19)
add_test(NAME Test20 COMMAND tester --test20)
add_test(NAME Test21 COMMAND tester --test21)

add_custom_target(coverage
    COMMAND find ${CMAKE_BINARY_DIR}/CMakeFiles/tester.dir -name "*.gcda" -exec gcov -o ${CMAKE_BINARY_DIR}/CMakeFiles/tester.dir {} +
    COMMENT "Generating coverage summary using gcov"
    VERBATIM
)

