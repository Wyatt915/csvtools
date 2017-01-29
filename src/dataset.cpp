#include "dataset.hpp"
#include "exprtk.hpp"

#include <cassert>

inline double sqr(double x){ return x*x; }

//---------------------[Constructors]------------------------------------------

dataset::dataset():sz(0)
{
    set_all_false();
    data = new double[0];
}

dataset::~dataset(){
    delete[] data;
}

// -----------------------[Overloads]-------------------------------------------

double& dataset::operator[](unsigned int idx){
    assert(idx<sz);
    return data[idx];
}

//----------------["Get-ish" member functions]---------------------------------

unsigned int dataset::size(){ return sz; }

double dataset::iqr(){ return 0.0; }

double dataset::max(){
    assert(sz > 0);

    if(max_b){ return max_d; }

    max_d = data[0];
    for(int i = 1; i < sz; i++){
        if(data[i] > max_d){ max_d = data[i]; }
    }

    max_b = true;
    return max_d;
}
double dataset::mean(){
    assert(sz > 0);

    if(mean_b){ return mean_d; }

    mean_d = std::accumulate(data, data+sz, 0.0)/double(sz);
    mean_b = true;
    return mean_d;
}
double dataset::median(){
    assert(sz > 0);

    if(median_b){ return median_d; }

    if(sorted){
        median_d =  (sz % 2 == 0) ? (data[sz/2] + data[sz/2 - 1])/2.0
                                    : data[sz/2];
        median_b = true;
        return median_d;
    }

    double* d = new double[sz];

    std::copy(data, data + sz, d);
    std::sort(data, data + sz);
    median_b = true;
    median_d = (sz % 2 == 0)  ? (d[sz/2] + d[sz/2 - 1])/2.0 : d[sz/2];

    delete[] d;

    return median_d;
}

double dataset::min(){
    assert(sz > 0);

    if(min_b){ return min_d; }

    min_d = data[0];
    for(int i = 1; i < sz; i++){
        if(data[i] > min_d){ min_d = data[i]; }
    }

    min_b = true;
    return min_d;
}

double dataset::sigma(double n){
    stdev();    //Make sure the standard deviation is defined.  This also implies that the mean is defined.
    return mean_d + (n * stdev_d);
}

double dataset::stdev(){
    assert(sz > 0);

    if(stdev_b){ return stdev_d; }

    stdev_d = sqrt(variance());
    stdev_b = true;
    return stdev_d;
}

double dataset::variance(){
    assert(sz > 0);
    if(variance_b){ return variance_d; }
    mean(); //make sure the mean is defined
    variance_d = 0.0;
    for(int i= 0; i < sz; i++){
        variance_d += sqr(mean_d - data[i]);
    }
    variance_d /= double(sz);
    variance_b = true;
    return variance_d;
}

//-------------------[Apply Modifications]--------------------------------------

void dataset::set_all_false(){
    iqr_b       = false;
    max_b       = false;
    mean_b      = false;
    median_b    = false;
    min_b       = false;
    stdev_b     = false;
    variance_b  = false;
}

void dataset::sort(){
    std::sort(data, data + sz);
}

//more specifically, this type of normalization is called feature scaling
void dataset::normalize(double rmin, double rmax){
    min(); max(); //make sure these are defined
    for (int i = 0; i < sz; i++) {
        data[i] = rmin + ((data[i] - min_d) * (rmax - rmin))/(max_d - min_d);
    }
    set_all_false(); //this changes EVERYTHING!
    min_d = rmin;
    max_d = rmax;
    max_b = min_b = true;
}

void dataset::apply_expression(std::string expression_string) {
    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double>     expression_t;
    typedef exprtk::parser<double>             parser_t;

    double x;

    symbol_table_t syms;
    syms.add_variable("x", x);

    expression_t expression;
    expression.register_symbol_table(syms);

    parser_t parser;

    if(!parser.compile(expression_string, expression)){
        printf("Something's donked.\n");
        return;
    }

    for (size_t i = 0; i < sz; i++) {
        x = data[i];
        data[i] = expression.value();
    }

    set_all_false(); //this changes EVERYTHING!
}
