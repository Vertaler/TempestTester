#ifndef TESTOPTIONS
#define TESTOPTIONS
#include "backgroundgenerator.h"
#include "bounded.h"

class TestOptions{
private:
    Bounded<int>* minLineCount;
    Bounded<int>* maxLineCount;
    Bounded<double>* period;
    FillingType fillingType;
public:

    Bounded<int>* getMinLineCount(){
        return minLineCount;
    }
    Bounded<int>* getMaxLineCount(){
        return maxLineCount;
    }
    Bounded<double>* getPeriod(){
        return period;
    }
    FillingType getFillingType(){
        return fillingType;
    }

    void setMinLineCount(Bounded<int>* value){
        minLineCount = value;
    }

    void setMaxLineCount(Bounded<int>* value){
        maxLineCount = value;
    }

    void setPeriod(Bounded<double>* value){
        period = value;
    }

    void setFillingType(FillingType value){
        fillingType = value;
    }

    ~TestOptions(){
        delete period;
        delete minLineCount;
        delete maxLineCount;
    }

};

#endif // TESTOPTIONS

