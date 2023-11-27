#include "run_test.h"
#include "toojpeg.h"

#include <sstream>

statistics::Statistics stat_("speed_tests_1.csv");

std::string getFileSize(const fs::path& path)
{
    std::stringstream f_size;
    uintmax_t size = fs::file_size(path);
    int o{};
    double mantissa = size;
    for (; mantissa >= 1024.; mantissa /= 1024., ++o);
    f_size << std::ceil(mantissa * 10.) / 10. << "BKMGTPE"[o];
    o ? f_size << "B (" << size << ')' : f_size;
    return f_size.str();
}

unsigned char* read_image(const fs::path& path_, int& width, int& height, const bool isRGB)
{
    Mat img = imread(path_.string());
    width  = img.cols;
    height = img.rows;

    unsigned char* image;

    if (isRGB)
    {
        const auto bytesPerPixel = 3;
        image = new unsigned char[width * height * bytesPerPixel];

        for (auto y = 0; y < height; y++)
        {
            for (auto x = 0; x < width; x++)
            {
                Vec3b bgrPixel = img.at<Vec3b>(y, x);
                auto offset = (y * width + x) * bytesPerPixel;

                image[offset    ] = bgrPixel.val[2];
                image[offset + 1] = bgrPixel.val[1];
                image[offset + 2] = bgrPixel.val[0];
            }
        }
    }
    else
    {
        int b, g, r, gr;
        const auto bytesPerPixel = 1;
        image = new unsigned char[width * height * bytesPerPixel];

        for (auto y = 0; y < height; y++)
        {
            for (auto x = 0; x < width; x++)
            {
                Vec3b bgrPixel = img.at<Vec3b>(y, x);
                b = bgrPixel.val[2];
                g = bgrPixel.val[1];
                r = bgrPixel.val[0];
                gr = std::nearbyint((b + g + r) / 3);
                auto offset = (y * width + x);
                image[offset] = std::clamp(gr, 0, 255);
            }
        }
    }

    return image;
}

std::ofstream myFile;

void myOutput(unsigned char byte)
{
    myFile << byte;
}

void runTest(unsigned char quality, bool downsample, const char* comment)
{
    fs::create_directory("results/");
    std::vector<fs::path> files;

    try {
        for (const auto& entry : fs::directory_iterator("images")) {
            if (entry.is_regular_file()) {
                files.push_back(entry.path());
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error accessing directory: " << e.what() << std::endl;
    }

    stat_ << "filename;width;height;isRGB;quality;downsample;seconds;milliseconds;size before;size after\n";
    int width, height;
    bool isRGB;

    std::string f_size_before, f_size_after, new_image_name;

    for (const auto& path : files)
    {
        f_size_before = getFileSize(path);

        isRGB = (path.stem().string().find("grayscale") == std::string::npos) ? true : false;
        std::cout << path.filename() << '\n';


        new_image_name = path.stem().string() + '_'
                         + std::to_string(int(std::clamp<uint8_t>(quality, 1, 100)));
        myFile.open("results/" + new_image_name + ".jpg", std::ios_base::out | std::ios_base::binary);

        unsigned char* image = read_image(path, width, height, isRGB);

        auto[seconds, milliseconds] = TooJpeg::writeJpeg(myOutput, image, width, height, isRGB, quality, downsample, comment);

        f_size_after = getFileSize(fs::path("results/" + new_image_name + ".jpg"));

        stat_ << new_image_name << ';' << width << ';' << height << ';' << isRGB << ';'
              << int(std::clamp<uint8_t>(quality, 1, 100)) << ';' << downsample << ';' << seconds << ';' << milliseconds << ';'
              << f_size_before << ';' << f_size_after << '\n';

        myFile.close();

        delete[] image;

    }

}


