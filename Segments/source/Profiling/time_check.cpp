#include "time_check.h"
#include "TimeLogger.h"
#include "linalg_utilities.h"

namespace Profiling {
	void distance_points(size_t n) noexcept {
		volatile LinAlg::value_t result;
		LinAlg::Point p1{ 0,0,0 }, p2{ 1,2,2 };
		PROFILE_FUNCTION
		for (size_t i = 0; i < n; ++i)
			result = LinAlg::distance(p1, p2);
	}
	
	void distance_line_point(size_t n) noexcept {
		volatile LinAlg::value_t result;
		LinAlg::Point p1{ 0, 0, 0 }, p2{ 1,0,0 }, p3{ -3, 4, 0 };
		LinAlg::Line line(p1, p2);
		PROFILE_FUNCTION
		for (size_t i = 0; i < n; ++i)
			result = LinAlg::distance(line, p3);
	}

	void distance_segmen_point(size_t n) noexcept {
		volatile LinAlg::value_t result;
		LinAlg::Point p1{ 0, 0, 0 }, p2{ 1,0,0 }, p3{ -3, 4, 0 };
		LinAlg::Segment segment(p1, p2);
		PROFILE_FUNCTION
		for (size_t i = 0; i < n; ++i)
			result = LinAlg::distance(segment, p3);
	}

	void collinear(size_t n) noexcept {
		volatile LinAlg::value_t result;
		LinAlg::Point p1{ 0, 0, 0 }, p2{ 1,0,1 };
		LinAlg::Point p3{ 0,1,0 }, p4{ 1,1,1 };
		LinAlg::Segment s1(p1, p2), s2(p3, p4);
		PROFILE_FUNCTION
		for (size_t i = 0; i < n; ++i)
			result = LinAlg::is_collinear(s1, s2);
	}
}
