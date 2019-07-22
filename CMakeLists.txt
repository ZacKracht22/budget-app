cmake_minimum_required(VERSION 3.5)
project(BUDGETAPP CXX)

# try to prevent accidental in-source builds, these cause lots of problems
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Remove any files created thus far and use a different directory for the build.")
endif()

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# configure Qt
find_package(Qt5 COMPONENTS Widgets Test REQUIRED)
if (Qt5Widgets_FOUND AND Qt5Test_FOUND)
  set(CMAKE_AUTOMOC ON)
  set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()
find_package(Qt5Charts)

set(gui_src
	budget.cpp
	expense_widget.cpp
	weights_widget.cpp
	income_widget.cpp
	budget_creator.cpp
	budget_view.cpp
	util.cpp
  )


# main entry point for GUI interface
set(gui_main
  main.cpp
)



if (Qt5Widgets_FOUND AND Qt5Test_FOUND)
	# build the program
	add_executable(budget_app ${gui_main} ${gui_src})
	target_link_libraries(budget_app Qt5::Widgets Qt5::Charts Qt5::Test)

	add_executable(budget_tests budget.cpp budget_test.cpp)
	target_link_libraries(budget_tests Qt5::Widgets Qt5::Test)

	add_executable(util_tests util.cpp util_test.cpp)
	target_link_libraries(util_tests Qt5::Widgets Qt5::Test)

else (Qt5Widgets_FOUND AND Qt5Test_FOUND)
  message("Qt >= 5.9  needs to be installed to build the budget interface and related tests.")
endif (Qt5Widgets_FOUND AND Qt5Test_FOUND)