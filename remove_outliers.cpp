#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/property_map.h>
#include <CGAL/compute_average_spacing.h>
#include <CGAL/remove_outliers.h>
#include <CGAL/IO/read_points.h>

#include <vector>
#include <fstream>
#include <iostream>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::Point_3 Point;

int main(int argc, char* argv[])
{
    // Set your filename here or pass it as argument
    const std::string fname = (argc > 1) ? argv[1] : "/home/gurdeep/Desktop/soot_tomography/output/model.xyz";

    std::vector<Point> points;

    // Read points from file
    if (!CGAL::IO::read_points(fname, std::back_inserter(points),
                              CGAL::parameters::point_map(CGAL::Identity_property_map<Point>())))
    {
        std::cerr << "Error: cannot read file " << fname << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Loaded " << points.size() << " points from file." << std::endl;

    // Number of neighbors for outlier removal
    const int nb_neighbors = 24;

    // Compute average spacing (scale estimate)
    const double average_spacing = CGAL::compute_average_spacing<CGAL::Sequential_tag>(points, nb_neighbors);
    std::cout << "Average spacing: " << average_spacing << std::endl;

    // Remove outliers by distance threshold (e.g., points farther than 2 * average spacing)
    auto first_to_remove = CGAL::remove_outliers<CGAL::Parallel_if_available_tag>(
        points,
        nb_neighbors,
        CGAL::parameters::threshold_percent(100.0)  // no limit on % points to remove
                         .threshold_distance(2.0 * average_spacing)
    );

    std::cout << (100.0 * std::distance(first_to_remove, points.end()) / points.size())
              << "% of points are considered outliers and will be removed." << std::endl;

    // Erase outliers from vector
    points.erase(first_to_remove, points.end());

    // Optional: shrink vector capacity
    std::vector<Point>(points).swap(points);

    std::cout << "Remaining points after outlier removal: " << points.size() << std::endl;

    // You can write the filtered points back to disk if you want:
    std::ofstream out("filtered_points.xyz");
    for (const auto& p : points)
    {
        out << p << "\n";
    }
    out.close();

    return EXIT_SUCCESS;
}
