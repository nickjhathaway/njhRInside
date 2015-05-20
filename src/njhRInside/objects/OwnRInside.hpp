/*
 * OwnRInside.hpp
 *
 *  Created on: May 20, 2015
 *      Author: nickhathaway
 */


namespace njhRInside {
#include "njhRinside/common.h"
#include <RInside.h>

class OwnRInside {
 private:
  static std::unique_ptr<RInside> rSession_;

 public:
  OwnRInside();
  ~OwnRInside();

  RInside& get() { return *rSession_; }
  // installing libraries
  void installLib(const std::string& lib);
  void openPdfDevice(const std::string & pdfFilename, double width, double height);
  void closeCurrentDevice();
  // multiple commands
  void multipleParseEvalQ(const VecStr& cmds);
};
} /* namespace njhRInside */
