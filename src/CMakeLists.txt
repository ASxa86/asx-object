project(asx-object)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
	${PROJECT_INCLUDE_DIR}/asx-object/Bytes.h
	${PROJECT_INCLUDE_DIR}/asx-object/Object.h
	${PROJECT_INCLUDE_DIR}/asx-object/String.h
	${PROJECT_INCLUDE_DIR}/asx-object/TypeInfo.h
	${PROJECT_INCLUDE_DIR}/asx-object/TypeTraits.h
)

target_sources(${PROJECT_NAME} PRIVATE
	Bytes.cpp
	Object.cpp
	String.cpp
)

project_install_target()
project_compile_options()
project_gen_export()
