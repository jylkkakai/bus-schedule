#ifndef PARSE_H_
#define PARSE_H_

#include "json.hpp"
#include <string>

struct StopPoint {
  std::string name;
  std::string short_name;
};
struct Line {

  std::string name;
  std::string description;
};

using json = nlohmann::json;

// bool object_has(json obj, std::string key, std::string value);
json get_data(const std::string url);
// void parse_stop_points(const std::string stop_name,
//                        std::vector<StopPoint> &stop_points);
void get_stop_point_short_name(std::string stop_name,
                               std::vector<StopPoint> &stop_points);
void get_stop_point_name(std::vector<StopPoint> &stop_points);
void get_line(std::string url, Line &line);
// void parse_routes(const std::string stop_points,
//                   std::vector<std::string> &routes);
// void parse_lines(const std::string stop_points,
//                  std::vector<std::string> &lines);
// void parse_journeys(const std::string stop_points,
//                     std::vector<std::string> &journeys);
// void parse_journey_patternd(const std::string stop_points,
//                             std::vector<std::string> &journey_patterns);
void print_departure_times(std::vector<StopPoint> &stop_points, int n);

void print_keys(json j);
#endif // PARSE_H_
