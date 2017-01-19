#pragma once

#include <vector>


class bin{
private:
    double lower;
    double upper;
    int value;
public:
    bin();
    bin(double, double);
    bool contains(double);
    int count();
    void inc();
    void setl(double);
    void setu(double);
};


class histogram {
private:
    int size;
    int numbins;

    double maxval;
    double minval;

    double* proportional;
    double* rawdata;
    bin* bins;
public:
    histogram();
    histogram(const std::vector<double>&);
    histogram(double*, int);
    void create(); //Determine bins automatically by the Freedman–Diaconis rule
    void create_by_bins(int); //use a predefined number of bins
    void create_by_binwidth(double); //use a predefined bin width
    void print(); //prints the bin followed by the count for that bin
    void printg(int); //prints a "graphical" histogram
    ~histogram ();
};
