#include "ccontainerfbd.h"

#include <algorithm>

CContainerFBD::CContainerFBD() {}

CContainerFBD::~CContainerFBD() {
    for (auto connection : FConnections)
        delete connection;
    for (auto functionBlock : FFunctionBlocks)
        delete functionBlock;
}

bool CContainerFBD::addFunctionBlock(CFunctionBlock* _block) {
    if (_block == nullptr)
        return false;

    std::string name = _block->getName();
    if (FFunctionBlocksByName.end() != FFunctionBlocksByName.find(name))
        return false;
    FFunctionBlocks.push_back(_block);
    FFunctionBlocksByName[_block->getName()] = _block;
    return true;
}

bool CContainerFBD::addConnection(CConnection* _con) {
    if (_con == nullptr)
        return false;

    auto it = std::find(FConnections.begin(), FConnections.end(), _con);
    if (it != FConnections.end())
        return false;
    FConnections.push_back(_con);
    return true;
}

CFunctionBlock* CContainerFBD::getFunctionBlock(const std::string& _name) const {
    auto it = FFunctionBlocksByName.find(_name);
    if (it == FFunctionBlocksByName.end())
        return nullptr;
    return it->second;
}

CFunctionBlock* CContainerFBD::getFunctionBlock(std::size_t _index) const {
    if (_index >= FFunctionBlocks.size())
        return nullptr;

    auto it = FFunctionBlocks.begin();
    std::advance(it, static_cast<long>(_index));
    return *it;
}

std::size_t CContainerFBD::getFunctionBlockCount() const {
    return FFunctionBlocks.size();
}

unsigned CContainerFBD::getSamplingTime() const {
    return FSamplingTime;
}

void CContainerFBD::setSamplingTime(unsigned _samplingTime) {
    FSamplingTime = _samplingTime;
}
