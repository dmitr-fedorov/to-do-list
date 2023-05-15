include(FetchContent)
FetchContent_Declare(gtest
  QUIET
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)

set(TARGET_NAME "tests")

set(INCLUDE_DIR_PATH "../include")

add_executable(${TARGET_NAME}
  InputAnalysisToolsTest.cpp
  DateTimeUtilityTest.cpp
)

target_link_libraries(${TARGET_NAME}
  PRIVATE
    ${SOURCE_LIB_NAME}
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(${TARGET_NAME}
  PROPERTIES
    LABELS "unit"
  DISCOVERY_TIMEOUT
    240
)