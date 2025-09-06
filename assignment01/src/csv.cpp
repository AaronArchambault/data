//
//  csv.cpp
//
//  Functions for reading CSV files.
//  You SHOULD modify this file.
//
//  Copyright 2019 David Kopec
// Aaron Archambault
//  Permission is hereby granted, free of charge, to any person
//  obtaining a copy of this software and associated documentation files
//  (the "Software"), to deal in the Software without restriction,
//  including without limitation the rights to use, copy, modify, merge,
//  publish, distribute, sublicense, and/or sell copies of the Software,
//  and to permit persons to whom the Software is furnished to do so,
//  subject to the following conditions:
//
//  The above copyright notice and this permission notice
//  shall be included in all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
//  OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
//  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//  OTHER DEALINGS IN THE SOFTWARE.

#include "csv.h"

#include <algorithm>  // for remove_if()
#include <iostream>
#include <sstream>


using namespace std;

namespace csi281 {
  // Remove extraneous characters from string so it can
  // be converted into a number
  void clean(string &str) {

    const string unwanted = "\"\' \t\n";
    str.erase(
        remove_if(str.begin(), str.end(), [&](char c) {
          return unwanted.find(c) != string::npos;
        }), str.end());

  }

  // Read from an input string stream we hit the next comma, or the end
  // and try to convert it into the float we seek.
  float readFloatCell(istringstream &iss) {
    string holder;
    getline(iss, holder, ',');
    clean(holder);
    if (holder.empty()) return 0; //tests if the holder is empty or not and if it is then it returns 0
    return stof(holder);
  }

  // Read from an input string stream, we hit the next comma, or the end
  // and try to convert it into the int we seek.
  int readIntCell(istringstream &iss) {
    string holder;
    getline(iss, holder, ',');
    clean(holder);
    if (holder.empty()) return 0; //tests if the holder is empty or not and if it is then it returns 0
    return stoi(holder);
  }

  // Read from a input string stream we hit the next comma, or the end
  // and try to convert it into the string we seek.
  string readStringCell(istringstream &iss) {
    string holder;
    getline(iss, holder, ',');
    return holder;
  }

  // Read a single line from a file stream and turn it into a CityYear
  // You'll want to use the standard library function getline()
  // and the readCell() functions above
  // You'll also want to construct a CityYear from what you have read from the file
  CityYear readLine(ifstream &file) {
    //first test if it can not get the file to read with getline and if it can't it returns a defult/empty cityyear with all 0s
    string line;
    if (!getline(file, line)) {
      return CityYear{0,0,0,0,0};
    }

    istringstream iss(line);
//take the first 2 "lines" of the file that are the stationID and name and put them in the local variables so that
    //the other variables that the program need don't take in those values/readings and put them in the wrong place
    string stationID = readStringCell(iss);
    string name = readStringCell(iss);

//creates yearData and then it reads the data from the file and the line that it is on into each of the variables
    //then it returns the yearData with all the line informaiton that it needed
    CityYear yearData;
    yearData.year = readIntCell(iss);
    yearData.numDaysBelow32 = readIntCell(iss);
    yearData.numDaysAbove90 = readIntCell(iss);
    yearData.averageTemperature = readFloatCell(iss);
    yearData.averageMax = readFloatCell(iss);
    yearData.averageMin = readFloatCell(iss);
    return yearData;

  }

  // Read city by looking at the specified lines in the CSV
  // You'll need to open an ifstream to fileName
  // You'll need to read CityYears from the file using readLine() until there
  // is nothing left to read
  // The ifstream method good() may be useful
  // Make sure to just read between startLine and endLine (inclusive of endLine)
  // Construct a CityTemperatureData and return it
  // create an array of CityYear instances to pass to the CityTemperatureData constructor
  // when the CityTemperatureData is created, it will take ownership of the array
  CityTemperatureData* readCity(string cityName, string fileName, int startLine, int endLine) {
    //uses ifstream to open the file and then it test if the file opened or not and if it did not then
    // it cout/prints it to the user that there was an error opening file name and then it returns a null pointer
    ifstream file(fileName);
    if (!file.is_open()) {
      cout << "Error opening file " << fileName << endl;
      return nullptr;
    }
//creates a string to hold the first line of the file which is the header and uses getline to store it
    //so that it is not stored in the data that is needed
    string header;
    getline(file, header);
//creates a string called skip so that it can skip the stating line and not get any of the informaiton that it does not need
    string skip;
    for (int i = 1; i < startLine; i++) {
      getline(file, skip);
    }
//takes the endline vaule and subtracts the startline value and adds 1 so that it can keep track of the number of years
    //so that it can use that number as the array index to keep the array correct and not overwrite anything that is need
    //then it creates a cityYear* data variable and sets it to a new(memory location on the heap) that is cityyear[numYears]
    int numYears = endLine - startLine + 1;
    CityYear* data = new CityYear[numYears];
    //loops untill i is grater than the numYears and when it loops it check if the file is good/ if it is
    //than it sets the data value of the array at index value of i to whant the readLine values return
    //if the file is not good than it sets the data value at the index i to a default value of cityYear with all 0s
    for (int i = 0; i < numYears; i++) {
      if (file.good()) {
        data[i] = readLine(file);
      } else {
        data[i] = CityYear{0,0,0,0,0};
      }
    }
//then it closes the file and returns a "new" citytemperatucedata with the values that it has gotten of cityname, data, and numYears
    file.close();
    return new CityTemperatureData(cityName, data, numYears);
  }
    // namespace csi281
}