#include "json.hpp"
#include "parse.h"
#include <iostream>

using json = nlohmann::json;
int main() {

  std::string stop_name = "Ruskeepää";
  std::vector<std::string> stop_points;
  std::vector<std::string> lines;
  std::vector<std::string> routes;
  std::vector<std::string> joyrneys;
  std::vector<std::string> joyrney_patterns;

  std::string url =
      "https://data.itsfactory.fi/journeys/api/1/stop-points?name=" + stop_name;
  get_data(url, "shortName", stop_points);

  for (auto el : stop_points)
    std::cout << el << std::endl;
}
