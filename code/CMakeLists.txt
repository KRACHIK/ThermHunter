cmake_minimum_required(VERSION 2.6)

project(ThermHunter)
 
 
file( GLOB SOURCE_CODE
	
	sourse/def.h
	 
	source/input_output_cleo_prms.h
	source/input_output_cleo_prms.cpp
	   
	source/core.h
	source/core.cpp

	source/BaseDequeObject.h
	sourse/BaseDequeObject.cpp
	
	source/ThermDeamon.h
	
	source/MyUtiles.h
	source/MyUtiles.cpp
)
source_group("" FILES ${SOURCE_CODE}) 
  
if(MSVC)
	if (COMMAND cmake_policy)
	CMAKE_POLICY(SET CMP0003 NEW)
	endif(COMMAND cmake_policy)
	set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG}   /MTd /Zi /Ob0 /Od /EHsc /RTC1 /D_DEBUG")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT /O2 /Ob2") 
	add_definitions(-D _CRT_SECURE_NO_WARNINGS)
	add_definitions(/sdl /EHsc /Od /RTC1 /GS)
endif()
set ( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )

add_library( ThermHunter SHARED ${SOURCE_CODE} )
 
   
#########################################################################################
project(client)				 
file( GLOB SOURCE_EXE
 
	sourse/EXE_main.h
	sourse/EXE_main.cpp
	
)
add_executable(client ${SOURCE_EXE})		# Создает исполняемый файл с именем PiratBot
target_link_libraries(client ThermHunter)	# Линковка программы с библиотекой
#########################################################################################
  
project(ThermHunterALL)
 







 