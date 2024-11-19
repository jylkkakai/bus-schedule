#include "json.hpp"
#include "parse.h"
#include <cctype>
#include <iostream>

using json = nlohmann::json;
int main(int argc, char *argv[]) {

  std::vector<StopPoint> stop_points;

  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " [option] [param]" << std::endl;
    return 0;
  }
  if (!strcmp(argv[1], "-s")) {
    if (argc < 3) {
      std::cout << "Usage: " << argv[0] << " " << argv[1] << " [param]"
                << std::endl;
      return 0;
    }
    int n = 5;
    if (argc > 3 && isdigit(argv[3][0])) {
      n = std::stoi(argv[3]);
    }
    get_stop_point_short_name(argv[2], stop_points);
    print_departure_times(stop_points, n);

  } else if (!strcmp(argv[1], "-n")) {

    if (argc < 3) {
      std::cout << "Usage: " << argv[0] << " " << argv[1] << " [param]"
                << std::endl;
      return 0;
    }
    StopPoint stop;
    stop.short_name = argv[2];
    stop_points.push_back(stop);
    int n = 5;
    if (argc > 3 && isdigit(argv[3][0])) {
      n = std::stoi(argv[3]);
    }
    print_departure_times(stop_points, n);

  } else {
    std::cout << "Unknown option " << argv[1] << std::endl;
  }
}
