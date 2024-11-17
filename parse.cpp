#include "parse.h"
#include "query.h"
#include <algorithm>
#include <iostream>
#include <set>

json get_data(const std::string url) {

  try {

    std::string data_str = url_query(url);
    auto data_json = json::parse(data_str);
    if (data_json["body"].empty())
      throw std::runtime_error("get_data(): empty body!\n");

    return data_json["body"];

  } catch (const std::exception &e) {

    std::cerr << "ERROR: parse_stop_points(): " << e.what() << std::endl;
    exit(1);
  }
}

void parse_stop_points(std::string url, std::vector<std::string> &stop_points) {

  std::string key = "shortName";

  auto data_json = get_data(url);
  for (auto el : data_json) {
    stop_points.push_back(el[key]);
  }
}

void print_keys(json j) {
  for (auto &[key, val] : j.items()) {
    std::cout << key << std::endl;
  }
}

void print_departure_times(std::vector<std::string> stop_points, int n) {
  std::string journeys_url =
      "https://data.itsfactory.fi/journeys/api/1/journeys?stopPointId=";
  std::set<std::string> times;
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
    std::advance(its, std::min(int(times.size()), n));
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
