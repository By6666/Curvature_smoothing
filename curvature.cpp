#include "include/data_type.h"

void calcTrajectoryCurvature(MPCTrajectory &traj,
                             int curvature_smoothing_num) {  //计算路径点的曲率
  unsigned int traj_k_size = traj.size();
  // traj.k.clear();
  /* calculate curvature by circle fitting from three points 通过三个点求曲率*/
  data_type p1, p2, p3;
  //三个点之间的间隔是curvature_smoothing_num，即求得是第curvature_smoothing_num个点～倒数第curvature_smoothing_num个点的曲率，
  //前curvature_smoothing_num个点都和第一个点的曲率相同，最后curvature_smoothing_num个点的曲率和最后一个点相同
  for (unsigned int i = curvature_smoothing_num;
       i < traj_k_size - curvature_smoothing_num; ++i) {
    p1.x = traj[i - curvature_smoothing_num].x;
    p1.y = traj[i - curvature_smoothing_num].y;

    p2.x = traj[i].x;
    p2.y = traj[i].y;

    p3.x = traj[i + curvature_smoothing_num].x;
    p3.y = traj[i + curvature_smoothing_num].y;

    double den = std::max(
        find_distence(p1, p2) * find_distence(p2, p3) * find_distence(p3, p1),
        0.0001);
    const double curvature =
        2.0 * ((p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x)) /
        den;
    //计算曲率的三点公式？？
    traj[i].k = curvature;
  }
  /* first and last curvature is copied from next value */
  for (int i = 0; i < curvature_smoothing_num; ++i) {
    traj[i].k = traj[curvature_smoothing_num].k;
    traj[traj_k_size - i - 1].k =
        traj[traj_k_size - curvature_smoothing_num - 1].k;
  }
}

// void MPCUtils::calcTrajectoryCurvature(
//     MPCTrajectory &traj,
//     int curvature_smoothing_num) {  //计算路径点的曲率  unsigned int
//                                     // traj_k_size = traj.x.size();
//                                     // traj.k.clear();
//   /* calculate curvature by circle fitting from three points
//    * 通过三个点求曲率*/
//   geometry_msgs::Point p1, p2,
//       p3;
//       //三个点之间的间隔是curvature_smoothing_num，即求得是第curvature_smoothing_num个点～倒数第curvature_smoothing_num个点的曲率，
//            ////前curvature_smoothing_num个点都和第一个点的曲率相同，最后curvature_smoothing_num个点的曲率和最后一个点相同
//            // for (unsigned int i = curvature_smoothing_num; i < traj_k_size
//            -
//            // curvature_smoothing_num; ++i)  {    p1.x = traj.x[i -
//            // curvature_smoothing_num];    p2.x = traj.x[i];    p3.x =
//            // traj.x[i + curvature_smoothing_num];    p1.y = traj.y[i -
//            // curvature_smoothing_num];    p2.y = traj.y[i];    p3.y =
//            // traj.y[i + curvature_smoothing_num];    double den =
//            // std::max(amathutils::find_distance(p1, p2) *
//            // amathutils::find_distance(p2, p3) *
//            // amathutils::find_distance(p3, p1), 0.0001);    const double
//            // curvature = 2.0 * ((p2.x - p1.x) * (p3.y - p1.y) - (p2.y -
//            p1.y)
//            //* (p3.x - p1.x)) / den;
//            ////计算曲率的三点公式？？    traj.k.push_back(curvature);  }
//   /* first and last curvature is copied from next value */
//   for (int i = 0; i < curvature_smoothing_num; ++i) {
//     traj.k.insert(traj.k.begin(), traj.k.front());
//     traj.k.push_back(traj.k.back());
//   }
// }