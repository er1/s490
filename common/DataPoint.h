/*
   Copyright 2012 Corey Clayton, Eric Chan, Mathieu Dumais-Savard

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef DATAPOINT_H
#define	DATAPOINT_H

#include "string.h"
#include "common.h"
#include <vector>

class DataPoint : public std::vector<uint8_t> {
public:

    inline DataPoint() : std::vector<uint8_t>() {
    };

    inline DataPoint(const DataPoint& orig) : std::vector<uint8_t>(orig) {
    };

    inline DataPoint(const DataPoint::const_iterator start, const DataPoint::const_iterator end) : std::vector<uint8_t>(start, end) {
    };


    // set the contents of this datapoint to the argument point passed in

    template <typename T>
    void wrap(const T& point) {
        resize(sizeof (T));
        memcpy(&front(), &point, sizeof (T));
    }

    // return as template type the value stored in this datapoint
    // TODO: the case where dataPoint does not contain type T;

    template <typename T>
    T unwrap() const {
        if (sizeof (T) != size()) {
            log("DataPoint was unwrapped as wrong type got %lu bytes for a %lu byte type.\n", size(), sizeof (T));
        }
        return *(T*) & front();
    }

    //
};

#endif	/* DATAPOINT_H */

