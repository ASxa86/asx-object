project(test-asx-node)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
	Node.test.cpp
)

find_package(GTest CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
	asx-node
	GTest::gtest_main
	GTest::gtest
)

project_install_target()
project_compile_options()
