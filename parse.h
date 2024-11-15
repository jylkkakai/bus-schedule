#ifndef PARSE_H_
#define PARSE_H_

#include "json.hpp"
#include <string>

using json = nlohmann::json;

bool object_has(json obj, std::string key, std::string value);
json get_data(const std::string url);
void parse_stop_points(const std::string stop_name,
                       std::vector<std::string> &stop_points);
void parse_routes(const std::string stop_points,
                  std::vector<std::string> &routes);
void parse_lines(const std::string stop_points,
                 std::vector<std::string> &lines);
void parse_journeys(const std::string stop_points,
                    std::vector<std::string> &journeys);
void parse_journey_patternd(const std::string stop_points,
                            std::vector<std::string> &journey_patterns);

#endif // PARSE_H_
