#ifndef DATAPOINT_H
#define	DATAPOINT_H

#include "../common/common.h"
#include "string.h"

class DataPoint : public std::vector<uint8_t> {
public:
    inline DataPoint() : std::vector<uint8_t>() {};
    inline DataPoint(const DataPoint& orig) : std::vector<uint8_t>(orig) {};
    inline DataPoint(const DataPoint::const_iterator start, const DataPoint::const_iterator end) : std::vector<uint8_t>(start, end) {};
    
    
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
        exitOnFail(sizeof (T) == size(), "DataPoint was unwraped as wrong type");
        return *(T*) & front();
    }

    //
};

#endif	/* DATAPOINT_H */

