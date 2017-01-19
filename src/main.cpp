//#include "strtk.h"
#include "histogram.hpp"

#include <algorithm>
#include <getopt.h>
#include <iostream>
#include <vector>

#include <stdlib.h> //rand
#include <time.h>



//more specifically, this type of normalization is called feature scaling
std::vector<double> normalize(std::vector<double> in, double rmin, double rmax){
    double maxval = *std::max_element(in.begin(), in.end());
    double minval = *std::min_element(in.begin(), in.end());
    for (size_t i = 0; i < in.size(); i++) {
        in[i] = rmin + ((in[i] - minval) * (rmax - rmin))/(maxval - minval);
    }
    return in;
}

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
    histogram test(rolldice(16, 1000000));
    test.create_by_bins(60);
    test.printg(20);
    return 0;
}
