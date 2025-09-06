//
//  CityTemperatureData.cpp
//
//  Implementation of CityTemperatureData
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

#include "CityTemperatureData.h"

using namespace std;

namespace csi281 {
  // Fill in all instance variables for CityTemperatureData.
  // Data will be stored in an array of CityYear instances.
  CityTemperatureData::CityTemperatureData(const string name, CityYear data[], int numYears)
      : _name(name), _data(data), _count(numYears) {

  }

  // Release any memory connected to CityTemperatureData.
  CityTemperatureData::~CityTemperatureData() {
    delete _data;
  }

  // Look up a CityYear instance held by CityTemperatureData by its year.
  // Find the right CityYear in the array and return it
  const CityYear CityTemperatureData::operator[](const int year) const {
    //it loops untill the value of i is grater than the value of _count and everytime it loops it tests
    //if the data value at index i .year is the same as the year and if it is then it retruns the value of _data
    //at index i but if it exits the loop it returns CityYear with 0s in all of the values somewhat as a sign that it failed
   for (int i = 0; i < _count; i++) {
     if (_data[i].year == year) {
       return _data[i];
     }
   }

    return CityYear{0,0,0,0,0,0};
  }


  // Get the average (mean) temperature of all time for this city
  // by averaging every CityYear.
  float CityTemperatureData::getAllTimeAverage() const {
    //it sets the total to 0 and then it loops until i is grater than _count and every time it loops it takes the total and adds
    //the total plus the _data value at index i of the .averageTempature then when it exits the loop it returns the total devied by the count
  float total = 0;
    for (int i = 0; i < _count; i++) {
      total += _data[i].averageTemperature;
    }
    return total / _count;

  }

  // Sum all of the days below 32 for all years.
  int CityTemperatureData::getTotalDaysBelow32() const {
    //sets the total to 0 and then it loops until i is grater than _count and everytime it loops it sets the value of total to be total plus the value of _data at the
    //i index of the numDaysBelow32 and then when it exits the loop it returns the total
    int total = 0;
    for (int i = 0; i < _count; i++) {
      total += (_data)[i].numDaysBelow32;
    }
    return total;
  }

  // Sum all of the days above 90 for all years.
  int CityTemperatureData::getTotalDaysAbove90() const {
    //sets the value of total and then it loops until i is grater than _count and everytime it loops it sets the total to the total plus
    //the vaule of _data at the index of i of the numDaysAbove90 and then when it exits the loop it returns the total
    int total = 0;
    for (int i = 0; i < _count; i++) {
      total += (_data)[i].numDaysAbove90;
    }
    return total;
  }
}  // namespace csi281
