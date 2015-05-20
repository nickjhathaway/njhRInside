/*
 * OwnRInside.cpp
 *
 *  Created on: May 20, 2015
 *      Author: nickhathaway
 */

#include "OwnRInside.hpp"

namespace njhRInside {


std::unique_ptr<RInside> ownRInside::rSession_ = std::unique_ptr<RInside>();

ownRInside::ownRInside() {
  if (!rSession_) {
    rSession_.reset(new RInside());
  }
}

ownRInside::~ownRInside() {
  if (rSession_) {
    rSession_->parseEvalQ("rm(list = ls())");

    // according this, we can't terminate the actual R instance via "quit()"
    // http://r.789695.n4.nabble.com/Terminating-and-restarting-an-embedded-R-instance-possible-td4641823.html
    // so this is not allowed:
    // rSession_->parseEvalQ("quit()");

    // can't do this because Rf_endEmbeddedR(0) doesn't actually terminate R
    // rSession_.reset();
  }
}
void ownRInside::multipleParseEvalQ(const VecStr& cmds) {
  auto& r = get();
  for (const auto& cmd : cmds) {
    r.parseEvalQ(cmd);
  }
}

bool endsWith(const std::string& a, const std::string& b) {
  // http://stackoverflow.com/a/874160
  if (a.size() >= b.size()) {
    return (0 == a.compare(a.size() - b.size(), b.size(), b));
  }
  return false;
}

void ownRInside::openPdfDevice(const std::string & pdfFilename, double pageWidth, double pageHeight){
  std::stringstream txt;
  std::string widthStr = std::to_string(pageWidth);
  std::string heightStr = std::to_string(pageHeight);
	if(endsWith(pdfFilename, ".pdf")){
		txt << "pdf(\"" << pdfFilename << "\", width=" << widthStr << ", height=" << heightStr << ");";
	}else{
		txt << "pdf(\"" << pdfFilename << ".pdf" << "\", width=" << widthStr << ", height=" << heightStr << ");";
	}
  auto& r = get();
  r.parseEvalQ(txt.str());
}
void ownRInside::closeCurrentDevice(){
  std::string txt = "dev.off();";
  auto& r = get();

  r.parseEvalQ(txt);
}


} /* namespace njhRInside */
