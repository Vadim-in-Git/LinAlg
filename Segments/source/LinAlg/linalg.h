#pragma once

namespace LinAlg {

	using value_t = double;

	struct Point { value_t x=0, y=0, z=0; };

	class Segment {
	public:
		Segment(const Point& p1, const Point& p2) : m_p1(p1), m_p2(p2) {}
		const Point& get_p1() const noexcept { return m_p1; }
		const Point& get_p2() const noexcept { return m_p2; }
	private:
		Point m_p1, m_p2;
	};

	struct Vector {
		Vector(value_t xx, value_t yy, value_t zz)
			: x(xx), y(yy), z(zz) {}
		Vector(const Point& p1, const Point& p2)
			: x(p2.x - p1.x), y(p2.y - p1.y), z(p2.z - p1.z) {}
		value_t x, y, z;
	};

	inline Vector operator * (const Vector& vec, value_t value) {
		return { vec.x * value, vec.y * value, vec.z * value };
	}
	inline Vector operator * (value_t value, const Vector& vec) {
		return vec * value;
	}

	class Line {
	public:
		Line(const Point& p1, const Point& p2)
			: m_point(p1), m_direction(p1, p2) {}
		Line(const Segment& segm)
			: m_point(segm.get_p1()), m_direction(segm.get_p1(), segm.get_p2()) {}
		const Point& get_point() const noexcept { return m_point; }
		const Vector& get_direction() const noexcept { return m_direction; }
	private:
		Point m_point;
		Vector m_direction;
	};

} // LinAlg