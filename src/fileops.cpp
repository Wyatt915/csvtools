/**
* @Author: Wyatt Sheffield <wyatt>
* @Date:   2017-01-28T15:32:43-06:00
* @Email:  wyatt@pixil.xyz
* @Filename: fileops.cpp
* @Last modified by:   wyatt
* @Last modified time: 2017-01-29T13:42:05-06:00
*/

// #include "strtk.hpp"
#include "fileops.hpp"
#include "dataset.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

void get_column(std::string fname, int col, dataset& container){
    // std::vector<std::string> row;
    std::vector<double> data;
    std::string line;
    std::fstream infile;
    infile.open(fname.c_str(), std::fstream::in);
    if(infile.is_open()){
        while(std::getline(infile,line)){
            // strtk::split(",\t", line, row);
            data.push_back(std::stod(line));
            // row.clear();
        }
        infile.close();
    }

    container.create(std::begin(data), std::end(data));
}

// void overwrite_column(std::string, int col, const dataset&){
//     std::fstream infile;
//     infile.open(fname.c_str(), std::fstream::in | std::fstream::out);
//     std::stringstream ss;
//     std::vector<std::string> row;
//
//     if(infile.is_open()){
//         while(std::getline(infile,line)){
//             strtk::split(",\t", line, row);
//
//             row.clear();
//         }
//         infile.close();
//     }
// }
