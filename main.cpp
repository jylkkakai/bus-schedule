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

  std::string stop_url =
      "https://data.itsfactory.fi/journeys/api/1/stop-points?name=" + stop_name;
  std::string routes_url =
      "https://data.itsfactory.fi/journeys/api/1/routes?stopId=";
  std::string journey_pattern_url =
      "https://data.itsfactory.fi/journeys/api/1/journey-patterns?stopPointId=";
  auto json = get_data(stop_url);
  std::cout << json.dump(4) << std::endl;
  parse_stop_points(stop_url, stop_points);
  for (auto el : stop_points) {
    auto json = get_data(journey_pattern_url + el);
    for (auto &[key, val] : json[0].items()) {
      std::cout << key << std::endl;
    }
    std::cout << el << std::endl;
    // std::cout << routes_url + el << std::endl;
  }
}
