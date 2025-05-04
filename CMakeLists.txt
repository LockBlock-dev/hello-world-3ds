cmake_minimum_required(VERSION 3.13)

# Declare project containing a single eponymous executable
project(3ds_application LANGUAGES C CXX ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME})

# Declare an asset target for the executable's RomFS (optional)
#dkp_add_asset_target(${PROJECT_NAME}_romfs romfs)

# Generate symbol list and map information (useful for debugging)
dkp_target_generate_symbol_list(${PROJECT_NAME})

# Generate a SMDH file for the executable
ctr_generate_smdh(${PROJECT_NAME}.smdh
	NAME "${PROJECT_NAME}"

	# Other options available:
	#DESCRIPTION "Built with devkitARM & libctru"
	#AUTHOR      "Unspecified Author"
	#ICON        myIcon.png
)

# Specify that the executable is a 3DSX file
ctr_create_3dsx(${PROJECT_NAME}
	SMDH ${PROJECT_NAME}.smdh
	#ROMFS ${PROJECT_NAME}_romfs  # Uncomment this if using RomFS
)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 23)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD_REQUIRED TRUE)

# Options for code generation
target_compile_options(${PROJECT_NAME} PRIVATE
	# Common C/C++ options
	-Wall
    -Werror

	# C++ specific options
	$<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions -fno-rtti>
)

# Options for linking to libraries (example)
#target_link_libraries(${PROJECT_NAME} PRIVATE
#	citro3d
#)

# Source code files
target_sources(${PROJECT_NAME} PRIVATE
	source/main.cpp
)

# PICA200 shader source code files (example)
#ctr_add_shader_library(${PROJECT_NAME}_shaders
#	source/vertex_shader.pica
#)

# Converted texture (example)
#ctr_add_graphics_target(my_tex IMAGE
#	INPUTS gfx/my_tex.png
#)

# Texture atlas (example)
#ctr_add_graphics_target(my_atlas ATLAS
#	INPUTS gfx/sprite1.png gfx/sprite2.png
#)

# Install assets to RomFS (uncomment as needed)
#dkp_install_assets (${PROJECT_NAME}_romfs TARGETS
#	${PROJECT_NAME}_shaders
#	my_tex
#	my_atlas
#)
