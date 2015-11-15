cmake_minimum_required(VERSION 2.8)

include_directories(.)

add_executable(multiplus
	Multiplus.cpp
	RS232.cpp
	main.cpp
)

target_link_libraries(multiplus
	kogmo_rtdb
	rt
	MultiPlusData
)
