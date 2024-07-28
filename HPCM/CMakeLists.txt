# CMakeList.txt : CMake project for CellMachine, include source and define
# project specific logic here.
#

protobuf_generate_cpp(CellMachine_ProtocolBuffers_Sources CellMachine_ProtocolBuffers_Headers "test.proto" "Settings/Settings.proto")

# Add source to this project's executable.
add_executable (CellMachine
	"CellMachine.cpp"
	"CellMachine.h"
	
	"Grid.cpp"
	"Grid.hpp"
	
	"Interface.cpp"
	"Interface.hpp"

	"ApplicationContext.cpp"
	"ApplicationContext.hpp"
	
	"Settings/Settings.cpp"
	"Settings/Settings.hpp"

	"Logic/Logic.cpp"
	"Logic/Logic.hpp"

	"Blocks/BlockAbstract.hpp"

	"Screens/MainMenu/MainMenu.cpp"
	"Screens/MainMenu/MainMenu.hpp"

	"Screens/LoadingScreen/LoadingScreen.cpp"
	"Screens/LoadingScreen/LoadingScreen.hpp"

	"Settings/Interface.cpp"
	"Settings/Interface.hpp"
	
	${CellMachine_ProtocolBuffers_Sources} ${CellMachine_ProtocolBuffers_Headers} "Interface.cpp"  "AudioSystem.hpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CellMachine PROPERTY CXX_STANDARD 23)
endif()

target_link_libraries(CellMachine PRIVATE protobuf::libprotobuf-lite)

list(GET CellMachine_ProtocolBuffers_Headers 0 CellMachine_ProtocolBuffers_ProbeDirectoryHeader)
# We can mark this as cache, even though the file header we probe may be different between calls, the directory will always be the same unless we re-configure.
get_filename_component(CellMachine_ProtocolBuffers_IncludeDirectory ${CellMachine_ProtocolBuffers_ProbeDirectoryHeader} DIRECTORY CACHE)
target_include_directories(CellMachine PRIVATE ${CellMachine_ProtocolBuffers_IncludeDirectory})

target_link_libraries(CellMachine
	PRIVATE
	$<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

target_link_libraries(CellMachine PRIVATE SDL2::SDL2_gfx)
target_link_libraries(CellMachine PRIVATE $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>)
target_link_libraries(CellMachine PRIVATE imgui::imgui)

add_custom_command(
        TARGET CellMachine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
                ${CMAKE_CURRENT_SOURCE_DIR}/Resources/
                ${CMAKE_CURRENT_BINARY_DIR}/Resources/)

# TODO: Add tests and install targets if needed.
