#include <CGAL/Simple_cartesian.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/Polygon_mesh_processing/shape_smoothing.h>
#include <fstream>

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_3 Point;
typedef CGAL::Surface_mesh<Point> Mesh;
namespace PMP = CGAL::Polygon_mesh_processing;

int main() {
    Mesh mesh;
    std::ifstream input("/home/gurdeep/Desktop/soot_tomography/output/surface.off");
    input >> mesh;

    PMP::tangential_relaxation(mesh,
        CGAL::parameters::number_of_iterations(10)
                        .weight_calculator(PMP::Uniform_weight<Mesh>()));

    std::ofstream output("/home/gurdeep/Desktop/soot_tomography/output/smoothed.off");
    output << mesh;
    return 0;
}
