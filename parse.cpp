#include "parse.h"
#include "query.h"
#include <iostream>

// bool object_has(json obj, std::string key, std::string value) {
//
//   // std::cout << obj.size() << std::endl;
//   for (auto &[k, v] : obj.items()) {
//     // std::cout << k << std::endl;
//     // std::cout << v << std::endl;
//     // std::cout << v["shortName"].dump() << value << std::endl;
//     if (v[key].dump() == value)
//       return true;
//     // break;
//   }
//   return false;
// }
json get_data(const std::string url) {

  std::string data_str = url_query(url);
  auto data_json = json::parse(data_str);
  if (data_json["body"].empty())
    throw std::runtime_error("get_data(): empty body!\n");

  return data_json["body"];
}

void parse_stop_points(std::string url, std::vector<std::string> &stop_points) {
  try {

    std::string key = "shortName";

    auto data_json = get_data(url);
    for (auto el : data_json) {
      stop_points.push_back(el[key]);
    }
  } catch (const std::exception &e) {
    std::cerr << "ERROR: parse_stop_points(): " << e.what() << std::endl;
  }
}
// void parse_routes(const std::vector<std::string> stop_points,
//                   std::vector<std::string> &routes) {
//   try {
//     for (auto el : stop_points) {
//       std::string routes_str = url_query(
//           "https://data.itsfactory.fi/journeys/api/1/stop-points?name=" +
//           el);
//       auto routes_json = json::parse(routes_str);
//       if (routes_json["body"].empty()) {
//         throw std::runtime_error("Stop " + el + " not found!\n");
//       }
//       for (auto el : routes_json["body"]) {
//         routes.push_back(el["shortName"]);
//       }
//     }
//
//   } catch (const std::exception &e) {
//
//     std::cerr << "Failed to parse stop-points: " << e.what() << std::endl;
//   }
// }
// void parse_lines(const std::string stop_points,
//                  std::vector<std::string> &lines) {}
// void parse_journeys(const std::string stop_points,
//                     std::vector<std::string> &journeys) {}
// void parse_journey_patternd(const std::string stop_points,
//                             std::vector<std::string> &journey_patterns) {}
