#ifndef RUN_TEST_H
#define RUN_TEST_H

#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>

#include <opencv2/opencv.hpp>
using namespace cv;

namespace fs = std::filesystem;

class Timer
{
private:
    using Clock = std::chrono::high_resolution_clock;
    using Second = std::chrono::duration<double, std::ratio<1>>;

    std::chrono::time_point<Clock> m_beg { Clock::now() };

public:
    void reset()
    {
        m_beg = Clock::now();
    }

    std::pair<double, int> elapsed() const
    {
        auto time = Clock::now() - m_beg;
        double sec = std::chrono::duration_cast<Second>(time).count();
        int millisec = std::chrono::duration_cast<std::chrono::milliseconds>(time).count();
        return std::make_pair(sec, millisec);
    }
};

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
