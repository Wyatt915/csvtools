#include "histogram.hpp"
#include "stats.hpp"

#include <algorithm>
#include <iostream>

#define TERMINAL_RED "\x1b[31;1m"
#define TERMINAL_DEF "\x1b[0m"

bin::bin(): upper(0), lower(0), value(0){}

bin::bin(double a, double b):value(0){
    if(a<b){
        lower = a;
        upper = b;
    }
    else{
        lower = b;
        upper = a;
    }
}


//is val in (lower,upper]?
bool bin::contains(double val){
    return val > lower && val <= upper;
}

bool bin::contains(double a, double b){
    return (a > lower && a <= upper) || (b > lower && b <= upper);
}

int bin::count(){
    return value;
}

void bin::inc(){
    ++value;
}

void bin::setl(double l){
    lower = l;
}

void bin::setu(double u){
    upper = u;
}


///////////////////////////////////////////////////////////////////////////////

histogram::histogram(dataset& ds, double mn, double mx, int b)
    :numbins(b), minval(mn), maxval(mx), rawdata(ds){
    size = rawdata.size();
    proportional = new double[numbins];
    bins = new bin[numbins];
    create_by_bins(numbins);
}

histogram::~histogram(){
    delete[] bins;
    delete[] proportional;
}

void histogram::create_by_bins(int n){
    numbins = n;

    delete[] bins;
    delete[] proportional;

    bins = new bin[numbins]();
    proportional = new double[numbins];

    double binwidth = (maxval - minval)/double(numbins);
    double temp = minval - (binwidth / 2); //ensure that minval gits placed in a bin

    for (size_t i = 0; i < numbins; i++) {
        bins[i].setl(temp);
        temp += binwidth;
        bins[i].setu(temp);
    }

    for(int i = 0; i < size; i++){
        for(int j = 0; j < numbins; j++){
            if(bins[j].contains(rawdata[i])){
                bins[j].inc();
                break;
            }
        }
    }

    for(int i = 0; i < numbins; i++){
        proportional[i] = double(bins[i].count())/double(size);
    }
}

void histogram::printg(int resolution){
    double max_prop_val = *std::max_element(proportional, proportional + numbins);

    for (int i = 0, j = resolution; i < resolution; i++, j--){
        std::cout << ' ';
        for (int k = 0; k < numbins; k++){
            if ((proportional[k] * (resolution / max_prop_val)) >= j){
                if(bins[k].contains(rawdata.sigma(-1), rawdata.sigma(1))){
                    std::cout << TERMINAL_RED << "# " << TERMINAL_DEF;
                }
                else{
                    std::cout << "# ";
                }
            }
            else{
                std::cout << "  ";
            }
        }
        //create labels for the vertical axis.
        std::cout << "| ";
        printf("%.3f", 100 * max_prop_val * (1- (double(i) / resolution)));
        std::cout << "%\n";

    }
    std::cout << '\n';
}
