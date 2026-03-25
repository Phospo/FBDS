#include "stimestamp.h"

STimeStamp::STimeStamp() {}

void STimeStamp::addSampling(unsigned _msec) {
    Milliseconds += _msec;
    Seconds += Milliseconds / 1000;
    Milliseconds %= 1000;
}
