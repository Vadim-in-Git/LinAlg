#include "CppUnitTest.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "../Segments/source/LinAlg/linalg_utilities.h"
using namespace LinAlg;

namespace Segments{
	TEST_CLASS(Distance){
	public:
		TEST_METHOD(Points){
			Point p1{ 0,0,0 }, p2{ 1,2,2 };
			value_t result = 3;
			Assert::AreEqual(result, distance(p1, p2));
		}
		TEST_METHOD(Point_and_line) {
			Point p1{ 0, 0, 0 }, p2{ 1,0,0 }, p3{ -3, 4, 0 };
			Line line(p1, p2);
			value_t result = 4;
			Assert::AreEqual(result, distance(line, p3));
		}
		TEST_METHOD(Point_and_Segment) {
			Point p1{ 0, 0, 0 }, p2{ 1,0,0 }, p3{ -3, 4, 0 };
			Segment segment(p1, p2);
			value_t result = 5;
			Assert::AreEqual(result, distance(segment, p3));
		}
	};
	TEST_CLASS(Others) {
	public:
		TEST_METHOD(Collinear) {
			Point p1{ 0, 0, 0 }, p2{ 1,0,1 };
			Point p3{ 0,1,0 }, p4{ 1,1,1 };
			Segment s1(p1, p2), s2(p3, p4);
			Assert::IsTrue(is_collinear(s1, s2));
		}
	};
}
