#include "parse.h"
#include "query.h"
#include <algorithm>
#include <ctime>
#include <iostream>
#include <map>
#include <string>

json get_data(const std::string url) {

  try {

    std::string data_str = url_query(url);
    auto data_json = json::parse(data_str);

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
  if (data_json.empty()) {
    std::cout << "Failed to find stop " << stop_name << "!" << std::endl;
    exit(0);
  }
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
    if (data_json.empty()) {
      std::cout << "Failed to find stop " << stop.short_name << "!"
                << std::endl;
      exit(0);
    }
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

  DayTime datetime = get_time();
  std::string query_day;
  if (datetime.day == "Sun")
    query_day = "sunday";
  else if (datetime.day == "Sat")
    query_day = "saturday";
  else
    query_day = "friday";
  get_stop_point_name(stop_points);

  std::string journeys_url =
      "https://data.itsfactory.fi/journeys/api/1/journeys?stopPointId=";
  std::map<std::string, Line> times;
  for (auto sp : stop_points) {
    auto journeys =
        get_data(journeys_url + sp.short_name + "&dayTypes=" + query_day);

    std::cout << "Stop: \t" + sp.short_name + " " + sp.name << std::endl;

    for (auto journey : journeys) {
      Line line;
      get_line(journey["lineUrl"], line);
      for (auto call : journey["calls"]) {

        if (call["stopPoint"]["shortName"] == sp.short_name &&
            call["departureTime"] > datetime.time) {
          times.insert({call["departureTime"], line});
        }
      }
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

DayTime get_time() {

  DayTime date;
  const auto now = std::time(nullptr);

  std::string datetime(100, 0);
  datetime.resize(std::strftime(&datetime[0], datetime.size(), "%a %T",
                                std::localtime(&now)));
  int delim_pos = datetime.find(' ');
  return {datetime.substr(0, delim_pos),
          datetime.substr(delim_pos + 1, datetime.length() - delim_pos)};
}
