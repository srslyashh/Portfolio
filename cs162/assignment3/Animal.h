#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>
using namespace std;

class Animal
{
    private:
        int age;
        int cost;
        float foodCost;
        int revenue;
    public:
        // constructors
        Animal();
        Animal(int,int,float,int);

        // destructor
        ~Animal();

        // getters
        int getAge();
        int getCost();
        float getFoodCost();
        int getRevenue();

        // setters
        void setCost(int);
        void setAge(int);
        void setFoodCost(float);
        void setRevenue(int);
        float newFoodC(float);

        // killing animals :(
        void emptyAnimal();
};

#endif