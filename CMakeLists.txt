# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

option(HPCM_NO_BUILD_TARGETS "Disables all builds targets, and only includes the HPCM-Shared documentation target (if supported by the system). Note that the documentation can still be generated with this option disabled (assuming your system has Doxygen installed)." FALSE)

if (HPCM_NO_BUILD_TARGETS)
	# If we don't want to build targets, vcpkg has no business here, since it only installs compilation dependencies.
	# So we disable vcpkg here.
	set(CMAKE_TOOLCHAIN_FILE "")
endif()

project ("HPCM")

if (NOT HPCM_NO_BUILD_TARGETS)
	find_package(SDL2 CONFIG REQUIRED)
	find_package(SDL2_image CONFIG REQUIRED)
	find_package(SDL2_mixer CONFIG REQUIRED)
	find_package(SDL2_ttf CONFIG REQUIRED)
	find_package(protobuf CONFIG REQUIRED)
	find_package(imgui CONFIG REQUIRED)
	find_package(sdl2-gfx CONFIG REQUIRED)
endif()

# Include sub-projects.
if(NOT ProjectHSIBot_NO_BUILD_TARGETS)
	add_subdirectory("HPCM")
endif()

include("HPCM-Docs/Doxygen.cmake")