project(asx-node)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
	${PROJECT_INCLUDE_DIR}/asx-node/NodeAbstract.h
	${PROJECT_INCLUDE_DIR}/asx-node/Node.h
	${PROJECT_INCLUDE_DIR}/asx-node/VisitorAbstract.h
	${PROJECT_INCLUDE_DIR}/asx-node/VisitorSerialize.h
)

target_sources(${PROJECT_NAME} PRIVATE
	Node.cpp
	VisitorSerialize.cpp
)

project_install_target()
project_compile_options()
project_gen_export()
