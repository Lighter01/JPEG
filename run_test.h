#ifndef RUN_TEST_H
#define RUN_TEST_H

#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <opencv2/opencv.hpp>
using namespace cv;

namespace fs = std::filesystem;

namespace statistics
{
    class Statistics
    {
    private:
        std::ofstream stat;

    public:
        Statistics(const std::string& path) : stat(path) {};
        ~Statistics() { stat.close(); }

        template<typename T>
        Statistics& operator<<(const T& data) { stat << data; return *this; }
    };
}

void runTest(unsigned char quality, bool downsample, const char* comment);

#endif // RUN_TEST_H
