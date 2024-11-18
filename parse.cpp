#include "parse.h"
#include "query.h"
#include <algorithm>
#include <iostream>
#include <map>

json get_data(const std::string url) {

  try {

    std::string data_str = url_query(url);
    auto data_json = json::parse(data_str);
    if (data_json["body"].empty())
      throw std::runtime_error("get_data(): empty body!\n");

    return data_json["body"];

  } catch (const std::exception &e) {

    std::cerr << "ERROR: Failed to get " + url + ": " << e.what() << std::endl;
    exit(1);
  }
}

void get_stop_point_short_name(std::string stop_name,
                               std::vector<StopPoint> &stop_points) {

  std::string short_name = "shortName";

  auto data_json =
      get_data("https://data.itsfactory.fi/journeys/api/1/stop-points?name=" +
               stop_name);
  for (auto el : data_json) {
    StopPoint stop_point;
    stop_point.short_name = el[short_name];
    stop_points.push_back(stop_point);
  }
}

void get_stop_point_name(std::vector<StopPoint> &stop_points) {

  std::string name = "name";

  for (auto &stop : stop_points) {
    auto data_json = get_data(
        "https://data.itsfactory.fi/journeys/api/1/stop-points?shortName=" +
        stop.short_name);
    stop.name = data_json[0]["name"];
  }
}
void get_line(std::string url, Line &line) {

  // std::string short_name = "shortName";

  auto data_json = get_data(url);
  // std::cout << .dump(4);
  line.description = data_json[0]["description"];
  line.name = data_json[0]["name"];
}

void print_keys(json j) {
  for (auto &[key, val] : j.items()) {
    std::cout << key << std::endl;
  }
}

void print_departure_times(std::vector<StopPoint> &stop_points, int n) {

  get_stop_point_name(stop_points);

  std::string journeys_url =
      "https://data.itsfactory.fi/journeys/api/1/journeys?stopPointId=";
  std::map<std::string, Line> times;
  for (auto sp : stop_points) {
    auto journeys = get_data(journeys_url + sp.short_name + "&dayTypes=friday");

    // print_keys(journeys[0]);
    // std::cout << journeys["lineUrl"] << std::endl;
    std::cout << "Stop: \t" + sp.short_name + " " + sp.name << std::endl;
    // std::cout << "Line: \t" + sp.line_name + " " + sp.line_description
    // << std::endl;

    for (auto journey : journeys) {
      // if (/*journey["dayTypes"][0] == "monday" ||*/
      //     journey["dayTypes"][0] == "friday") {
      Line line;
      get_line(journey["lineUrl"], line);
      for (auto call : journey["calls"]) {

        if (call["stopPoint"]["shortName"] == sp.short_name /*&&
              call["departureTime"] > "13:00:00"*/) {
          times.insert({call["departureTime"], line});
        }
      }
      // }
    }
    auto its = times.begin();
    std::advance(its, std::min(int(times.size()), n));
    for (auto it = times.begin(); it != its; it++) {
      std::cout << "\t" + it->first + " " + it->second.name + " " +
                       it->second.description
                << std::endl;
    }
    times.clear();
  }
}
