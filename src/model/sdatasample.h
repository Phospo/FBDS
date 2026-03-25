#ifndef SDATASAMPLE_H
#define SDATASAMPLE_H

#include "stimestamp.h"

enum class DataSampleStatus { ok = 0, bad = 1};

struct SDataSample {
    double Value{0};
    DataSampleStatus Status{DataSampleStatus::bad};
    STimeStamp TimeStamp;

    SDataSample();
    SDataSample(STimeStamp _ts);
    SDataSample(double _val);
    bool isOK() const;
};

#endif // SDATASAMPLE_H
