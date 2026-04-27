#include "cfunctionblock.h"

CFunctionBlock::CFunctionBlock(std::string _name, unsigned _in_count, double _const, double _init_out) : FName(_name), FConst(_const), FInitialOutput(_init_out) {
    if (_in_count > 0) {
        for (unsigned i = 1; i <= _in_count; i++) {
            FInputs.push_back({i});
        }
    }
    FOutputs.push_back({1});
}

CFunctionBlock::~CFunctionBlock() {
}

std::string CFunctionBlock::getName() const {
    return FName;
}

unsigned CFunctionBlock::getInputCount() const {
    return static_cast<unsigned>(FInputs.size());
}

unsigned CFunctionBlock::getOutputCount() const {
    return static_cast<unsigned>(FOutputs.size());
}

double CFunctionBlock::getConstValue() const {
    return FConst;
}

double CFunctionBlock::getInitialOutputValue() const {
    return FInitialOutput;
}

CInput* CFunctionBlock::getInput(unsigned _num) {
    if (_num == 0 || _num > FInputs.size())
        return nullptr;

    return &FInputs[_num - 1];
}

COutput* CFunctionBlock::getOutput(unsigned _num) {
    if (_num == 0 || _num > FOutputs.size())
        return nullptr;

    return &FOutputs[_num - 1];
}

void CFunctionBlock::initialize() {
    FOutputs[0].setData(SDataSample(FInitialOutput));
}

void CFunctionBlock::calculate(STimeStamp _ts) {
    SDataSample data(_ts);

    data.Value += FConst;
    data.TimeStamp = _ts;

    SDataSample ds;
    for (auto& in : FInputs) {
        ds = in.getData();
        if (ds.isOK()) {
            data.Value += ds.Value;
        } else {
            data.Status = DataSampleStatus::bad;
        }
    }
    FOutputs[0].setData(data);
}
