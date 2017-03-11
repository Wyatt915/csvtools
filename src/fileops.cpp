/**
* @Author: Wyatt Sheffield <wyatt>
* @Date:   2017-01-28T15:32:43-06:00
* @Email:  wyatt@pixil.xyz
* @Filename: fileops.cpp
* @Last modified by:   wyatt
* @Last modified time: 2017-03-11T14:14:49-06:00
*/

// #include "strtk.hpp"
#include "fileops.hpp"
#include "dataset.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

bool check_delim(char test, std::string delim){
    bool test_in_delim = false;
    int pos = 0;
    while(!test_in_delim && pos < delim.length()){
        test_in_delim = (test == delim[pos]);
        pos++;
    }
    return test_in_delim;
}

void split(std::string line, std::string delim, std::vector<std::string>& container){
    container.clear();
    std::string token = "";
    for (size_t i = 0; i < line.length(); i++) {
        if(check_delim(line[i], delim)){
            container.push_back(token);
            token = "";
        }
        else{
            token += line[i];
        }
    }
    if(token != ""){
        container.push_back(token);
    }
}

std::vector<std::vector<std::string> > get_column(int col, dataset& container){
    std::vector<std::string> row;
    std::vector<double> data;
    std::string line;
    std::vector<std::vector<std::string> > csv;
    while(std::getline(std::cin, line)){
        //row gets cleared in the split function
        split(line, ",", row);
        csv.push_back(row);
        data.push_back(std::stod(row[col]));
    }

    container.create(std::begin(data), std::end(data));
    return csv;
}

std::vector<std::vector<std::string> > get_column(std::string fname, int col, dataset& container){
    std::vector<std::string> row;
    std::vector<double> data;
    std::string line;
    std::vector<std::vector<std::string> > csv;
    std::fstream infile;
    infile.open(fname.c_str(), std::fstream::in);
    if(infile.is_open()){
        while(std::getline(infile,line)){
            split(line, ",", row);
            csv.push_back(row);
            data.push_back(std::stod(row[col]));
            row.clear();
        }
        infile.close();
    }

    container.create(std::begin(data), std::end(data));
    return csv;
}

// void output()

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
