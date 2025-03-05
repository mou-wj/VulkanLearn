cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)
set(TargetName VulkanLearn)
project(${TargetName})
find_package(Vulkan)
if(Vulkan_FOUND)
    list(APPEND Libs3rd ${Vulkan_LIBRARIES})
	list(APPEND IncludeDir3rd "${Vulkan_INCLUDE_DIRS}")
	
else()
	message(FATAL_ERROR "vulkan is not found")
endif()

file(GLOB_RECURSE SrcFiles ./src/*.cpp ./src/*.h ./src/*.c)

add_executable(${TargetName} ${SrcFiles})
target_include_directories(${TargetName} PUBLIC ${IncludeDir3rd})
target_compile_definitions(${TargetName} PRIVATE VULKAN_INCLUDE_DIRS="${Vulkan_INCLUDE_DIRS}" PROJECT_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(${TargetName} PRIVATE ${Libs3rd})



