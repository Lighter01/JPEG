#ifndef PREPROCESSED_IMAGE_HOLDER_H
#define PREPROCESSED_IMAGE_HOLDER_H

#include <algorithm>
#include <vector>

struct preprocessed_image_holder
{
    int pos;
    int16_t quantized[64];
    int DC;
    int posNonZero;

    preprocessed_image_holder(int pos_, int16_t quantized_[64], int DC_, int posNonZero_) : pos(pos_), DC(DC_),
                                                                                                  posNonZero(posNonZero_)
    {
        std::copy(quantized_, quantized_ + 64, this->quantized);
    }

};

std::vector<preprocessed_image_holder> blocks_Y;
std::vector<preprocessed_image_holder> blocks_Cb;
std::vector<preprocessed_image_holder> blocks_Cr;

#endif // PREPROCESSED_IMAGE_HOLDER_H
