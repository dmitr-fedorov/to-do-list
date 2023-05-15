set(INCLUDE_DIR_PATH "../include")

set(HEADERS
  ${INCLUDE_DIR_PATH}/DateTimeUtility.h
  ${INCLUDE_DIR_PATH}/DateTime.h
  ${INCLUDE_DIR_PATH}/Task.h
  ${INCLUDE_DIR_PATH}/TaskList.h
  ${INCLUDE_DIR_PATH}/TaskStorageFile.h
  ${INCLUDE_DIR_PATH}/InputAnalysisTools.h
  ${INCLUDE_DIR_PATH}/Command.h
  ${INCLUDE_DIR_PATH}/CommandAdd.h
  ${INCLUDE_DIR_PATH}/CommandUpdate.h
  ${INCLUDE_DIR_PATH}/CommandDelete.h
  ${INCLUDE_DIR_PATH}/CommandDone.h
  ${INCLUDE_DIR_PATH}/CommandSelect.h
  ${INCLUDE_DIR_PATH}/CommandSave.h
  ${INCLUDE_DIR_PATH}/CommandsInvoker.h
)

set(SOURCES
  DateTimeUtility.cpp
  DateTime.cpp
  Task.cpp
  TaskList.cpp
  TaskStorageFile.cpp
  InputAnalysisTools.cpp
  CommandAdd.cpp
  CommandUpdate.cpp
  CommandDelete.cpp
  CommandDone.cpp
  CommandSelect.cpp
  CommandSave.cpp
  CommandsInvoker.cpp
)

set(TARGET_NAME "app")

set(SOURCE_LIB_NAME "${TARGET_NAME}_src")

set(SOURCE_LIB_NAME "${SOURCE_LIB_NAME}" PARENT_SCOPE)

add_library(${SOURCE_LIB_NAME}
  ${HEADERS}
  ${SOURCES}
)

add_executable(${TARGET_NAME}
  main.cpp
)

target_link_libraries(${TARGET_NAME}
  ${SOURCE_LIB_NAME}
)