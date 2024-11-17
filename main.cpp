#include "json.hpp"
#include "parse.h"
#include <iostream>
// #include <iterator>
#include <set>

using json = nlohmann::json;
int main() {

  std::string stop_name = "Ruskeepää";
  std::vector<std::string> stop_points;
  std::vector<std::string> lines;
  std::vector<std::string> routes;
  std::vector<std::string> joyrneys;
  std::vector<std::string> joyrney_patterns;
  std::set<std::string> times;

  std::string stop_url =
      "https://data.itsfactory.fi/journeys/api/1/stop-points?name=" + stop_name;
  std::string routes_url =
      "https://data.itsfactory.fi/journeys/api/1/routes?stopId=";
  std::string journeys_url =
      "https://data.itsfactory.fi/journeys/api/1/journeys?stopPointId=";
  parse_stop_points(stop_url, stop_points);
  for (auto sp : stop_points) {
    auto journeys = get_data(journeys_url + sp); // + "&dayTypes=sunday");

    std::cout << sp + " Ruskeepaa" << std::endl;
    std::cout << "73B" << std::endl;
    for (auto journey : journeys) {
      // std::cout << journey["calls"].size() << std::endl;
      // print_keys(journey);
      if (journey["dayTypes"][0] == "sunday") {
        // std::cout << journey["dayTypes"] << std::endl;
        // break;
        for (auto call : journey["calls"]) {

          if (call["stopPoint"]["shortName"] == sp &&
              call["departureTime"] > "15:00:00") {
            times.insert(call["departureTime"]);
            // std::cout << call["departureTime"] << std::endl;
          }
        }
      }
    }
    auto its = times.begin();
    std::advance(its, 5);
    for (auto it = times.begin(); it != its; it++) {
      std::cout << "\t" << *it << std::endl;
    }
    times.clear();
    // print_keys(json[0]);

    // for (auto call : json["call"]) {
    // std::cout << json[0]["calls"].dump(4) << std::endl;
    std::cout << journeys.size() << std::endl;
  }
}
