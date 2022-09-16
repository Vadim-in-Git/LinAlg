#include "TimeLogger.h"
#include "time_check.h"

int main() {
	START_SESSION
	Profiling::distance_points();
	Profiling::distance_line_point();
	Profiling::distance_segmen_point();
	Profiling::collinear();
	return 0;
}