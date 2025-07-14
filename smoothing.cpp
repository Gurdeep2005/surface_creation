#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/Polygon_mesh_processing/tangential_relaxation.h>
#include <CGAL/Polygon_mesh_processing/IO/polygon_mesh_io.h>
 
#include <fstream>
 
typedef CGAL::Exact_predicates_inexact_constructions_kernel   K;
typedef CGAL::Surface_mesh<K::Point_3>                        Mesh;
 
 
namespace PMP = CGAL::Polygon_mesh_processing;
 
 
int main(int argc, char* argv[])
{
  const std::string filename = (argc > 1) ? argv[1] : CGAL::data_file_path("/home/gurdeep/Desktop/soot_tomography/output/surface2.off");
 
  Mesh mesh;
  if(!PMP::IO::read_polygon_mesh(filename, mesh) || !CGAL::is_triangle_mesh(mesh))
  {
    std::cerr << "Invalid input." << std::endl;
    return 1;
  }
 
  unsigned int nb_iter = (argc > 2) ? std::stoi(std::string(argv[2])) : 30;
 
  std::cout << "Relax...";
 
  PMP::tangential_relaxation(mesh, CGAL::parameters::number_of_iterations(nb_iter));
 
  std::cout << "done." << std::endl;

  const std::string output_filename = (argc > 3) ? argv[3] : "/home/gurdeep/Desktop/soot_tomography/output/smooth_surface.off";

  // Use std::ofstream and CGAL's operator<< to write the mesh
  std::ofstream out(output_filename);
  if(!out)
  {
      std::cerr << "Cannot open " << output_filename << " for writing." << std::endl;
      return 1;
  }

  out << mesh;

  std::cout << "Result written to " << output_filename << std::endl;
 
  return 0;
}
