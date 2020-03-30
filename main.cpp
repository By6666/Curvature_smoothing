#include "include/data_type.h"
#include "include/matplotlibcpp.h"

// code cmd
// g++ main.cpp curvature.cpp -std=c++11 -I/usr/include/python2.7 -lpython2.7

const char *file_path = "data.csv";

int main() {
  MPCTrajectory data_stg;
  FILE *File = fopen(file_path, "r");

  if (!File) {
    std::cout << "** file open fail !! **" << std::endl;
    return 0;
  }

  double x = 0.0, y = 0.0, yaw = 0.0;
  while (!feof(File)) {
    int read_result = fscanf(File, (const char *)"%lf %lf %lf", &x, &y, &yaw);
    if (read_result != 3) {
      std::cout << "** Read line fail !!! **" << std::endl;
    } else {
      data_stg.emplace_back(x, y, yaw);
    }
  }
  fclose(File);
  std::cout << "** Read data sucessful !!! **" << std::endl;

  //   for (auto elem : data_stg) {
  //     std::cout << elem.x << "  " << elem.y << "  " << elem.yaw << std::endl;
  //   }
  int curvature_smoothing_num = 0;
  while (true) {
    std::cout << "Please input curvature_smoothing_num: ";
    std::cin >> curvature_smoothing_num;

    calcTrajectoryCurvature(data_stg, curvature_smoothing_num);

    std::vector<double> curvature_data;
    curvature_data.reserve(data_stg.size());
    std::cout << "*************curvature************" << std::endl;
    for (auto elem : data_stg) {
      std::cout << elem.k << std::endl;
      curvature_data.push_back(elem.k);
    }

    matplotlibcpp::plot(curvature_data);
    matplotlibcpp::grid(true);
    matplotlibcpp::show();
  }

  return 0;
}