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
void get_data(const std::string url, const std::string key,
              std::vector<std::string> &out_str) {
  try {
    std::string data_str = url_query(url);
    auto stop_points_json = json::parse(data_str);
    if (stop_points_json["body"].empty()) {
      throw std::runtime_error("Data " + key + " not found!\n");
    }
    for (auto el : stop_points_json["body"]) {
      out_str.push_back(el[key]);
    }
  } catch (const std::exception &e) {
    std::cerr << "Failed to parse stop-points: " << e.what() << std::endl;
  }
}
//
// void parse_stop_points(std::string stop_name,
//                        std::vector<std::string> &stop_points) {
//   try {
//     std::string stop_points_str = url_query(
//         "https://data.itsfactory.fi/journeys/api/1/stop-points?name=" +
//         stop_name);
//     // get_data(stop_points_str, "shortName", stop_points);
//     // auto stop_points_json = json::parse(stop_points_str);
//     // if (stop_points_json["body"].empty()) {
//     //   throw std::runtime_error("Stop " + stop_name + " not found!\n");
//     // }
//     // for (auto el : stop_points_json["body"]) {
//     //   stop_points.push_back(el["shortName"]);
//     // }
//   } catch (const std::exception &e) {
//     std::cerr << "Failed to parse stop-points: " << e.what() << std::endl;
//   }
// }
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
