cmake_minimum_required(VERSION 3.1)
set (CMAKE_CXX_STANDARD 17)

project(fieldgen)

list(APPEND CMAKE_MODULE_PATH "./cmake")

find_package(SuiteSparse REQUIRED)

add_executable(fieldgen
        src/Complex.cpp
        src/DenseMatrix.cpp
        src/Edge.cpp
        src/Face.cpp
        src/HalfEdge.cpp
        src/KVecDir.cpp
        src/LinearContext.cpp
        src/Mesh.cpp
        src/MeshIO.cpp
        src/Quaternion.cpp
        src/Real.cpp
        src/SectionIntegrals.cpp
        src/SparseMatrix.cpp
        src/Vector.cpp
        src/Vertex.cpp
        src/commandline.cpp
        )

target_include_directories(fieldgen PUBLIC ./src ./include ${SUITESPARSE_INCLUDE_DIRS})

target_link_libraries(fieldgen ${SUITESPARSE_LIBRARIES})
