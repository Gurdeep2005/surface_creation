cmake_minimum_required(VERSION 3.1)
project(soot_point_processing)

# Find CGAL with Core component
find_package(CGAL REQUIRED COMPONENTS Core)
find_package(Eigen3 REQUIRED NO_MODULE)

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
target_link_libraries(estimate_normals CGAL::CGAL CGAL::CGAL_Core Eigen3::Eigen)
target_compile_definitions(estimate_normals PRIVATE CGAL_EIGEN3_ENABLED)
target_compile_features(estimate_normals PRIVATE cxx_std_14)

# === Executable: orient_normals ===
add_executable(orient_normals orient_normals.cpp)
target_link_libraries(orient_normals CGAL::CGAL CGAL::CGAL_Core Eigen3::Eigen)
target_compile_definitions(orient_normals PRIVATE CGAL_EIGEN3_ENABLED)
target_compile_features(orient_normals PRIVATE cxx_std_14)

# === Executable: reconstruction ===
add_executable(reconstruction reconstruction.cpp)
target_link_libraries(reconstruction CGAL::CGAL CGAL::CGAL_Core Eigen3::Eigen)
target_compile_definitions(reconstruction PRIVATE CGAL_EIGEN3_ENABLED)
target_compile_features(reconstruction PRIVATE cxx_std_14)

# === Executable: smoothing ===
add_executable(smoothing smoothing.cpp)
target_link_libraries(smoothing CGAL::CGAL CGAL::CGAL_Core)
target_compile_features(smoothing PRIVATE cxx_std_14)

# === Executable: shrink_wrap ===
add_executable(shrink_wrap shrink_wrap.cpp)
target_link_libraries(shrink_wrap CGAL::CGAL CGAL::CGAL_Core)
target_compile_features(shrink_wrap PRIVATE cxx_std_14)