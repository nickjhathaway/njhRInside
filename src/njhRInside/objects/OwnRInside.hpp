#pragma once
/*
 * OwnRInside.hpp
 *
 *  Created on: May 20, 2015
 *      Author: nickhathaway
 */

#include "njhRInside/common.h"
#include <RInside.h>

namespace njhRInside {

class OwnRInside {
 private:
  static std::unique_ptr<RInside> rSession_;

 public:
  OwnRInside();
  ~OwnRInside();

  RInside& get();
  // installing/loading libraries
  void installLib(const std::string & lib, uint32_t numThreads);
  void loadLib(const std::string& lib);
  // dealing with graphing devices
  void openPdfDevice(std::string pdfFilename, double width, double height);
  void closeCurrentDevice();
  // multiple commands
  void multipleParseEvalQ(const VecStr& cmds);
};


} /* namespace njhRInside */
