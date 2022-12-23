// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu:bionic               //
//  Date ......: 2021/02/10                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include <catch/catch.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>
#include <iostream>

#include "color.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"
#include "path_image.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("True == True", "") { REQUIRE(true == true); }

TEST_CASE("path_image 1 - tie") {
  std::string input =
      "/home/vagrant/src/mp-mountain-paths-ninaat2/example-data/ex_input_data/"
      "all-tie-row1-2w-3h.dat";
  ElevationDataset dataset(input, 2, 3);
  GrayscaleImage image(dataset);
  PathImage path_im(image, dataset);
  REQUIRE(path_im.Width() == 2);
  REQUIRE(path_im.Height() == 3);
  REQUIRE(path_im.Paths().at(0).GetPath().at(0) == 0);
  REQUIRE(path_im.Paths().at(0).GetPath().at(1) == 0);
  REQUIRE(path_im.Paths().at(1).GetPath().at(0) == 1);
  REQUIRE(path_im.Paths().at(1).GetPath().at(1) == 1);
  REQUIRE(path_im.Paths().at(2).GetPath().at(0) == 2);
  REQUIRE(path_im.Paths().at(2).GetPath().at(1) == 2);
}

TEST_CASE("5w 2h") {
  std::string input =
      "/home/vagrant/src/mp-mountain-paths-ninaat2/example-data/ex_input_data/"
      "prompt_5w_2h.dat";
  ElevationDataset dataset(input, 5, 2);
  GrayscaleImage image(dataset);
  PathImage path_im(image, dataset);
  REQUIRE(path_im.Width() == 5);
  REQUIRE(path_im.Height() == 2);
  REQUIRE(path_im.Paths().at(0).GetPath().at(0) == 0);
  REQUIRE(path_im.Paths().at(0).GetPath().at(1) == 0);
  REQUIRE(path_im.Paths().at(0).GetPath().at(2) == 1);
  // REQUIRE(path_im.Paths().at(0).GetPath().at(3) == 1);
  // REQUIRE(path_im.Paths().at(0).GetPath().at(4) == 1);
}

// TEST_CASE("part of 2 by 5") {
//   std::string input =
//   "/home/vagrant/src/mp-mountain-paths-ninaat2/example-data/ex_input_data/part
//   of 5by2.dat"; ElevationDataset dataset(input, 3, 2); GrayscaleImage
//   image(dataset); PathImage path_im(image, dataset); REQUIRE(path_im.Width()
//   == 3); REQUIRE(path_im.Height() == 2);
//   REQUIRE(path_im.Paths().at(0).GetPath().at(0) == 0);
//   REQUIRE(path_im.Paths().at(0).GetPath().at(1) == 1);
//   REQUIRE(path_im.Paths().at(0).GetPath().at(2) == 0);
//   REQUIRE(path_im.Paths().at(1).GetPath().at(0) == 1);
//   REQUIRE(path_im.Paths().at(1).GetPath().at(1) == 1);
//   REQUIRE(path_im.Paths().at(1).GetPath().at(2) == 0);
// }

// TEST_CASE("part of 2 by 5 flipped") {
//   std::string input =
//   "/home/vagrant/src/mp-mountain-paths-ninaat2/example-data/ex_input_data/part
//   of 5 by 2 flipped.dat"; ElevationDataset dataset(input, 2, 2);
//   GrayscaleImage image(dataset);
//   PathImage path_im(image, dataset);
//   REQUIRE(path_im.Width() == 2);
//   REQUIRE(path_im.Height() == 2);
//   // REQUIRE(path_im.Paths().at(1).GetPath().at(1) == 0);
// }

TEST_CASE("2 by 2 decrease") {
  std::string input =
      "/home/vagrant/src/mp-mountain-paths-ninaat2/example-data/ex_input_data/"
      "2 by 2 decrease.dat";
  ElevationDataset dataset(input, 2, 2);
  GrayscaleImage image(dataset);
  PathImage path_im(image, dataset);
  REQUIRE(path_im.Paths().at(0).GetPath().at(1) == 1);
}

TEST_CASE("negatives, decrease") {
  std::string input =
      "/home/vagrant/src/mp-mountain-paths-ninaat2/example-data/ex_input_data/negatives, increase.dat";
  ElevationDataset dataset(input, 2, 3);
  GrayscaleImage image(dataset);
  PathImage path_im(image, dataset);
  REQUIRE(path_im.Paths().at(1).GetPath().at(1) == 0);
}

