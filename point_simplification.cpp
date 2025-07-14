#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/grid_simplify_point_set.h>
#include <CGAL/compute_average_spacing.h>
#include <CGAL/IO/read_points.h>
#include <CGAL/IO/write_points.h>

#include <vector>
#include <fstream>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::Point_3 Point;

int main()
{
  const std::string input_filename = "/home/gurdeep/Desktop/soot_tomography/output/filtered_points.xyz";
 // const std::string input_filename = "/home/gurdeep/Desktop/soot_tomography/output/simplified_points.xyz";

  // Read input points
  std::vector<Point> points;
  if (!CGAL::IO::read_points(input_filename, std::back_inserter(points)))
  {
    std::cerr << "Error: cannot read file " << input_filename << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "Read " << points.size() << " points.\n";

  // Compute average spacing for grid cell size
  double spacing = CGAL::compute_average_spacing<CGAL::Sequential_tag>(points, 6);
  double cell_size = spacing * 1.2;
  unsigned int min_points_per_cell = 3;

  std::cout << "Computed average spacing: " << spacing << std::endl;
  std::cout << "Using cell size: " << cell_size << std::endl;

  // Simplify using grid clustering
  auto it = CGAL::grid_simplify_point_set(
      points, cell_size,
      CGAL::parameters::min_points_per_cell(min_points_per_cell));

  points.erase(it, points.end());
  points.shrink_to_fit();

  std::cout << "Remaining points after simplification: " << points.size() << "\n";

  // Save result
  const std::string output_filename = "/home/gurdeep/Desktop/soot_tomography/output/simplified_points.xyz";
  if (!CGAL::IO::write_points(output_filename, points,
        CGAL::parameters::stream_precision(6)))
  {
    std::cerr << "Error: cannot write output file.\n";
    return EXIT_FAILURE;
  }

  std::cout << "Simplified point set saved to: " << output_filename << "\n";

  return EXIT_SUCCESS;
}
