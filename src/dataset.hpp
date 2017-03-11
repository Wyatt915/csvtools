#pragma once

#include <algorithm>
#include <string>

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

    template<class iterator_type> void create(iterator_type, iterator_type);

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

    void set_all_false();
    void scale(double, double);
    void sort();
    void apply_expression(std::string);
};

template<class iterator_type> dataset::dataset(iterator_type i_begin, iterator_type i_end){
    set_all_false();
    sz = std::distance(i_begin, i_end);
    data = new double[sz];
    std::copy(i_begin, i_end, data);
}

template<class iterator_type> void dataset::create(iterator_type i_begin, iterator_type i_end){
    set_all_false();
    sz = std::distance(i_begin, i_end);
    delete[] data;
    data = new double[sz];
    std::copy(i_begin, i_end, data);
}
