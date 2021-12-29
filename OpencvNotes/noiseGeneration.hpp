//
//  noiseGeneration.hpp
//  OpencvNotes
//
//  Created by Ray on 2021/12/28.
//

#ifndef noiseGeneration_hpp
#define noiseGeneration_hpp

#include <stdio.h>
cv::Mat AddSaltAndPepperNoise(cv::Mat image, int n);
void GenerateSaltAndPepperNoise();
cv::Mat AddGaussNoise(cv::Mat mat, float mean, float std);
void GenerateGaussNoise();

#endif /* noiseGeneration_hpp */
