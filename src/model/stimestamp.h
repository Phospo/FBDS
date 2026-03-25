#ifndef STIMESTAMP_H
#define STIMESTAMP_H

struct STimeStamp {
    unsigned Seconds{0};
    unsigned Milliseconds{0};

    STimeStamp();
    void addSampling(unsigned _msec);
};

#endif // STIMESTAMP_H
