#include "sdatasample.h"

SDataSample::SDataSample() {}

SDataSample::SDataSample(STimeStamp _ts) : Status(DataSampleStatus::ok), TimeStamp(_ts) {}

SDataSample::SDataSample(double _val) : Value(_val), Status(DataSampleStatus::ok) {}

bool SDataSample::isOK() const {
    return Status == DataSampleStatus::ok;
}
