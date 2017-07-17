#ifndef BOUNDED_H
#define BOUNDED_H


template <typename T>
class Bounded
{
    T step;
    T max;
    T min;
    T value;


    void clamp()
    {
        if(this->value > max){
            this->value = max;
        }
        if(this->value < min){
            this->value = min;
        }
    }
public:
    T Value(){return value;}


    void Inc()
    {
        value += step;
        clamp();
    }

    void Dec()
    {
        value -= step;
        clamp();

    }

    void Set(T value)
    {
        this->value = value;
        clamp();
    }

    Bounded(T step, T max, T min, T value)
    {
        this->step = step;
        this->max = max;
        this->min = min;
        Set(value);
    }

    Bounded()
    {

    }
};

#endif // BOUNDED_H
