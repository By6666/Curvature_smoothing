#ifndef DATA_TYPE_H
#define DATA_TYPE_H

#include <iostream>
#include <vector>
#include <algorithm>

struct data_type {
  double x;
  double y;
  double yaw;
  double k;

  data_type(double x_, double y_, double yaw_)
      : x(x_), y(y_), yaw(yaw_), k(0.0) {}
  data_type() = default;
};

typedef std::vector<data_type> MPCTrajectory;

void calcTrajectoryCurvature(MPCTrajectory &traj, int curvature_smoothing_num);

inline double find_distence(const data_type& p1,const data_type& p2){
    return std::hypot(p1.x - p2.x, p1.y - p2.y);
}

#endif