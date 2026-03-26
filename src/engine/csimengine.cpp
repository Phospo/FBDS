#include "csimengine.h"

#include <cstddef>
#include <iostream>

CSimEngine::CSimEngine(CContainerFBD* _fbd) : FFBDScheme(_fbd) {}

void CSimEngine::setSimStop(unsigned _stop_step) {
    FSimStop = _stop_step;
}
void CSimEngine::initialize() {
    FSimStep = 0;
    FSimTS = STimeStamp();
    if (FFBDScheme == nullptr)
        return;

    for (std::size_t index = 0; index < FFBDScheme->getFunctionBlockCount(); ++index) {
        CFunctionBlock* block = FFBDScheme->getFunctionBlock(index);
        if (block == nullptr)
            continue;

        block->initialize();
    }
}
void CSimEngine::doSimStep() {
    if (FFBDScheme == nullptr)
        return;

    FSimStep++;
    FSimTS.addSampling(FFBDScheme->getSamplingTime());
    for (std::size_t index = 0; index < FFBDScheme->getFunctionBlockCount(); ++index) {
        CFunctionBlock* block = FFBDScheme->getFunctionBlock(index);
        if (block == nullptr)
            continue;

        block->calculate(FSimTS);
    }
}

void CSimEngine::simulateBatch() {
    if (FFBDScheme == nullptr) {
        std::cerr << "Simulation engine is not configured." << std::endl;
        return;
    }

    CFunctionBlock* monitoredBlock = FFBDScheme->getFunctionBlock("FB4");
    if (monitoredBlock == nullptr && FFBDScheme->getFunctionBlockCount() > 0)
        monitoredBlock = FFBDScheme->getFunctionBlock(FFBDScheme->getFunctionBlockCount() - 1);

    std::cout << "Simulation status: " << int(FSimStatus) << std::endl;
    initialize();
    FSimStatus = SimStatus::running;
    std::cout << "Simulation status: " << int(FSimStatus) << std::endl;

    // Po inicjalizacji wykonaj jednokrotne obliczenie bloków na kroku 0 (t=0), aby wartość Sum1 już wtedy była aktualna.
    if (FFBDScheme != nullptr) {
        for (std::size_t index = 0; index < FFBDScheme->getFunctionBlockCount(); ++index) {
            CFunctionBlock* block = FFBDScheme->getFunctionBlock(index);
            if (block == nullptr)
                continue;
            block->calculate(FSimTS);
        }
    }

    if (monitoredBlock != nullptr && monitoredBlock->getOutput(1) != nullptr) {
        std::cout << "Simulation step: " << FSimStep
                  << ", " << monitoredBlock->getName()
                  << " out_1: " << monitoredBlock->getOutput(1)->getData().Value
                  << std::endl;
    }

    while (FSimStep < FSimStop) {
        doSimStep();
        if (monitoredBlock != nullptr && monitoredBlock->getOutput(1) != nullptr) {
            std::cout << "Simulation step: " << FSimStep
                      << ", " << monitoredBlock->getName()
                      << " out_1: " << monitoredBlock->getOutput(1)->getData().Value
                      << std::endl;
        } else {
            std::cout << "Simulation step: " << FSimStep << std::endl;
        }
    }

    FSimStatus = SimStatus::stopped;
    std::cout << "Simulation status: " << int(FSimStatus) << std::endl;
}