TEST_CASE("2 by 3 increase") {
  std::string input =
      "/home/vagrant/src/mp-mountain-paths-ninaat2/example-data/ex_input_data/"
      "2 by 3 increase value.dat";
  ElevationDataset dataset(input, 2, 3);
  GrayscaleImage image(dataset);
  PathImage path_im(image, dataset);
  REQUIRE(path_im.Paths().at(1).GetPath().at(1) == 2);
}

TEST_CASE("2 by 2") {
  std::string input =
      "/home/vagrant/src/mp-mountain-paths-ninaat2/example-data/ex_input_data/"
      "test2by2.dat";
  ElevationDataset dataset(input, 2, 2);
  GrayscaleImage image(dataset);
  PathImage path_im(image, dataset);
  REQUIRE(path_im.Paths().at(1).GetPath().at(1) == 0);
}

TEST_CASE("all 1's") {
  std::string input =
      "/home/vagrant/src/mp-mountain-paths-ninaat2/example-data/ex_input_data/"
      "all 1s 2 by 2.dat";
  ElevationDataset dataset(input, 2, 2);
  GrayscaleImage image(dataset);
  PathImage path_im(image, dataset);
  REQUIRE(path_im.Width() == 2);
  REQUIRE(path_im.Height() == 2);
  REQUIRE(path_im.Paths().at(0).GetPath().at(0) == 0);
  REQUIRE(path_im.Paths().at(0).GetPath().at(1) == 0);
  REQUIRE(path_im.Paths().at(1).GetPath().at(0) == 1);
  REQUIRE(path_im.Paths().at(1).GetPath().at(1) == 1);
}

TEST_CASE("all 1's 3 by 3") {
  std::string input =
      "/home/vagrant/src/mp-mountain-paths-ninaat2/example-data/ex_input_data/"
      "all 1s 3 by 3.dat";
  ElevationDataset dataset(input, 3, 3);
  GrayscaleImage image(dataset);
  PathImage path_im(image, dataset);
  REQUIRE(path_im.Width() == 3);
  REQUIRE(path_im.Height() == 3);
  REQUIRE(path_im.Paths().at(0).GetPath().at(0) == 0);
  REQUIRE(path_im.Paths().at(0).GetPath().at(1) == 0);
  REQUIRE(path_im.Paths().at(0).GetPath().at(2) == 0);
  REQUIRE(path_im.Paths().at(1).GetPath().at(0) == 1);
  REQUIRE(path_im.Paths().at(1).GetPath().at(1) == 1);
  REQUIRE(path_im.Paths().at(1).GetPath().at(2) == 1);
  REQUIRE(path_im.Paths().at(2).GetPath().at(0) == 2);
}

TEST_CASE("up down up") {
  std::string input =
      "/home/vagrant/src/mp-mountain-paths-ninaat2/example-data/ex_input_data/"
      "up down up.dat";
  ElevationDataset dataset(input, 3, 2);
  GrayscaleImage image(dataset);
  PathImage path_im(image, dataset);
  REQUIRE(path_im.Width() == 3);
  REQUIRE(path_im.Height() == 2);
  REQUIRE(path_im.Paths().at(0).GetPath().at(0) == 0);
  REQUIRE(path_im.Paths().at(0).GetPath().at(1) == 1);
  REQUIRE(path_im.Paths().at(0).GetPath().at(2) == 0);
  REQUIRE(path_im.Paths().at(1).GetPath().at(0) == 1);
  REQUIRE(path_im.Paths().at(1).GetPath().at(1) == 0);
  REQUIRE(path_im.Paths().at(1).GetPath().at(2) == 1);
}

TEST_CASE("path image to ppm") {
  std::string input =
      "/home/vagrant/src/mp-mountain-paths-ninaat2/example-data/ex_input_data/map-input-w51-h55.dat";
  ElevationDataset dataset(input, 51, 55);
  GrayscaleImage image(dataset);
  PathImage path_im(image, dataset);
  std::string name = " ";
  path_im.ToPpm(name);
  std::cout << name << std::endl;
  REQUIRE(path_im.Width() == 51);
  REQUIRE(path_im.Height() == 55);
}

/////////////////////////////////////////////////////////////////////////////////////////////