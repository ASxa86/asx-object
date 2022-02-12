project(test-asx-object)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
	Bytes.test.cpp
	Object.test.cpp
	String.test.cpp
	TypeInfo.test.cpp
	TypeTraits.test.cpp
)

find_package(GTest CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
	asx-object
	GTest::gtest_main
	GTest::gtest
)

project_install_target()
project_compile_options()
