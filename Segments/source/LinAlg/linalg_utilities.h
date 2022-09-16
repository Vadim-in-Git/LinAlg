#pragma once
#include "linalg.h"

namespace LinAlg {

	// ѕроверка на равенство значений
	inline bool is_equal(value_t val1, value_t val2) noexcept;

	// —кал€рное произведение
	inline value_t inner_product(const Vector& v1, const Vector& v2) noexcept {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	// ¬екторное произведение
	inline Vector cross_product(const Vector& v1, const Vector& v2) noexcept {
		return { v1.y * v2.z - v1.z * v2.y, -v1.x * v2.z + v1.z * v2.x, v1.x * v2.y - v1.y * v2.x };
	}

	// ≈вклидова норма вектора
	value_t norm(const Vector& vec) noexcept;

	// ≈диничный вектор
	Vector unit(Vector vec) noexcept;

	// коллиниарны ли пр€мые
	bool is_collinear(const Line& l1, const Line& l2) noexcept;

	// совпадают ли точки
	bool is_same(const Point& p1, const Point& p2) noexcept;

	// лежит ли точка внутри пр€мой
	bool is_in(const Point& point, const Line& line) noexcept;

	// совпадают ли линии
	bool is_same(const Line& line1, const Line& line2) noexcept;

	// лежит ли точка внутри отрезка
	bool is_in(const Point& point, const Segment& seg) noexcept;

	// Ѕлижайша€ точка на линии line к точке point
	Point closest_point(const Line& line, const Point& point) noexcept;

	// –ассто€ние между точками
	value_t distance(const Point& p1, const Point& p2) noexcept;

	// –ассто€ние между точкой и пр€мой
	value_t distance(const Line& line, const Point& point) noexcept;
	inline value_t distance(const Point& point, const Line& line) noexcept { distance(line, point); }

	// –ассто€ние между точкой и отрезком
	value_t distance(const Segment& seg, const Point& point) noexcept;
	inline value_t distance(const Point& point, const Segment& seg) noexcept { distance(seg, point); }

}