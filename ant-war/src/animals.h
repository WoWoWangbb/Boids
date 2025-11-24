# ifndef ANIMAL
# define ANIMAL


template<typename T>
class Animal {
public:
    vector2<T> position;
	bool is_predator;

    Animal(const vector2<T>& pos = { 0,0 }, bool is_pred = false) : position(pos), is_predator(is_pred) {}

    virtual ~Animal() = default;  
};


# endif // !ANIMAL
