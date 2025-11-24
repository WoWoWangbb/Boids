# ifndef BOIDS_H
# define BOIDS_H

# include "vector2.h"
# include "animals.h"

template<typename T>
struct boid : public virtual Animal<T> { 
    vector2<T> velocity;
    vector2<T> acceleration;

    boid(const vector2<T>& pos = { 0,0 },
        const vector2<T>& vel = { 0,0 },
        const vector2<T>& acc = { 0,0 })
        : Animal<T>(pos), velocity(vel), acceleration(acc) {}  
};


#endif