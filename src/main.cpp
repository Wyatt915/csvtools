/**
* @Author: Wyatt Sheffield <wyatt>
* @Date:   2017-01-28T15:33:49-06:00
* @Email:  wyatt@pixil.xyz
* @Filename: main.cpp
* @Last modified by:   wyatt
* @Last modified time: 2017-01-29T13:47:36-06:00
*/



#include "dataset.hpp"
#include "histogram.hpp"
#include "fileops.hpp"


#include <algorithm>
#include <getopt.h>
#include <iostream>
#include <string>
#include <vector>

#include <stdlib.h> //rand
#include <time.h>


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

void test() {
    std::vector<double> v = rolldice(16, 1000000);
    dataset diceTrials(std::begin(v), std::end(v));
    double minimum = diceTrials.sigma(-3);
    double maximum = diceTrials.sigma(3);
    histogram test(diceTrials, minimum, maximum, 40);
    std::cout << "Mean: " << diceTrials.mean() << std::endl;
    std::cout << "Standard Deviation: " << diceTrials.stdev() << std::endl;
    test.printg(20);
    diceTrials.apply_expression("sin(x^2 - 2x + 1)");
    minimum = diceTrials.sigma(-3);
    maximum = diceTrials.sigma(3);
    histogram testtwo(diceTrials, minimum, maximum, 40);
    std::cout << "\n\n\n" << std::endl;
    std::cout << "Mean: " << diceTrials.mean() << std::endl;
    std::cout << "Standard Deviation: " << diceTrials.stdev() << std::endl;
    testtwo.printg(20);
}

int main(int argc, char* argv[]){
    static struct option long_options[] = {
        {"column",          required_argument,  0, 'c'},
        {"delimeters",      required_argument,  0, 'd'},
        {"expression",      required_argument,  0, 'e'},
        {"help",            no_argument,        0, 'h'},
        {"input-file",      required_argument,  0, 'i'},
        {"output-file",     required_argument,  0, 'o'},
        {"range",           required_argument,  0, 'r'},
        {"test",            optional_argument,  0, 't'},
        {0, 0, 0, 0}
    };
    char c;

    bool outputFileFlag =   false; //set to true if the -o option is encountered.
    bool inputFileFlag =    false;
    bool expressionFlag =   false;

    int column = 0; //column which will be operated on
    std::string delimeters;
    std::string outputFileName;
    std::string inputFileName;
    std::string range;
    std::string expression;

    while ( (c = getopt_long(argc, argv, "c:d:hi:o:s:t", long_options, NULL)) != -1 ) {
        int this_option_optind = optind ? optind : 1;
        switch (c) {
            case 'c':
                column = std::stoi(std::string(optarg));
                break;
            case 'd':
                delimeters = std::string(optarg);
                break;
            case 'e':
                expressionFlag = true;
                expression = std::string(optarg);
                break;
            case 'h':
                std::cout << "PLACEHOLDER HELP TEXT" << std::endl;
                return 0;
            case 'i':
                inputFileFlag = true;
                inputFileName = std::string(optarg);
                break;
            case 'o':
            outputFileFlag = true;
                outputFileName = std::string(optarg);
                break;
            case 't':
                test();
                break;
            case ':':   /* missing option argument */
                fprintf(stderr, "%s: option `-%c' requires an argument\n",
                argv[0], optopt);
                return 1;
            case '?':    /* invalid option */
                fprintf(stderr, "%s: option `-%c' is invalid: ignored\n",
                argv[0], optopt);
                return 2;
            default:
                std::cerr << "Invalid argument." << std::endl;
                return 3;
        }
    }

    dataset columnData;

    if(inputFileFlag){
        get_column(inputFileName, column, columnData);
        histogram h(columnData, 1, 10, 10);
        h.print();
        std::cout << std::endl;
        h.printg(10);
    }



    return 0;
}
