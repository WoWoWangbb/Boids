# ifndef  VECTOR_2
# define  VECTOR_2
#include "config.h"
#include <cmath>

template <typename T>
struct vector2 {
	T x, y;
	vector2(T _x = 0, T _y = 0) : x(_x), y(_y) {}
	vector2<T> operator+(vector2<T> const& other) const {
		return { x + other.x, y + other.y };
	}
	vector2<T> operator-(vector2<T> const& other) const {
		return { x - other.x, y - other.y };
	}
	vector2<T> operator*(T const& scalar) const {
		return { x * scalar, y * scalar };
	}
	vector2<T> operator/(T const& scalar) const {
		return { x / scalar, y / scalar };
	}
	vector2<T>& operator+=(vector2<T> const& other) {
		x += other.x;
		y += other.y;
		return *this;
	}
	vector2<T>& operator-=(vector2<T> const& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}
	vector2<T>& operator*=(T const& scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	}
	vector2<T> normalized() const {
		T l = length();
		if (l == 0) return { 0, 0 };
		return { x / l, y / l };
	}
	T length() const {
		return std::sqrt(x * x + y * y);
	}
};



#endif // ! VECTOR_2

