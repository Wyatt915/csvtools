#include "dataset.hpp"
#include <algorithm>

inline double sqr(double x){ return x*x; }

//---------------------[Constructors]------------------------------------------

dataset::dataset():
    iqr_b(false), max_b(false), mean_b(false), median_b(false),
    min_b(false), stdev_b(false), variance_b(false), sorted(false), size(0)
{
        data = new double[0];
}

dataset::dataset(double* d, unsigned int s):
    iqr_b(false), max_b(false), mean_b(false), median_b(false),
    min_b(false), stdev_b(false), variance_b(false), sorted(false), size(s)
{
    data = new double[size];
    std::copy(d, d + s, data);
}

dataset::dataset(const std::vector<double>& v):
    iqr_b(false), max_b(false), mean_b(false), median_b(false),
    min_b(false), stdev_b(false), variance_b(false), sorted(false)
{
    size = v.size();
    data = new double[size];
    std::copy(std::begin(v), std::end(v), data);
}

//----------------["Get-ish" member functions]---------------------------------

double dataset::iqr(){ return 0.0; }

double dataset::max(){
    assert(size > 0);

    if(max_b){ return max_d; }

    max_d = data[0];
    for(int i = 1; i < size; i++){
        if(data[i] > max){ max = data[i]; }
    }

    max_b = true;
    return max_d;
}
double dataset::mean(){
    assert(size > 0);

    if(mean_b){ return mean_d; }

    mean_d = std::accumulate(data, data+size, 0.0)/double(size);
    mean_b = true;
    return mean_d;
}
double dataset::median(){
    assert(size > 0);

    if(median_b){ return median_d; }

    if(sorted){
        median_d =  (size % 2 == 0) ? (data[size/2] + data[size/2 - 1])/2.0
                                    : data[size/2];
        median_b = true;
        return median_d;
    }

    double* d = new double[size];

    std::copy(data, data + size, d);
    std::sort(data, data + size);
    median_b = true;
    median_d = (size % 2 == 0)  ? (d[size/2] + d[size/2 - 1])/2.0 : d[size/2];

    delete[] d;

    return median_d;
}

double dataset::min(){
    assert(size > 0);

    if(min_b){ return min_d; }

    min_d = data[0];
    for(int i = 1; i < size; i++){
        if(data[i] > min){ min = data[i]; }
    }

    min_b = true;
    return min_d;
}

double dataset::stdev(){
    assert(size > 0);

    if(stdev_b){ return stdev_d; }

    stdev_d = sqrt(variance());
    stdev_b = true;
    return stdev_d;
}
double dataset::variance(){
    assert(size > 0);

    if(variance_b){ return variance_d; }

    mean(); //make sure the mean is defined
    variance_d = 0.0;

    for(int i= 0; i < size; i++){
        variance_d += sqr(mean_d - data[i]);
    }

    variance_d /= double(size);

    variance_b = true;
    return variance_d;
}

//more specifically, this type of normalization is called feature scaling
void dataset::normalize(double rmin, double rmax){
    min(); max(); //make sure these are defined
    for (size_t i = 0; i < size; i++) {
        data[i] = rmin + ((data[i] - min_d) * (rmax - rmin))/(max_d - min_d);
    }
    min_d = rmin;
    max_d = rmax;
    iqr_b = mean_b = median_b = stdev_b = variance_b = false; //this changes EVERYTHING!
}
