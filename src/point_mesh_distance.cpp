#include "point_mesh_distance.h"

void point_mesh_distance(
  const Eigen::MatrixXd & X,
  const Eigen::MatrixXd & VY,
  const Eigen::MatrixXi & FY,
  Eigen::VectorXd & D,
  Eigen::MatrixXd & P,
  Eigen::MatrixXd & N)
{
  // Replace with your code
  int n = X.rows();
  P.resizeLike(X);
  N.resizeLike(X);
  D.resize(n);

  Eigen::MatrixXd PFN;
  igl::per_face_normals(VY, FY, Eigen::Vector3d(1,1,1).normalized(), PFN);
  // loop through every point
  for(int i = 0;i<X.rows();i++){
    double min_d = -1;
    int min_f_idx = 0;
    Eigen::RowVector3d closest_p;
    // loop through every face, finding the min p and d for that face
    // choose the minimum d and corresponding p and set
    for(int f =0; f < FY.rows(); f++){
      double d;
      Eigen::RowVector3d p;

      Eigen::RowVector3d a = VY.row(FY(f, 0));
      Eigen::RowVector3d b = VY.row(FY(f, 1));
      Eigen::RowVector3d c = VY.row(FY(f, 2));
      point_triangle_distance(X.row(i), a,b,c, d, p);
      if(min_d == -1 || d < min_d){
        min_d = d;
        closest_p = p;
        min_f_idx = f;
      }
    }
    P.row(i) = closest_p;
    D(i) = min_d;
    N.row(i) = PFN.row(min_f_idx);
  }
}
