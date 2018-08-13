project(tnkQt)

cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
if (POLICY CMP0043)
  cmake_policy(SET CMP0043 NEW)
endif()

if(WIN32)
  if(MSVC)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
  endif()
endif()

find_package(Qt5 COMPONENTS Core REQUIRED)

# Auto generate moc files
set(CMAKE_AUTOMOC ON)

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

file(GLOB_RECURSE tnkQt_common_SRCS common/*.cpp common/*.h)


file(GLOB_RECURSE tnkQt_sql_SRCS sql/*.cpp sql/*.h)
find_package(Qt5 COMPONENTS Sql REQUIRED)

file(GLOB_RECURSE tnkQt_ws_SRCS ws/*.cpp ws/*.h)
find_package(Qt5 COMPONENTS Network REQUIRED)

file(GLOB_RECURSE tnkQt_sync_SRCS sync/*.cpp sync/*.h)



# Create the application
add_library(tnkQt SHARED 
	${tnkQtCommon_SRCS} 
	${tnkQt_sql_SRCS} 
	${tnkQt_ws_SRCS}
	${tnkQt_sync_SRCS}
)




# Link to Cutelyst
target_link_libraries(tnkQt
    Qt5::Core    
Qt5::Sql
Qt5::Network
)
