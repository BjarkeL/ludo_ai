# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ai_player

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ai_player/build

# Include any dependencies generated for this target.
include CMakeFiles/ai_ludo_player.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ai_ludo_player.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ai_ludo_player.dir/flags.make

CMakeFiles/ai_ludo_player.dir/main.cpp.o: CMakeFiles/ai_ludo_player.dir/flags.make
CMakeFiles/ai_ludo_player.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ai_player/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ai_ludo_player.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ai_ludo_player.dir/main.cpp.o -c /home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ai_player/main.cpp

CMakeFiles/ai_ludo_player.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ai_ludo_player.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ai_player/main.cpp > CMakeFiles/ai_ludo_player.dir/main.cpp.i

CMakeFiles/ai_ludo_player.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ai_ludo_player.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ai_player/main.cpp -o CMakeFiles/ai_ludo_player.dir/main.cpp.s

CMakeFiles/ai_ludo_player.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/ai_ludo_player.dir/main.cpp.o.requires

CMakeFiles/ai_ludo_player.dir/main.cpp.o.provides: CMakeFiles/ai_ludo_player.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/ai_ludo_player.dir/build.make CMakeFiles/ai_ludo_player.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/ai_ludo_player.dir/main.cpp.o.provides

CMakeFiles/ai_ludo_player.dir/main.cpp.o.provides.build: CMakeFiles/ai_ludo_player.dir/main.cpp.o


CMakeFiles/ai_ludo_player.dir/ai_player.cpp.o: CMakeFiles/ai_ludo_player.dir/flags.make
CMakeFiles/ai_ludo_player.dir/ai_player.cpp.o: ../ai_player.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ai_player/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ai_ludo_player.dir/ai_player.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ai_ludo_player.dir/ai_player.cpp.o -c /home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ai_player/ai_player.cpp

CMakeFiles/ai_ludo_player.dir/ai_player.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ai_ludo_player.dir/ai_player.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ai_player/ai_player.cpp > CMakeFiles/ai_ludo_player.dir/ai_player.cpp.i

CMakeFiles/ai_ludo_player.dir/ai_player.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ai_ludo_player.dir/ai_player.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ai_player/ai_player.cpp -o CMakeFiles/ai_ludo_player.dir/ai_player.cpp.s

CMakeFiles/ai_ludo_player.dir/ai_player.cpp.o.requires:

.PHONY : CMakeFiles/ai_ludo_player.dir/ai_player.cpp.o.requires

CMakeFiles/ai_ludo_player.dir/ai_player.cpp.o.provides: CMakeFiles/ai_ludo_player.dir/ai_player.cpp.o.requires
	$(MAKE) -f CMakeFiles/ai_ludo_player.dir/build.make CMakeFiles/ai_ludo_player.dir/ai_player.cpp.o.provides.build
.PHONY : CMakeFiles/ai_ludo_player.dir/ai_player.cpp.o.provides

CMakeFiles/ai_ludo_player.dir/ai_player.cpp.o.provides.build: CMakeFiles/ai_ludo_player.dir/ai_player.cpp.o


CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/game.cpp.o: CMakeFiles/ai_ludo_player.dir/flags.make
CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/game.cpp.o: /home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/game.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ai_player/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/game.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/game.cpp.o -c /home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/game.cpp

CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/game.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/game.cpp > CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/game.cpp.i

CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/game.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/game.cpp -o CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/game.cpp.s

CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/game.cpp.o.requires:

.PHONY : CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/game.cpp.o.requires

CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/game.cpp.o.provides: CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/game.cpp.o.requires
	$(MAKE) -f CMakeFiles/ai_ludo_player.dir/build.make CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/game.cpp.o.provides.build
.PHONY : CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/game.cpp.o.provides

CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/game.cpp.o.provides.build: CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/game.cpp.o


CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/test_game.cpp.o: CMakeFiles/ai_ludo_player.dir/flags.make
CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/test_game.cpp.o: /home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/test_game.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ai_player/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/test_game.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/test_game.cpp.o -c /home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/test_game.cpp

CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/test_game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/test_game.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/test_game.cpp > CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/test_game.cpp.i

CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/test_game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/test_game.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/test_game.cpp -o CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/test_game.cpp.s

CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/test_game.cpp.o.requires:

.PHONY : CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/test_game.cpp.o.requires

CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/test_game.cpp.o.provides: CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/test_game.cpp.o.requires
	$(MAKE) -f CMakeFiles/ai_ludo_player.dir/build.make CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/test_game.cpp.o.provides.build
.PHONY : CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/test_game.cpp.o.provides

CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/test_game.cpp.o.provides.build: CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/test_game.cpp.o


# Object files for target ai_ludo_player
ai_ludo_player_OBJECTS = \
"CMakeFiles/ai_ludo_player.dir/main.cpp.o" \
"CMakeFiles/ai_ludo_player.dir/ai_player.cpp.o" \
"CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/game.cpp.o" \
"CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/test_game.cpp.o"

# External object files for target ai_ludo_player
ai_ludo_player_EXTERNAL_OBJECTS =

ai_ludo_player: CMakeFiles/ai_ludo_player.dir/main.cpp.o
ai_ludo_player: CMakeFiles/ai_ludo_player.dir/ai_player.cpp.o
ai_ludo_player: CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/game.cpp.o
ai_ludo_player: CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/test_game.cpp.o
ai_ludo_player: CMakeFiles/ai_ludo_player.dir/build.make
ai_ludo_player: CMakeFiles/ai_ludo_player.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ai_player/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable ai_ludo_player"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ai_ludo_player.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ai_ludo_player.dir/build: ai_ludo_player

.PHONY : CMakeFiles/ai_ludo_player.dir/build

CMakeFiles/ai_ludo_player.dir/requires: CMakeFiles/ai_ludo_player.dir/main.cpp.o.requires
CMakeFiles/ai_ludo_player.dir/requires: CMakeFiles/ai_ludo_player.dir/ai_player.cpp.o.requires
CMakeFiles/ai_ludo_player.dir/requires: CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/game.cpp.o.requires
CMakeFiles/ai_ludo_player.dir/requires: CMakeFiles/ai_ludo_player.dir/home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ludo_game_code/Domain-Code/test_game.cpp.o.requires

.PHONY : CMakeFiles/ai_ludo_player.dir/requires

CMakeFiles/ai_ludo_player.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ai_ludo_player.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ai_ludo_player.dir/clean

CMakeFiles/ai_ludo_player.dir/depend:
	cd /home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ai_player/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ai_player /home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ai_player /home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ai_player/build /home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ai_player/build /home/bjarke/Documents/Uni_8th_semester/tools_for_ai/ludo_ai/ai_player/build/CMakeFiles/ai_ludo_player.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ai_ludo_player.dir/depend

