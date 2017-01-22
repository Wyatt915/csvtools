//#include "strtk.h"
#include "dataset.hpp"
#include "histogram.hpp"

#include <algorithm>
#include <getopt.h>
#include <iostream>
#include <vector>

#include <stdlib.h> //rand
#include <time.h>


std::vector<double> rolldice(int dice, int trials){
    std::vector<double> v;

    srand(time(NULL));
    double sum = 0.0;
    for(int i = 0; i < trials; i++){
        for(int j = 0; j < dice; j++){
            sum += rand() % 6 + 1;
        }
        v.push_back(sum);
        sum = 0.0;
    }
    return v;
}

int main(int argc, char const *argv[]) {
    dataset diceTrials(rolldice(16, 1000000));
    double minimum = diceTrials.mean() - 2*diceTrials.stdev();
    double maximum = diceTrials.mean() + 2*diceTrials.stdev();
    histogram test(diceTrials, minimum, maximum, 28);
    std::cout << "Mean: " << diceTrials.mean() << std::endl;
    test.printg(20);
    return 0;
}
