#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "Projekt1.h"


using namespace std;

// Function to calculate the exponential moving average (EMA) of a vector of values
vector<double> calculateEMA(vector<double> values, int period) 
{
    vector<double> ema;
    double multiplier = 1.0 - (2.0 / (period + 1.0));
    double exponent = 0.0;
    double denominator = 0.0;
    for (int i = 0; i < values.size(); i++) 
    {
        exponent = 0.0;
        denominator = 0.0;
        for (int j = 0; j <= period; j++)
        {
            double temp = pow(multiplier, j);
            if (i - j > 0)
            {
                exponent += temp * values[i - j];
                denominator += temp;
            }
        }
        ema.push_back(exponent / denominator);
    }
    return ema;
}

// Function to calculate the MACD of a vector of values
vector<double> calculateMACD(vector<double> values) 
{
    vector<double> macd;
    vector<double> ema12 = calculateEMA(values, 12);
    vector<double> ema26 = calculateEMA(values, 26);
    for (int i = 0; i < values.size(); i++) 
    {
        if (i < 26)
        {
            macd.push_back(0.0);
        }
        else
        {
            macd.push_back(ema12[i] - ema26[i]);
        }
    }
    return macd;
}

// Function to calculate the signal line of a vector of MACD values
vector<double> calculateSignalLine(vector<double> macd) 
{
    vector<double> signalLine;
    vector<double> ema9 = calculateEMA(macd, 9);
    for (int i = 0; i < macd.size(); i++) 
    {
        if (i < 35)
        {
            signalLine.push_back(0.0);
        }
        else
        {
            signalLine.push_back(ema9[i]);
        }
    }
    return signalLine;
}

// Fucntion to save vectors with results to txt files
void SaveToFile(std::vector<double>& macd, std::vector<double>& signalLine)
{
    std::ofstream outFile("WynikiMacd.txt");

    // Check if the file was opened successfully
    if (outFile.is_open()) {
        // Iterate over the vector and write each element to the file
        for (double element : macd) {
            outFile << element << std::endl;
        }

        // Close the file
        outFile.close();
        std::cout << "Vector saved to file." << std::endl;
    }
    else {
        std::cout << "Unable to open file." << std::endl;
    }

    std::ofstream outFile1("WynikiSignal.txt");

    // Check if the file was opened successfully
    if (outFile1.is_open()) {
        // Iterate over the vector and write each element to the file
        for (double element : signalLine) {
            outFile1 << element << std::endl;
        }

        // Close the file
        outFile1.close();
        std::cout << "Vector saved to file." << std::endl;
    }
    else {
        std::cout << "Unable to open file." << std::endl;
    }
}

// Function to read values from txt file to vector
void ReadFromFile(std::vector<double>& values, string fileName)
{
    ifstream inputFile(fileName);
    double value;

    while (inputFile >> value) {
        values.push_back(value);
    }
    inputFile.close();

   /* double* tab = new double[values.size()];
    for (int i = 0; i < values.size(); i++)
    {
        tab[values.size() - i - 1] = values[i];
    }
    for (int i = 0; i < values.size(); i++)
    {
         values[i] = tab[i];
    }*/
}

// Function to automatically buy/sell stock depending on macd and signal line
void BuySellAlgorithm(std::vector<double>& values, std::vector<double>& macd, std::vector<double>& signalLine)
{
    double cash = 1000.0;
    double shares = 0.0;
    double price = 0.0;
    bool holding = false;
    double stopLoss = 0.95;
    double takeProfit = 1.05;
    double stopLossPrice = 0.0;
    double takeProfitPrice = 0.0;

    // Loop through the historical data
    for (int i = 0; i < values.size(); i++)
    {
        // Check for buy signal
        if (macd[i] > signalLine[i] && !holding)
        {
            price = values[i];
            shares = cash / price;
            cash = 0.0;
            holding = true;
            stopLossPrice = price * stopLoss;
            takeProfitPrice = price * takeProfit;
        }

        // Check for sell signal
        if (macd[i] < signalLine[i] && holding)
        {
            price = values[i];
            cash = shares * price;
            shares = 0.0;
            holding = false;
            stopLossPrice = 0.0;
            takeProfitPrice = 0.0;
        }

        // Check for stop loss or take profit
        if (holding && (values[i] <= stopLossPrice || values[i] >= takeProfitPrice))
        {
            price = values[i];
            cash = shares * price;
            shares = 0.0;
            holding = false;
            stopLossPrice = 0.0;
            takeProfitPrice = 0.0;
        }
    }

    // Print final results
    cout << "Final cash balance: " << cash << endl;
    cout << "Final shares balance: " << shares << endl;
    cout << "Total value: " << cash + shares * values.back() << endl;
}

// Function to print values of macd and signal line
void Print(std::vector<double>& values, std::vector<double>& macd, std::vector<double>& signalLine)
{
    for (int i = 0; i < values.size(); i++) {
        cout << "MACD: " << macd[i] << " Signal Line: " << signalLine[i] << endl;
    }
}

// Fucntion to perform all actions required
void StartProgram(string fName)
{
    vector<double> values;
    // Open the input file and read the values into a vector

    ReadFromFile(values, fName);


    // Calculate the MACD and signal line of the values
    vector<double> macd = calculateMACD(values);
    vector<double> signalLine = calculateSignalLine(macd);

    // Save results to txt files to generate charts later
    SaveToFile(macd, signalLine);


    // Print the MACD and signal line values to the console
    //Print(values, macd, signalLine);

    // Run algorithm to earn some money :)
    BuySellAlgorithm(values, macd, signalLine);
}

int main() 
{
    //string fileName = "Wig20Otwarcie.txt";
    //StartProgram(fileName);

    string fileName = "a.txt";
    StartProgram(fileName);
    return 0;
}


