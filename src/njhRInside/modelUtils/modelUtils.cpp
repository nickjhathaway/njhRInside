/*
 * modelUtils.cpp
 *
 *  Created on: May 20, 2015
 *      Author: nickhathaway
 */

#include "modelUtils.hpp"

namespace njhRInside {


std::unordered_map<std::string, std::vector<double>> getModelQualError(
    const std::unordered_map<std::string, std::vector<double>>& data,
    uint32_t qualStart, uint32_t qualStop, double qualStep,
    const std::string& model) {
  return getModelQualError(data.at("qual"), data.at("error"), data.at("weight"),
                           qualStart, qualStop, qualStep, model);
}

std::unordered_map<std::string, std::vector<double>> getModelQualError(
    const std::vector<double>& qualVec, const std::vector<double>& errorVec,
    const std::vector<double>& weightVec, uint32_t qualStart, uint32_t qualStop,
    double qualStep, const std::string& model) {
  ownRInside ownSession;

  Rcpp::DataFrame inData = Rcpp::DataFrame::create(
      Rcpp::Named("qual") = qualVec, Rcpp::Named("error") = errorVec,
      Rcpp::Named("weight") = weightVec);
  auto& r = ownSession.get();
  r["inData"] = inData;
  r.parseEvalQ("myModel <- glm(error ~ qual, family = binomial(link = \"" +
               model + "\"), data = inData, weights= weight);");
  std::string seqStrCmd = std::to_string(qualStart) + "," + std::to_string(qualStop) +
                          ",by=" + std::to_string(qualStep);
  r.parseEvalQ("qTable = data.frame(qual = seq(" + seqStrCmd + "));");
  r.parseEvalQ(
      "qTable[, c(\"p\", \"se\")] <- predict(myModel, qTable, type = "
      "\"response\", se.fit = TRUE)[-3];");
  // R.parseEvalQ("print(qTable);");
  r.parseEvalQ("qTable_mat = as.matrix(qTable);");
  // R.parseEvalQ("cat(qTable_mat, sep =" ");");
  std::string txt = "qTable_mat;";
  Rcpp::NumericMatrix outData = r.parseEval(txt);
  std::unordered_map<std::string, std::vector<double>> out;

  std::vector<double> qualOut;
  for (auto i : iter::range(outData.nrow())) {
    qualOut.emplace_back(outData(i, 0));
  }
  out["qual"] = qualOut;

  std::vector<double> predOut;
  for (auto i : iter::range(outData.nrow())) {
    predOut.emplace_back(outData(i, 1));
  }
  out["pred"] = predOut;
  std::vector<double> seOut;
  for (auto i : iter::range(outData.nrow())) {
    seOut.emplace_back(outData(i, 2));
  }
  out["se"] = seOut;
  return out;
}

std::unordered_map<double, double> createLikelihoodMap(
    const std::unordered_map<std::string, std::vector<double>>& predOut) {
  std::vector<double> qualVec = predOut.at("qual");
  std::vector<double> predVec = predOut.at("pred");
  std::unordered_map<double, double> ans;
  for (const auto& i : iter::range(qualVec.size())) {
    ans[roundDecPlaces(qualVec[i], 2)] = predVec[i];
  }
  return ans;
}


} /* namespace njhRInside */
