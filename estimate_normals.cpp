#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/IO/read_xyz_points.h>
#include <CGAL/IO/write_xyz_points.h>
#include <CGAL/jet_estimate_normals.h>
#include <CGAL/property_map.h>
#include <CGAL/Named_function_parameters.h>

#include <vector>
#include <utility>
#include <fstream>
#include <iostream>

// Kernel and types
typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::Point_3 Point;
typedef Kernel::Vector_3 Vector;
typedef std::pair<Point, Vector> PointVectorPair;

typedef CGAL::Parallel_if_available_tag Concurrency_tag;

int main(int argc, char* argv[])
{
 // const std::string input_filename  = (argc > 1) ? argv[1] : "/home/gurdeep/Desktop/soot_tomography/output/simplified_points.xyz";
    const std::string input_filename  = (argc > 1) ? argv[1] : "/home/gurdeep/Desktop/soot_tomography/output/filtered_points.xyz";
    const std::string output_filename = (argc > 2) ? argv[2] : "/home/gurdeep/Desktop/soot_tomography/output/points_with_normals.xyz";

  // Read input points
  std::vector<PointVectorPair> points;
  if (!CGAL::IO::read_XYZ(input_filename,
                          std::back_inserter(points),
                          CGAL::parameters::point_map(CGAL::First_of_pair_property_map<PointVectorPair>())
                                           .normal_map(CGAL::Second_of_pair_property_map<PointVectorPair>())))
  {
    std::cerr << "Error: cannot read file " << input_filename << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "Read " << points.size() << " points.\n";

  // Estimate normals
  const unsigned int nb_neighbors = 18;
  CGAL::jet_estimate_normals<Concurrency_tag>(
      points, nb_neighbors,
      CGAL::parameters::point_map(CGAL::First_of_pair_property_map<PointVectorPair>())
          .normal_map(CGAL::Second_of_pair_property_map<PointVectorPair>())
    );

  // Write output
  if (!CGAL::IO::write_XYZ(output_filename, points,
                           CGAL::parameters::point_map(CGAL::First_of_pair_property_map<PointVectorPair>())
                                            .normal_map(CGAL::Second_of_pair_property_map<PointVectorPair>())
                                            .stream_precision(17)))
  {
    std::cerr << "Error writing to " << output_filename << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "Wrote normals to " << output_filename << std::endl;

  return EXIT_SUCCESS;
}
