#include "elevation_dataset.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

ElevationDataset::ElevationDataset(const std::string& filename, size_t width, size_t height) {
  if (width == 0 || height == 0) {
    throw std::invalid_argument("height, width issue");
  }
  width_ = width;
  height_ = height;
  for (size_t i = 0; i < height; i++) {
    data_.push_back({});
  }
  std::ifstream ifs(filename);
  if (!ifs.is_open()) {
    throw std::out_of_range("not opening");
  }
  int value = 0;
  unsigned long position = 0;
  bool initialized_min_max = false;
  while (ifs.good()) {
    ifs >> value;
    if (ifs.fail()) {
      ifs.clear();
      ifs.ignore(kMaxLength, ' ');
    } else {
      int row = static_cast<int>(position / width);
      data_.at(row).push_back(value);
      if (!initialized_min_max) {
        max_ele_ = data_.at(0).at(0);
        min_ele_ = data_.at(0).at(0);
        initialized_min_max = true;
      }
      if (value > max_ele_) {
        max_ele_ = value;
      } else if (value < min_ele_) {
        min_ele_ = value;
      }
      ++position;
    }
  }
  if (position < (width_ * height_) - 1) {
    throw std::out_of_range("too few inputs");
  }
}

size_t ElevationDataset::Width() const { return width_; }

size_t ElevationDataset::Height() const { return height_; }

int ElevationDataset::MaxEle() const { return max_ele_; }

int ElevationDataset::MinEle() const { return min_ele_; }

int ElevationDataset::DatumAt(size_t row, size_t col) const {
  return data_.at(row).at(col);
}

const std::vector<std::vector<int>>& ElevationDataset::GetData() const {
  return data_;
}