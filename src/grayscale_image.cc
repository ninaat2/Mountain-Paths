#include "grayscale_image.hpp"

#include <cmath>
#include <string>
#include <stdexcept>
#include <fstream>

#include "elevation_dataset.hpp"

GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
  width_ = dataset.Width();
  height_ = dataset.Height();
  int max_ele = dataset.MaxEle();
  int min_ele = dataset.MinEle();
  image_ = {};
  for (size_t i = 0; i < height_; i++) {
    image_.push_back({});
  }
  // for each element in the dataset, find the shade of gray and apply it
  for (size_t i = 0; i < height_; ++i) {
    for (size_t j = 0; j < width_; ++j) {
      int elevation_point = dataset.DatumAt(i, j);
      int shade_of_gray = 0;
      if (min_ele == max_ele) {
        shade_of_gray = 0;
      } else {
        int numerator = elevation_point - min_ele;
        int denominator = max_ele - min_ele;
        double quotient = static_cast<double>(numerator)/denominator;
        shade_of_gray =
            std::round(quotient * kMaxColorValue);
      }
      Color color(shade_of_gray, shade_of_gray, shade_of_gray);
      image_.at(i).push_back(color);
    }
  }
}
GrayscaleImage::GrayscaleImage(const std::string& filename,
                               size_t width,
                               size_t height) {
  ElevationDataset dataset(filename, width, height);
  width_ = dataset.Width();
  height_ = dataset.Height();
  int max_ele = dataset.MaxEle();
  int min_ele = dataset.MinEle();
  image_ = {};
  for (size_t i = 0; i < height_; i++) {
    image_.push_back({});
  }
  // for each element in the dataset, find the shade of gray and apply it
  for (size_t i = 0; i < height_; ++i) {
    for (size_t j = 0; j < width_; ++j) {
      int elevation_point = dataset.DatumAt(i, j);
      int shade_of_gray = 0;
      if (min_ele == max_ele) {
        shade_of_gray = 0;
      } else {
        int numerator = elevation_point - min_ele;
        int denominator = max_ele - min_ele;
        double quotient = static_cast<double>(numerator)/denominator;
        shade_of_gray =
            std::round(quotient * kMaxColorValue);
      }
      Color color(shade_of_gray, shade_of_gray, shade_of_gray);
      image_.at(i).push_back(color);
    }
  }
}


size_t GrayscaleImage::Width() const { return width_; }
size_t GrayscaleImage::Height() const { return height_; }
unsigned int GrayscaleImage::MaxColorValue() const { return kMaxColorValue; }
const Color& GrayscaleImage::ColorAt(int row, int col) const {
  return image_.at(row).at(col);
}
const std::vector<std::vector<Color>>& GrayscaleImage::GetImage() const {
  return image_;
}

void GrayscaleImage::ToPpm(const std::string& name) const {
  std::ofstream ofs{name};
  if (!ofs.is_open()) {
      throw std::runtime_error("ofstream not opening");
  }
  ofs << "P3 \n" << width_ << ' ' << height_ << "\n" << "255 \n" << std::endl;
  for (size_t row = 0; row < height_; ++row) {
    for (size_t col = 0; col < width_; ++col) {
      Color this_color = image_.at(row).at(col);
      ofs << this_color.Red() << ' ' << this_color.Green() << ' ' << this_color.Blue() << ' ' << std::endl;
    }
    ofs << '\n' << std::endl;
  }
}