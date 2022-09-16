#include"linalg_utilities.h"

#include <cmath>
#include <algorithm>
#include <limits>

namespace LinAlg {

	static value_t EPS = std::numeric_limits<value_t>::epsilon();

	inline bool is_equal(value_t val1, value_t val2) noexcept {
		return std::abs(val1 - val2) < EPS;
	}

	value_t norm(const Vector& vec) noexcept {
		return sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
	}

	Vector unit(Vector vec) noexcept {
		auto val = norm(vec);
		vec.x /= val;
		vec.y /= val;
		vec.z /= val;
		return vec;
	}

	bool is_collinear(const Line& l1, const Line& l2) noexcept {
		return is_equal(norm(cross_product(l1.get_direction(), l2.get_direction())), 0);
	};

	bool is_same(const Point& p1, const Point& p2) noexcept {
		return is_equal(p1.x, p2.x) && is_equal(p1.y, p2.y) && is_equal(p1.z, p2.z);
	}

	bool is_in(const Point& point, const Line& line) noexcept {
		Line line_to_point(line.get_point(), point);
		return is_collinear(line, line_to_point);
	}

	bool is_same(const Line& line1, const Line& line2) noexcept {
		return is_in(line1.get_point(), line2) && is_collinear(line1, line2);
	}

	bool is_in(const Point& point, const Segment& seg) noexcept {
		if (!is_in(point, Line{ seg })) return false;
		const Point& p1 = seg.get_p1();
		const Point& p2 = seg.get_p2();
		if (std::min(p1.x, p2.x) < point.x && point.x < std::max(p1.x, p2.x)) return true;
		if (std::min(p1.y, p2.y) < point.y && point.y < std::max(p1.y, p2.y)) return true;
		if (std::min(p1.z, p2.z) < point.z && point.z < std::max(p1.z, p2.z)) return true;
		return false;
	}

	Point closest_point(const Line& line, const Point& point) noexcept {
		Vector vec{ line.get_point(), point };
		Vector unit_vec = unit(line.get_direction());
		Vector proj = unit_vec * inner_product(unit_vec, vec);
		const Point& line_p = line.get_point();
		return { line_p.x + proj.x, line_p.y + proj.y, line_p.z + proj.z };
	}

	value_t distance(const Point& p1, const Point& p2) noexcept {
		if (is_same(p1, p2)) return 0;
		return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
	}

	value_t distance(const Line& line, const Point& point) noexcept {
		if (is_in(point, line)) return 0;
		Point closest = closest_point(line, point);
		return distance(closest, point);
	}

	value_t distance(const Segment& seg, const Point& point) noexcept {
		if (is_in(point, seg)) return 0;
		Vector vec{ seg.get_p1(), point };
		Vector unit_vec = unit(Vector{ seg.get_p1(), seg.get_p2() });
		value_t proj = inner_product(unit_vec, vec);
		if (proj < 0)
			return distance(seg.get_p1(), point);
		if (proj > norm(Vector{ seg.get_p1(), seg.get_p2() }))
			return distance(seg.get_p2(), point);
		Vector proj_vec = unit_vec * proj;
		const Point& line_p = seg.get_p1();
		Point closest{ line_p.x + proj_vec.x, line_p.y + proj_vec.y, line_p.z + proj_vec.z };
		return distance(closest, point);
	}

}