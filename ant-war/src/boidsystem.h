#ifndef BOIDSYSTEM_H
#define BOIDSYSTEM_H

#include "boids.h"
#include "config.h"
#include<vector>
#include<cmath>

using namespace std;

template<typename T>
class BSystem {
public:
	vector<boid<T>> boids;
	void add_boid(vector2<T> const& position, vector2<T> const& velocity) {
		boids.push_back({ position, velocity, {0, 0} });
	}
	void do_update();
private:
	vector2<T> ruleCohesion(const boid<T>& b, T kc = T(Config::K_COHESION));
	vector2<T> ruleSeparation(const boid<T>& b, T ks = T(Config::K_SEPARATION));
	vector2<T> ruleAlignment(const boid<T>& b, T ka = T(Config::K_ALIGNMENT));
	vector2<T> ruleCible(const boid<T>& b, vector2<T> const& object, T k = T(Config::K_TARGET));
};


template<typename T>
vector2<T> BSystem<T>::ruleCohesion(const boid<T>& b, T kc) {
	vector2<T> center{ 0, 0 };
	int count = 0;
	for (const auto& other : boids) {
		if (&other == &b) continue;
		T dist = (other.position - b.position).length();
		if (1) {
			center += other.position;
			count++;
		}
	}
	if (count > 0) {
		center *= (1.0 / count);
		return (center - b.position) * T(kc);
	}
	return { 0,0 };
}

template<typename T>
vector2<T> BSystem<T>::ruleAlignment(const boid<T>& b, T ka) {
	vector2<T> avgVelocity{ 0, 0 };
	int count = 0;
	for (const auto& other : boids) {
		if (&other == &b) continue;
		T dist = (other.position - b.position).length();
		if (1) {
			avgVelocity += other.velocity;
			count++;
		}
	}
	if (count > 0) {
		avgVelocity *= (1.0 / count);
		return (avgVelocity - b.velocity) * T(ka);
	}
	return { 0,0 };
}


template<typename T>
vector2<T> BSystem<T>::ruleSeparation(const boid<T>& b, T ks) {
	vector2<T> force{ 0, 0 };
	for (const auto& other : boids) {
		if (&other == &b) continue;
		vector2<T> diff = b.position - other.position;
		if (diff.length() < Config::SEPARATION_RADIUS) {
			force += diff;
		}
	}
	return force * T(ks);
	return { 0,0 };
}

// r¨¨gle: tendance ¨¤ se diriger vers une cible
template<typename T>
vector2<T> BSystem<T>::ruleCible(const boid<T>& b, const vector2<T>& target, T k ) {
	vector2<T> dir = target - b.position;
	if (dir.length() == 0) return { 0, 0 };

	vector2<T> acceleration = dir * k / dir.length();

	return acceleration;
}


template<typename T>
void BSystem<T>::do_update() {

	for (auto& b : boids) {
		vector2<T> c = ruleCohesion(b);
		vector2<T> s = ruleSeparation(b);
		vector2<T> a = ruleAlignment(b);
		
		if (Config::cible_MODE) {
		vector2<T> nestPosition{ Config::TARGET_X, Config::TARGET_Y }; // position de la cible (nid)
		vector2<T> t = ruleCible(b, nestPosition);
		b.acceleration = c + a + t + s;
		}
		else {
			b.acceleration = c + a + s;
		}

	}


	for (auto& b : boids) {
		b.velocity += b.acceleration;

		T maxSpeed = 4;
		if (b.velocity.length() > maxSpeed) {
			b.velocity = b.velocity.normalized() * maxSpeed;
		}

		b.position += b.velocity;

		// if outbound
		int WIDTH = Config::WIDTH;
		int HEIGHT = Config::HEIGHT;
		if (b.position.x < 0) b.position.x += WIDTH;
		if (b.position.x > WIDTH) b.position.x -= WIDTH;
		if (b.position.y < 0) b.position.y += HEIGHT;
		if (b.position.y > HEIGHT) b.position.y -= HEIGHT;
	}
}

# endif


