#pragma once

#include <algorithm>
#include <iostream>
#include <vector>


//a value is placed in a bin if it is less than or equal to the upper bound of
//that bin as defined by binranges.
void calc_histogram(const std::vector<double>& in, double* hist, int bins){
    long* count = new long[bins]();
    double* binranges = new double[bins]();

    double maxval = *std::max_element(in.begin(), in.end());
    double minval = *std::min_element(in.begin(), in.end());

    double binwidth = (maxval - minval)/double(bins);
    double temp = minval;

    for (size_t i = 0; i < bins; i++) {
        binranges[i] = temp;
        temp += binwidth;
    }

    for(double d : in){
        for(int i = bins-1; i >= 0; i--){
            if(d > binranges[i]){
                count[i]++;
                break;
            }
        }
    }

    int total = in.size();
    for(int i = 0; i < bins; i++){
        hist[i] = double(count[i])/double(total);
    }

    delete[] count;
    delete[] binranges;
}

void calc_histogram_by_binwidth(const std::vector<double>& in, double* hist, double binwidth){
    double maxval = *std::max_element(in.begin(), in.end());
    double minval = *std::min_element(in.begin(), in.end());

    int bins = (maxval - minval)/binwidth;

    double* binranges = new double[bins]();
    long* count = new long[bins]();

    double temp = minval;

    for (size_t i = 0; i < bins; i++) {
        binranges[i] = temp;
        temp += binwidth;
    }

    for(double d : in){
        for(int i = bins-1; i >= 0; i--){
            if(d > binranges[i]){
                count[i]++;
                break;
            }
        }
    }

    int total = in.size();
    for(int i = 0; i < bins; i++){
        hist[i] = double(count[i])/double(total);
    }

    delete[] count;
    delete[] binranges;
}


void print_histogram(std::vector<double> data, int bins, int resolution){
    double* histogram = new double[bins];

    calc_histogram(data, histogram, bins);

    double max_val = *std::max_element(histogram, histogram + bins);

    for (int i = 0, j = resolution; i < resolution; i++, j--){
        std::cout << ' ';
        for (int k = 0; k < bins; k++){
            if ((histogram[k] * (resolution / max_val)) >= j){
                std::cout << "# ";
            }
            else{
                std::cout << "  ";
            }
        }
        //create labels for the vertical axis.
        std::cout << "| ";
        printf("%.3f", 100 * (max_val - (((double)i / resolution)*max_val)));
        std::cout << "%\n";

    }

    std::cout << ' ';
    for (int i = 0; i < 26; i++){
        std::cout << (char)('A' + i) << ' ';
    }
    std::cout << '\n';
    delete[] histogram;
}

void print_histogram_by_binwidth(std::vector<double> data, double binwidth, int resolution){
    double maxval = *std::max_element(data.begin(), data.end());
    double minval = *std::min_element(data.begin(), data.end());

    int bins = (maxval - minval)/binwidth;

    double* histogram = new double[bins];

    calc_histogram_by_binwidth(data, histogram, binwidth);

    double max_val = *std::max_element(histogram, histogram + bins);

    for (int i = 0, j = resolution; i < resolution; i++, j--){
        std::cout << ' ';
        for (int k = 0; k < bins; k++){
            if ((histogram[k] * (resolution / max_val)) >= j){
                std::cout << "# ";
            }
            else{
                std::cout << "  ";
            }
        }
        //create labels for the vertical axis.
        std::cout << "| ";
        printf("%.3f", 100 * (max_val - (((double)i / resolution)*max_val)));
        std::cout << "%\n";

    }
    std::cout << '\n';
    delete[] histogram;
}
