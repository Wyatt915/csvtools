#pragma once
#include <algorithm>


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
    template<class iterator_type> dataset(iterator_type, iterator_type);
    ~dataset ();

    double iqr();           //Interquartile range
    double max();           //maximum value
    double mean();          //arithmetic mean
    double median();        //median
    double min();           //Minimum value
    double sigma(double);   //Mean + x standard deviations
    double stdev();         //Standard Deviation
    double variance();      //Variance (standard deviation squared)

    double& operator[](unsigned int);

    unsigned int size();

    void normalize(double, double);
    void sort();
};

template<class iterator_type> dataset::dataset(iterator_type i_begin, iterator_type i_end):
    iqr_b(false), max_b(false), mean_b(false), median_b(false),
    min_b(false), stdev_b(false), variance_b(false), sorted(false)
{
        sz = std::distance(i_begin, i_end);
        data = new double[sz];
        std::copy(i_begin, i_end, data);
}
