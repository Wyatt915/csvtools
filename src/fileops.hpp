/**
* @Author: Wyatt Sheffield <wyatt>
* @Date:   2017-01-24T07:44:34-06:00
* @Email:  wyatt@pixil.xyz
* @Filename: fileops.hpp
* @Last modified by:   wyatt
* @Last modified time: 2017-03-01T20:52:57-06:00
*/
#pragma once
#include <string>
#include <vector>

class dataset;

void split(std::string, std::string, std::vector<std::string>&);
std::vector<std::vector<std::string> > get_column(int, dataset&);
std::vector<std::vector<std::string> > get_column(std::string, int, dataset&);
//void overwrite_column(std::string, int, const dataset&);
