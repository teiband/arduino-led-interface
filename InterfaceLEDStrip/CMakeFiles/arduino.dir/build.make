# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Produce verbose output by default.
VERBOSE = 1

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/teiband/wearhap

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/teiband/wearhap

# Include any dependencies generated for this target.
include src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/depend.make

# Include the progress variables for this target.
include src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/progress.make

# Include the compile flags for this target's objects.
include src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/flags.make

src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/arduino.cpp.o: src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/flags.make
src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/arduino.cpp.o: src/actuators/arduino-led-interface/InterfaceLEDStrip/arduino.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/teiband/wearhap/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/arduino.cpp.o"
	cd /home/teiband/wearhap/src/actuators/arduino-led-interface/InterfaceLEDStrip && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/arduino.dir/arduino.cpp.o -c /home/teiband/wearhap/src/actuators/arduino-led-interface/InterfaceLEDStrip/arduino.cpp

src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/arduino.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/arduino.dir/arduino.cpp.i"
	cd /home/teiband/wearhap/src/actuators/arduino-led-interface/InterfaceLEDStrip && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/teiband/wearhap/src/actuators/arduino-led-interface/InterfaceLEDStrip/arduino.cpp > CMakeFiles/arduino.dir/arduino.cpp.i

src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/arduino.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/arduino.dir/arduino.cpp.s"
	cd /home/teiband/wearhap/src/actuators/arduino-led-interface/InterfaceLEDStrip && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/teiband/wearhap/src/actuators/arduino-led-interface/InterfaceLEDStrip/arduino.cpp -o CMakeFiles/arduino.dir/arduino.cpp.s

src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/arduino.cpp.o.requires:
.PHONY : src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/arduino.cpp.o.requires

src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/arduino.cpp.o.provides: src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/arduino.cpp.o.requires
	$(MAKE) -f src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/build.make src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/arduino.cpp.o.provides.build
.PHONY : src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/arduino.cpp.o.provides

src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/arduino.cpp.o.provides.build: src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/arduino.cpp.o

src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/main.cpp.o: src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/flags.make
src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/main.cpp.o: src/actuators/arduino-led-interface/InterfaceLEDStrip/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/teiband/wearhap/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/main.cpp.o"
	cd /home/teiband/wearhap/src/actuators/arduino-led-interface/InterfaceLEDStrip && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/arduino.dir/main.cpp.o -c /home/teiband/wearhap/src/actuators/arduino-led-interface/InterfaceLEDStrip/main.cpp

src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/arduino.dir/main.cpp.i"
	cd /home/teiband/wearhap/src/actuators/arduino-led-interface/InterfaceLEDStrip && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/teiband/wearhap/src/actuators/arduino-led-interface/InterfaceLEDStrip/main.cpp > CMakeFiles/arduino.dir/main.cpp.i

src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/arduino.dir/main.cpp.s"
	cd /home/teiband/wearhap/src/actuators/arduino-led-interface/InterfaceLEDStrip && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/teiband/wearhap/src/actuators/arduino-led-interface/InterfaceLEDStrip/main.cpp -o CMakeFiles/arduino.dir/main.cpp.s

src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/main.cpp.o.requires:
.PHONY : src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/main.cpp.o.requires

src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/main.cpp.o.provides: src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/main.cpp.o.requires
	$(MAKE) -f src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/build.make src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/main.cpp.o.provides.build
.PHONY : src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/main.cpp.o.provides

src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/main.cpp.o.provides.build: src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/main.cpp.o

src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/RS232.cpp.o: src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/flags.make
src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/RS232.cpp.o: src/actuators/arduino-led-interface/InterfaceLEDStrip/RS232.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/teiband/wearhap/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/RS232.cpp.o"
	cd /home/teiband/wearhap/src/actuators/arduino-led-interface/InterfaceLEDStrip && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/arduino.dir/RS232.cpp.o -c /home/teiband/wearhap/src/actuators/arduino-led-interface/InterfaceLEDStrip/RS232.cpp

src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/RS232.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/arduino.dir/RS232.cpp.i"
	cd /home/teiband/wearhap/src/actuators/arduino-led-interface/InterfaceLEDStrip && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/teiband/wearhap/src/actuators/arduino-led-interface/InterfaceLEDStrip/RS232.cpp > CMakeFiles/arduino.dir/RS232.cpp.i

src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/RS232.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/arduino.dir/RS232.cpp.s"
	cd /home/teiband/wearhap/src/actuators/arduino-led-interface/InterfaceLEDStrip && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/teiband/wearhap/src/actuators/arduino-led-interface/InterfaceLEDStrip/RS232.cpp -o CMakeFiles/arduino.dir/RS232.cpp.s

src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/RS232.cpp.o.requires:
.PHONY : src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/RS232.cpp.o.requires

src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/RS232.cpp.o.provides: src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/RS232.cpp.o.requires
	$(MAKE) -f src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/build.make src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/RS232.cpp.o.provides.build
.PHONY : src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/RS232.cpp.o.provides

src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/RS232.cpp.o.provides.build: src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/RS232.cpp.o

# Object files for target arduino
arduino_OBJECTS = \
"CMakeFiles/arduino.dir/arduino.cpp.o" \
"CMakeFiles/arduino.dir/main.cpp.o" \
"CMakeFiles/arduino.dir/RS232.cpp.o"

# External object files for target arduino
arduino_EXTERNAL_OBJECTS =

bin/arduino: src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/arduino.cpp.o
bin/arduino: src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/main.cpp.o
bin/arduino: src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/RS232.cpp.o
bin/arduino: src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/build.make
bin/arduino: src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../../../bin/arduino"
	cd /home/teiband/wearhap/src/actuators/arduino-led-interface/InterfaceLEDStrip && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/arduino.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/build: bin/arduino
.PHONY : src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/build

src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/requires: src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/arduino.cpp.o.requires
src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/requires: src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/main.cpp.o.requires
src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/requires: src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/RS232.cpp.o.requires
.PHONY : src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/requires

src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/clean:
	cd /home/teiband/wearhap/src/actuators/arduino-led-interface/InterfaceLEDStrip && $(CMAKE_COMMAND) -P CMakeFiles/arduino.dir/cmake_clean.cmake
.PHONY : src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/clean

src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/depend:
	cd /home/teiband/wearhap && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/teiband/wearhap /home/teiband/wearhap/src/actuators/arduino-led-interface/InterfaceLEDStrip /home/teiband/wearhap /home/teiband/wearhap/src/actuators/arduino-led-interface/InterfaceLEDStrip /home/teiband/wearhap/src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/actuators/arduino-led-interface/InterfaceLEDStrip/CMakeFiles/arduino.dir/depend
