#pragma once

#include "dataset.hpp"

#include <vector>

class dataset {
private:
    double* data;
    unsigned int sz;
    bool sorted;

    double iqr_d, max_d, mean_d, median_d, min_d, stdev_d, variance_d;

    //these are true if the values have alredy been calculated
    bool iqr_b, max_b, mean_b, median_b, min_b, stdev_b, variance_b;
public:
    dataset();
    dataset(double*, unsigned int);
    dataset(const std::vector<double>&);
    ~dataset ();

    double iqr();
    double max();
    double mean();
    double median();
    double min();
    double stdev();
    double variance();

    double& operator[](unsigned int);

    unsigned int size();

    void normalize(double, double);
    void sort();
};
