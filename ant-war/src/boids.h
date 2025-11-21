# ifndef BOIDS_H
# define BOIDS_H

# include "vector2.h"
#include "config.h"
#include<vector>
#include<cmath>

//template <typename T>
//struct vector2{
//	T x, y;
//	vector2(T _x = 0,T _y = 0) : x(_x), y(_y) {}
//	vector2<T> operator+(vector2<T> const & other) const {
//		return { x + other.x, y + other.y };
//	}
//	vector2<T> operator-(vector2<T> const & other) const {
//		return { x - other.x, y - other.y };
//	}
//	vector2<T> operator*(T const & scalar) const {
//		return { x * scalar, y * scalar };
//	}
//	vector2<T> & operator+=(vector2<T> const & other) {
//		x += other.x;
//		y += other.y;
//		return *this;
//	}
//	vector2<T> & operator-=(vector2<T> const & other) {
//		x -= other.x;
//		y -= other.y;
//		return *this;
//	}
//	vector2<T> & operator*=(T const & scalar) {
//		x *= scalar;
//		y *= scalar;
//		return *this;
//	}
//	vector2<T> normalized() const {
//		T l = length();
//		if (l == 0) return { 0, 0 };
//		return { x / l, y / l };
//	}
//	T length() const {
//		return sqrt(x * x + y * y);
//	}
//
//};

template<typename T>
struct boid {
	vector2<T> position;
	vector2<T> velocity;
	vector2<T> acceleration;
};

//template<typename T>
//class BSystem {
//public:
//	vector<boid<T>> boids;
//	void add_boid(vector2<T> const & position, vector2<T> const & velocity) {
//		boids.push_back({ position, velocity, {0, 0} });
//	}
//	void do_update();
//private:
//	vector2<T> ruleCohesion(const boid<T>& b);
//	vector2<T> ruleSeparation(const boid<T>& b);
//	vector2<T> ruleAlignment(const boid<T>& b);
//
//};
//
//
//template<typename T>
//vector2<T> BSystem<T>::ruleCohesion(const boid<T>& b) {
//	vector2<T> center{ 0, 0 };
//	int count = 0;
//	for (const auto& other : boids) {
//		if (&other == &b) continue;
//		T dist = (other.position - b.position).length();
//		if (dist < 100) {
//			center += other.position;
//			count++;
//		}
//	}
//	if (count > 0) {
//		center *= (1.0 / count);
//		return (center - b.position) * T(0.01);
//	}
//	return { 0,0 };
//}
//
//template<typename T>
//vector2<T> BSystem<T>::ruleAlignment(const boid<T>& b) {
//	vector2<T> avgVelocity{ 0, 0 };
//	int count = 0;
//	for (const auto& other : boids) {
//		if (&other == &b) continue;
//		T dist = (other.position - b.position).length();
//		if (dist < 100) {
//			avgVelocity += other.velocity;
//			count++;
//		}
//	}
//	if (count > 0) {
//		avgVelocity *= (1.0 / count);
//		return (avgVelocity - b.velocity) * T(0.02);
//	}
//	return { 0,0 };
//}
//
//template<typename T>
//vector2<T> BSystem<T>::ruleSeparation(const boid<T>& b) {
//	vector2<T> force{ 0, 0 };
//	int count = 0;
//	for (const auto& other : boids) {
//		if (&other == &b) continue;
//		vector2<T> diff = b.position - other.position;
//		if (diff.length() < 50) {
//			force += diff;
//			count++;
//		}
//	}
//	if (count > 0)  return force * T(0.5);
//	return { 0,0 };
//}
//
//template<typename T>
//void BSystem<T>::do_update() {
//	
//	for (auto& b : boids) {
//		vector2<T> c = ruleCohesion(b);
//		vector2<T> s = ruleSeparation(b);
//		vector2<T> a = ruleAlignment(b);
//
//		b.acceleration = c + s + a;
//	}
//
//	
//	for (auto& b : boids) {
//		b.velocity += b.acceleration;
//
//		T maxSpeed = 4;
//		if (b.velocity.length() > maxSpeed) {
//			b.velocity = b.velocity.normalized() * maxSpeed;
//		}
//
//		b.position += b.velocity;
//
//	
//		if (b.position.x < 0) b.position.x += 800;
//		if (b.position.x > 800) b.position.x -= 800;
//		if (b.position.y < 0) b.position.y += 600;
//		if (b.position.y > 600) b.position.y -= 600;
//	}
//}

#endif