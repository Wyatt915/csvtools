#pragma once

#include <algorithm>
#include <vector>

namespace stat{
    inline double sqr(double x){ return x*x; }

    double mean(std::vector<double>& data){
        return std::accumulate(std::begin(data), std::end(data), 0)/data.size();
    }

    double mean(double data[], int size){
        return std::accumulate(data, data + size, 0)/size;
    }

    double median(std::vector<double>& data){
        std::sort(std::begin(data),std::end(data));
        int n = data.size();
        return (n % 2 == 0) ? (data[n/2] + data[n/2-1])/2.0 :  data[n/2];
    }

    double stddev(std::vector<double>& data, double avg){
        double sum = 0.0;
        for(int i = 0; i < data.size(); i++){
            sum += sqr(data[i] - avg);
        }
        return sqrt(sum/data.size());
    }

    double stddev(double* data, double avg, int size){
        double sum = 0.0;
        for(int i = 0; i < size; i++){
            sum += sqr(data[i] - avg);
        }
        return sqrt(sum/size);
    }
}
