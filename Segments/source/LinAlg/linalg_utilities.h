#pragma once
#include "linalg.h"

namespace LinAlg {

	// �������� �� ��������� ��������
	inline bool is_equal(value_t val1, value_t val2) noexcept;

	// ��������� ������������
	inline value_t inner_product(const Vector& v1, const Vector& v2) noexcept {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	// ��������� ������������
	inline Vector cross_product(const Vector& v1, const Vector& v2) noexcept {
		return { v1.y * v2.z - v1.z * v2.y, -v1.x * v2.z + v1.z * v2.x, v1.x * v2.y - v1.y * v2.x };
	}

	// ��������� ����� �������
	value_t norm(const Vector& vec) noexcept;

	// ��������� ������
	Vector unit(Vector vec) noexcept;

	// ����������� �� ������
	bool is_collinear(const Line& l1, const Line& l2) noexcept;

	// ��������� �� �����
	bool is_same(const Point& p1, const Point& p2) noexcept;

	// ����� �� ����� ������ ������
	bool is_in(const Point& point, const Line& line) noexcept;

	// ��������� �� �����
	bool is_same(const Line& line1, const Line& line2) noexcept;

	// ����� �� ����� ������ �������
	bool is_in(const Point& point, const Segment& seg) noexcept;

	// ��������� ����� �� ����� line � ����� point
	Point closest_point(const Line& line, const Point& point) noexcept;

	// ���������� ����� �������
	value_t distance(const Point& p1, const Point& p2) noexcept;

	// ���������� ����� ������ � ������
	value_t distance(const Line& line, const Point& point) noexcept;
	inline value_t distance(const Point& point, const Line& line) noexcept { distance(line, point); }

	// ���������� ����� ������ � ��������
	value_t distance(const Segment& seg, const Point& point) noexcept;
	inline value_t distance(const Point& point, const Segment& seg) noexcept { distance(seg, point); }

}