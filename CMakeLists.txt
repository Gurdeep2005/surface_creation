cmake_minimum_required(VERSION 3.1)
project(soot_point_processing)

# Find CGAL with Core component
find_package(CGAL REQUIRED COMPONENTS Core)

# === Executable: remove_outliers ===
add_executable(remove_outliers remove_outliers.cpp)
target_link_libraries(remove_outliers CGAL::CGAL CGAL::CGAL_Core)
target_compile_features(remove_outliers PRIVATE cxx_std_14)

# === Executable: simplify ===
add_executable(point_simplification point_simplification.cpp)
target_link_libraries(point_simplification CGAL::CGAL CGAL::CGAL_Core)
target_compile_features(point_simplification PRIVATE cxx_std_14)

# === Executable: estimate_normals ===
add_executable(estimate_normals estimate_normals.cpp)
target_link_libraries(estimate_normals CGAL::CGAL CGAL::CGAL_Core)
target_compile_features(estimate_normals PRIVATE cxx_std_17)
