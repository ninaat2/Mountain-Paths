#ifndef PATH_IMAGE_H
#define PATH_IMAGE_H

#include <cstdlib>  // for size_t
#include <vector>

#include "color.hpp"
#include "path.hpp"
#include "grayscale_image.hpp"

class PathImage {
public:
  PathImage(const GrayscaleImage &image, const ElevationDataset &dataset);
  size_t Width() const;
  size_t Height() const;
  unsigned int MaxColorValue() const;
  const std::vector<Path>& Paths() const;
  const std::vector<std::vector<Color> >& GetPathImage() const;
  void ToPpm(const std::string& name) const;
private:
  std::vector<Path> paths_;
  size_t width_ = 0;
  size_t height_ = 0;
  std::vector<std::vector<Color>> path_image_;
  static const int kMaxColorValue = 255;
  void CreatePath(size_t start_row, const ElevationDataset &dataset);
  const int kGreenRed = 31;
  const int kGreenGreen = 253;
  const int kGreenBlue = 13;
  const int kRedRed = 252;
  const int kRedGreen = 25;
  const int kRedBlue = 63;
  void TopRow(const ElevationDataset& dataset, Path& path, int& col, size_t& current_row);
  void MiddleRow(const ElevationDataset& dataset, Path& path, int& col, size_t& current_row);
  void BottomRow(const ElevationDataset& dataset, Path& path, int& col, size_t& current_row);
};

#endif