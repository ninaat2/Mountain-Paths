#include "path_image.hpp"

#include <fstream>
#include <stdexcept>
#include <string>

#include "grayscale_image.hpp"

PathImage::PathImage(const GrayscaleImage& image,
                     const ElevationDataset& dataset) {
  if (dataset.Height() == 0 || dataset.Width() == 0) {
    throw std::out_of_range("0 width, height");
  }
  paths_ = {};
  path_image_ = image.GetImage();
  width_ = dataset.Width();
  height_ = dataset.Height();

  for (size_t start_row = 0; start_row < height_; ++start_row) {
    CreatePath(start_row, dataset);
  }

  for (int i = 0; i < static_cast<int>(paths_.size()); ++i) {
    for (int col = 0; col < static_cast<int>(width_); ++col) {
      int row = static_cast<int>(paths_.at(i).GetPath().at(col));
      path_image_.at(row).at(col) = Color(kRedRed, kRedGreen, kRedBlue);
    }
  }

  size_t min_ele_change = paths_.at(0).EleChange();
  size_t min_ele_change_path = 0;
  for (size_t path_count = 1; path_count < paths_.size(); ++path_count) {
    if (paths_.at(path_count).EleChange() < min_ele_change) {
      min_ele_change = paths_.at(path_count).EleChange();
      min_ele_change_path = path_count;
    }
  }
  for (size_t col = 0; col < width_; ++col) {
    size_t row = paths_.at(min_ele_change_path).GetPath().at(col);
    path_image_.at(row).at(col) = Color(kGreenRed, kGreenGreen, kGreenBlue);
  }
}

void PathImage::CreatePath(size_t start_row, const ElevationDataset& dataset) {
  Path path(width_, start_row);
  path.SetLoc(0, start_row);
  size_t current_row = start_row;
  for (int col = 1; col < static_cast<int>(width_); ++col) {
    if (current_row != 0 && current_row != height_ - 1) {
      MiddleRow(dataset, path, col, current_row);
    } else if (current_row == 0) {
      TopRow(dataset, path, col, current_row);
    } else {
      BottomRow(dataset, path, col, current_row);
    }
  }
  paths_.push_back(path);
}

void PathImage::MiddleRow(const ElevationDataset& dataset,
                         Path& path,
                         int& col,
                         size_t& current_row) {
  int min_change_row = 0;
  int min_change = 0;
  int previous_value = dataset.DatumAt(current_row, col - 1);
  int same_change = abs(previous_value - dataset.DatumAt(current_row, col));
  min_change = same_change;
  min_change_row = current_row;
  int down_change = abs(previous_value - dataset.DatumAt(current_row + 1, col));
  if (down_change < min_change) {
    min_change = down_change;
    min_change_row = current_row + 1;
    current_row += 1;
  }
  int up_change = abs(previous_value - dataset.DatumAt(current_row - 1, col));
  if (up_change < min_change) {
    min_change = up_change;
    min_change_row = current_row - 1;
    current_row -= 1;
  }
  path.SetLoc(col, min_change_row);
  if (min_change > 0) {
    path.IncEleChange(min_change);
  } else if (min_change < 0) {
    throw std::out_of_range("incrementing by negative");
  }
}

void PathImage::BottomRow(const ElevationDataset& dataset,
                         Path& path,
                         int& col,
                         size_t& current_row) {
  int min_change_row = 0;
  int min_change = 0;
  int previous_value = dataset.DatumAt(current_row, col - 1);
  int same_change = abs(previous_value - dataset.DatumAt(current_row, col));
  min_change = same_change;
  min_change_row = current_row;
  int up_change = abs(previous_value - dataset.DatumAt(current_row - 1, col));
  if (up_change < min_change) {
    min_change = up_change;
    min_change_row = current_row - 1;
    current_row -= 1;
  }
  path.SetLoc(col, min_change_row);
  if (min_change > 0) {
    path.IncEleChange(min_change);
  } else if (min_change < 0) {
    throw std::out_of_range("incrementing by negative");
  }
}

void PathImage::TopRow(const ElevationDataset& dataset,
                      Path& path,
                      int& col,
                      size_t& current_row) {
  int min_change_row = 0;
  int min_change = 0;
  int previous_value = dataset.DatumAt(current_row, col - 1);
  int same_change = abs(previous_value - dataset.DatumAt(current_row, col));
  min_change = same_change;
  min_change_row = current_row;
  int down_change = abs(previous_value - dataset.DatumAt(current_row + 1, col));
  if (down_change < min_change) {
    min_change = down_change;
    min_change_row = current_row + 1;
    current_row += 1;
  }
  path.SetLoc(col, min_change_row);
  if (min_change > 0) {
    path.IncEleChange(min_change);
  } else if (min_change < 0) {
    throw std::out_of_range("incrementing by negative");
  }
}

size_t PathImage::Width() const { return width_; }
size_t PathImage::Height() const { return height_; }
unsigned int PathImage::MaxColorValue() const { return kMaxColorValue; }
const std::vector<Path>& PathImage::Paths() const { return paths_; }
const std::vector<std::vector<Color>>& PathImage::GetPathImage() const {
  return path_image_;
}

void PathImage::ToPpm(const std::string& name) const {
  std::ofstream ofs{name};
  if (!ofs.is_open()) {
    throw std::runtime_error("ofstream not opening");
  }
  ofs << "P3 \n" << width_ << ' ' << height_ << "\n" << "255 \n";
  for (size_t row = 0; row < height_; ++row) {
    for (size_t col = 0; col < width_; ++col) {
      Color this_color = path_image_.at(row).at(col);
      ofs << this_color.Red() << ' ' << this_color.Green() << ' ' << this_color.Blue() << ' ';
    }
    ofs << '\n';
  }
}