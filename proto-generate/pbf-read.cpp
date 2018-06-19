#include <iostream>
#include <algorithm>
#include <fstream>
#include <memory>
#include <array>
#include "google-generated/route.pb.h"

// generate a pbf file based on the request:
//    'https://api.mapbox.com/directions/v5/mapbox/driving-traffic/-77.03400313854218,38.899923675122196;-73.99072587490082,40.756567079102425?access_token=pk.eyJ1IjoiaGFwcHlnbyIsImEiOiJjamF2YjR3M3M3MHZvMzNuaXczZmlkem95In0.1HHBIuWNJsipt4g8VDQlMw&geometries=polyline6&steps=true'
int main() {
    using namespace valhalla;

    std::ifstream InputFile("./dcny.route.pbf");
    Directions route;
    route.ParseFromIstream(&InputFile);
    auto desc = route.GetDescriptor();
    std::cout << desc->field_count() << std::endl;
    std::cout << route.waypoints_size() << std::endl;
}
