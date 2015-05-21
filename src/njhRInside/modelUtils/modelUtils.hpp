#pragma once
/*
 * modelUtils.hpp
 *
 *  Created on: May 20, 2015
 *      Author: nickhathaway
 */

#include "njhRInside/common.h"


namespace njhRInside {

std::unordered_map<std::string, std::vector<double>> getModelQualError(
    const std::vector<double>& qualVec, const std::vector<double>& errorVec,
    const std::vector<double>& weightVec, uint32_t qualStart, uint32_t qualStop,
    double qualStep, const std::string& model);
std::unordered_map<std::string, std::vector<double>> getModelQualError(
    const std::unordered_map<std::string, std::vector<double>>& data,
    uint32_t qualStart, uint32_t qualStop, double qualStep,
    const std::string& model);
std::unordered_map<double, double> createLikelihoodMap(
    const std::unordered_map<std::string, std::vector<double>>& predOut);


} /* namespace njhRInside */
