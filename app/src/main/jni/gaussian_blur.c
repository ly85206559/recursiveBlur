//
// Created by Ben.li on 2017/7/11.
//
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <memory.h>
#include "gaussian_blur.h"

void
calculateHorizonComp(unsigned char *data, double *weightArr, int width, int height, int radius) {
    unsigned char *calData = malloc(sizeof(unsigned char) * width * height);
    memcpy(calData, data, sizeof(unsigned char) * width * height);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double sum = 0;
            for (int k = -radius; k <= radius; k++) {
                int index = j + k;
                if (index < 0) {
                    index = abs(index);
                } else if (index >= width) {
                    index = width * 2 - index - 1;
                }
                sum += (*(calData + i * width + index)) * weightArr[k + radius];
            }
            *(calData + i * width + j) = sum;
        }
    }
    memcpy(data, calData, sizeof(unsigned char) * width * height);
    free(calData);
}

void
calculateVerticalComp(unsigned char *data, double *weightArr, int width, int height, int radius) {
    unsigned char *calData = malloc(sizeof(unsigned char) * width * height);
    memcpy(calData, data, sizeof(unsigned char) * width * height);
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            double sum = 0;
            for (int k = -radius; k <= radius; k++) {
                int index = j + k;
                if (index < 0) {
                    index = abs(index);
                } else if (index >= height) {
                    index = height * 2 - index - 1;
                }
                sum += (*(calData + index * width + i)) * weightArr[k + radius];
            }
            *(calData + j * width + i) = sum;
        }
    }
    memcpy(data, calData, sizeof(unsigned char) * width * height);
    free(calData);
}

double getWeight(int x, int radius) {
    double sigma = (radius * 2 + 1) / 2;
    double weight = (1 / sqrt(2 * M_PI) * sigma) * pow(M_E, ((-(x * x)) / ((2 * sigma * sigma))));

    return weight;
}

void calculateWeightMatrix(double *weightArr, int radius) {
    for (int i = 0; i < radius * 2 + 1; i++) {
        *(weightArr + i) = getWeight(i - radius, radius);
    }
}

void calculateNormalizedWeightMatrix(double *weightArr, int length) {
    double weightSum = 0;

    for (int i = 0; i < length; i++) {
        weightSum += *(weightArr + i);
    }

    for (int i = 0; i < length; i++) {
        *(weightArr + i) = *(weightArr + i) / weightSum;
    }
}
