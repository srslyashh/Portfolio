#ifndef ZOO_H
#define ZOO_H

#include "Animal.h"
#include "Bear.h"
#include "Sealion.h"
#include "Tiger.h"
#include <iostream>
using namespace std;

class Zoo
{
    private:
        SeaLion *sealion;
        Tiger *tiger;
        Bear *bear;
        float balance;
        int numSL;
        int numTiger;
        int numBear;
        float totalFeed;
        float bonus;
        int quitGame;
    public:
        Zoo();
        Zoo(SeaLion* const &, Tiger* const &, Bear* const &, int, int, int);
        ~Zoo();

        //void removeAnimal(const Animal&);
        //void addAnimal(const Animal&);
        //bool isAdult(const Animal&);
        bool isBalance0();

        //getter
        int getQuitG();

        // setting up new arr
        void setUpSL(SeaLion* const& sl, int msl);
        void setUpT(Tiger* const& t, int mt);
        void setUpB(Bear* const& b, int mb);

        //getters
        SeaLion*& getSeaLion();
        Tiger*& getTiger();
        Bear*& getBear();

        int getBaby(int);
        int getAdult(int);
        int getAdolescent(int);

        // add members
        void addSeaLion();
        void addTiger();
        void addBear();

        // add babies
        void addSLB();
        void addTB();
        void addBB();

        void addSpecies(int, int);

        // remove members
        void removeSpecies(int, int);
        void removeSeaLion(int);
        void removeTiger(int);
        void removeBear(int);

        // price of animal
        int priceFunction(int, int);
        // print functions
        void printInitial();
        void printStatus();
        void printOptions();
        void printFeed();
        void buySpeciesOpt();

        // checking options.
        int checkOption(const string, int);
        void loopOption(string &, int &, int);
        float feedOption(float);

        float sumFeed(float);
        int checkMoney(int,int,int);

        // the game itself.
        void startZoo();
        void randomEvent();
        void randomEventTwo(int &, int);
        void monthEnd();
        void incrementAge();
        void subtractFeed();
        void monthlyRevenue();
        float revenueNotUpdated();
        void GameOver(int);
        int checkEnoughBalance();
        int isGameOver();
        void printSummary();

        // EVENT FUNCTIONS
        void animalSick(int);
        void giveBirth(int);
        void bonusSL();
        void eventPrint(int);
        string getName(int);
        void randAnimal(int, int&);
        int doesAExist(int species);

        // bill & sum
        float bill(int, int &);
        float checkingSum(float);
        float billBear(int &);
        float billTiger(int &);
        float billSL(int &);
};

#endif