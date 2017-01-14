//#include "strtk.h"

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

void calc_histogram(const std::vector<double>& in, double* hist, int binwidth, bool flag){
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

void print_histogram(std::vector<double> data, int binwidth, int resolution, bool flag){
    double maxval = *std::max_element(data.begin(), data.end());
    double minval = *std::min_element(data.begin(), data.end());

    int bins = (maxval - minval)/binwidth;

    double* histogram = new double[bins];

    calc_histogram(data, histogram, binwidth, true);

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
    print_histogram(rolldice(10, 100000), 1, 20, true);
    return 0;
}
