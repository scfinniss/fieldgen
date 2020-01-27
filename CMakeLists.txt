cmake_minimum_required(VERSION 3.1)
set (CMAKE_CXX_STANDARD 17)

project(fieldgen)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(SuiteSparse REQUIRED)

add_executable(fieldgen
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Complex.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/DenseMatrix.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Edge.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Face.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/HalfEdge.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/KVecDir.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/LinearContext.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Mesh.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/MeshIO.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Quaternion.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Real.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/SectionIntegrals.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/SparseMatrix.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Vector.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Vertex.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/commandline.cpp
        )

target_include_directories(fieldgen PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/src 
	${CMAKE_CURRENT_SOURCE_DIR}/include 
	${SUITESPARSE_INCLUDE_DIRS})

target_link_libraries(fieldgen ${SUITESPARSE_LIBRARIES})

