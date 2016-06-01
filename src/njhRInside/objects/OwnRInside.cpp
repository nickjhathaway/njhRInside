/*
 * OwnRInside.cpp
 *
 *  Created on: May 20, 2015
 *      Author: nickhathaway
 */

#include "OwnRInside.hpp"

namespace njhRInside {


std::unique_ptr<RInside> OwnRInside::rSession_ = std::unique_ptr<RInside>();

OwnRInside::OwnRInside() {
  if (!rSession_) {
    rSession_.reset(new RInside());
  }
}

OwnRInside::~OwnRInside() {
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

void OwnRInside::multipleParseEvalQ(const VecStr& cmds) {
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

void OwnRInside::openPdfDevice(std::string pdfFilename, double pageWidth,
		double pageHeight) {
	std::stringstream txt;
	std::string widthStr = std::to_string(pageWidth);
	std::string heightStr = std::to_string(pageHeight);
	if (!endsWith(pdfFilename, ".pdf")) {
		pdfFilename.append(".pdf");
	}
	txt << "pdf(\"" << pdfFilename << "\", width=" << widthStr << ", height="
			<< heightStr << ", useDingbats = F);";
	auto& r = get();
	r.parseEvalQ(txt.str());
}

void OwnRInside::closeCurrentDevice(){
  auto& r = get();
  r.parseEvalQ("dev.off();");
}

RInside& OwnRInside::get() {
	return *rSession_;
}


void OwnRInside::installLib(const std::string & lib, uint32_t numThreads) {

	std::stringstream libCmd;
	libCmd << "install.packages(c(\"" << lib << "\"), repos=\"http://cran.us.r-project.org\",";
	libCmd << " Ncpus = " << numThreads << ", lib =.libPaths()[length(.libPaths()  )])";
  auto& r = get();
  r.parseEvalQ(libCmd.str());
}


void OwnRInside::loadLib(const std::string& lib) {
	auto& r = get();
	r.parseEvalQ("suppressMessages(library(" + lib + "))");  // load library, no return value
}





} /* namespace njhRInside */
