#include "json.hpp"
#include "parse.h"
#include <iostream>

using json = nlohmann::json;
int main() {

  std::string stop_name = "Ruskeepää";
  std::vector<StopPoint> stop_points;

  get_stop_point_short_name(stop_name, stop_points);
  std::cout << "Print times" << std::endl;
  print_departure_times(stop_points, 26);
}
