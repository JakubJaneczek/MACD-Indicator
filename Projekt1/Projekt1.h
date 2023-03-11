#pragma once

void SaveToFile(std::vector<double>& macd, std::vector<double>& signalLine);

void BuySellAlgorithm(std::vector<double>& values, std::vector<double>& macd, std::vector<double>& signalLine);

void Print(std::vector<double>& values, std::vector<double>& macd, std::vector<double>& signalLine);

void StartProgram();

void ReadFromFile(std::vector<double>& values);
