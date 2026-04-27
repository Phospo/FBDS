#include "cfbdbuilder.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "cfunctionblock.h"
#include "cconnection.h"
#include "csingen.h"
#include "cconstval.h"

CFBDBuilder::CFBDBuilder(CContainerFBD* _cont) : FScheme(_cont) {}

namespace {

bool resolveOutputEndpoint(const CContainerFBD* _scheme,
                          COutput* _output,
                          std::string& _blockName,
                          unsigned& _outputNumber) {
    if (_scheme == nullptr || _output == nullptr) {
        return false;
    }

    for (std::size_t blockIndex = 0; blockIndex < _scheme->getFunctionBlockCount(); ++blockIndex) {
        CFunctionBlock* block = _scheme->getFunctionBlock(blockIndex);
        if (block == nullptr) {
            continue;
        }

        for (unsigned outputIndex = 1; outputIndex <= block->getOutputCount(); ++outputIndex) {
            COutput* output = block->getOutput(outputIndex);
            if (output != _output) {
                continue;
            }

            _blockName = block->getName();
            _outputNumber = output->getNumber();
            return true;
        }
    }

    return false;
}

bool resolveInputEndpoint(const CContainerFBD* _scheme,
                         CInput* _input,
                         std::string& _blockName,
                         unsigned& _inputNumber) {
    if (_scheme == nullptr || _input == nullptr) {
        return false;
    }

    for (std::size_t blockIndex = 0; blockIndex < _scheme->getFunctionBlockCount(); ++blockIndex) {
        CFunctionBlock* block = _scheme->getFunctionBlock(blockIndex);
        if (block == nullptr) {
            continue;
        }

        for (unsigned inputIndex = 1; inputIndex <= block->getInputCount(); ++inputIndex) {
            CInput* input = block->getInput(inputIndex);
            if (input != _input) {
                continue;
            }

            _blockName = block->getName();
            _inputNumber = input->getNumber();
            return true;
        }
    }

    return false;
}

}

void CFBDBuilder::configureFBD() {
    // Ustawienie czasu próbkowania w ms
    FScheme->setSamplingTime(10);

    CSinGen* sinGen = new CSinGen("SinGen1", 1, 1.0, 0.0, 0.0);
    sinGen->setRoundingPrecision(6); //
    FScheme->addFunctionBlock(sinGen);

    CConstVal* constGen = new CConstVal("ConstGen1", 1.0);
    FScheme->addFunctionBlock(constGen);

    CFunctionBlock* sumBlock = new CFunctionBlock("Sum1", 2, 0.0, 0.0);
    FScheme->addFunctionBlock(sumBlock);

    // SinGen -> 1-Sum
    CConnection* con1 = new CConnection();
    con1->connectBegin(sinGen->getOutput(1));
    con1->connectEnd(sumBlock->getInput(1));
    FScheme->addConnection(con1);

    // ConstGen -> 2-Sum
    CConnection* con2 = new CConnection();
    con2->connectBegin(constGen->getOutput(1));
    con2->connectEnd(sumBlock->getInput(2));
    FScheme->addConnection(con2);
}

bool CFBDBuilder::loadFromJSON(const std::string& _path, unsigned* _simulationSteps) {
    if (FScheme == nullptr) {
        return false;
    }

    QFile inputFile(QString::fromStdString(_path));
    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    const QByteArray jsonBytes = inputFile.readAll();
    inputFile.close();

    QJsonParseError parseError;
    const QJsonDocument document = QJsonDocument::fromJson(jsonBytes, &parseError);
    if (parseError.error != QJsonParseError::NoError || !document.isObject()) {
        return false;
    }

    const QJsonObject root = document.object();
    if (!root.value("blocks").isArray()) {
        return false;
    }

    FScheme->clear();

    const unsigned samplingTime = static_cast<unsigned>(root.value("samplingTime").toInt(10));
    FScheme->setSamplingTime(samplingTime == 0 ? 10U : samplingTime);

    if (_simulationSteps != nullptr) {
        unsigned steps = static_cast<unsigned>(root.value("simulationSteps").toInt(100));
        if (steps == 0) {
            steps = 100;
        }
        *_simulationSteps = steps;
    }

    const QJsonArray blocks = root.value("blocks").toArray();
    for (const QJsonValue& blockValue : blocks) {
        if (!blockValue.isObject()) {
            FScheme->clear();
            return false;
        }

        const QJsonObject blockObject = blockValue.toObject();
        const std::string name = blockObject.value("name").toString().toStdString();
        const std::string type = blockObject.value("type").toString().toStdString();
        const QJsonObject params = blockObject.value("params").toObject();

        if (name.empty() || type.empty()) {
            FScheme->clear();
            return false;
        }

        CFunctionBlock* block = nullptr;
        if (type == "SinGen") {
            const double frequency = params.value("frequency").toDouble(1.0);
            const double amplitude = params.value("amplitude").toDouble(1.0);
            const double phase = params.value("phase").toDouble(0.0);
            const double offset = params.value("offset").toDouble(0.0);

            CSinGen* sinGen = new CSinGen(name, frequency, amplitude, phase, offset);
            sinGen->setRoundingPrecision(params.value("roundingPrecision").toInt(-1));
            block = sinGen;
        } else if (type == "ConstVal") {
            block = new CConstVal(name, params.value("value").toDouble(0.0));
        } else if (type == "FunctionBlock") {
            const unsigned inputCount = static_cast<unsigned>(params.value("inputCount").toInt(0));
            const double constValue = params.value("constValue").toDouble(0.0);
            const double initialOutput = params.value("initialOutput").toDouble(0.0);
            block = new CFunctionBlock(name, inputCount, constValue, initialOutput);
        } else {
            FScheme->clear();
            return false;
        }

        if (!FScheme->addFunctionBlock(block)) {
            delete block;
            FScheme->clear();
            return false;
        }
    }

    if (root.value("connections").isArray()) {
        const QJsonArray connections = root.value("connections").toArray();
        for (const QJsonValue& connectionValue : connections) {
            if (!connectionValue.isObject()) {
                FScheme->clear();
                return false;
            }

            const QJsonObject connectionObject = connectionValue.toObject();

            std::string fromBlockName = connectionObject.value("fromBlock").toString().toStdString();
            unsigned fromOutput = static_cast<unsigned>(connectionObject.value("fromOutput").toInt(1));
            std::string toBlockName = connectionObject.value("toBlock").toString().toStdString();
            unsigned toInput = static_cast<unsigned>(connectionObject.value("toInput").toInt(1));

            if (connectionObject.value("from").isObject()) {
                const QJsonObject fromObject = connectionObject.value("from").toObject();
                fromBlockName = fromObject.value("block").toString().toStdString();
                fromOutput = static_cast<unsigned>(fromObject.value("output").toInt(1));
            }

            if (connectionObject.value("to").isObject()) {
                const QJsonObject toObject = connectionObject.value("to").toObject();
                toBlockName = toObject.value("block").toString().toStdString();
                toInput = static_cast<unsigned>(toObject.value("input").toInt(1));
            }

            CFunctionBlock* fromBlock = FScheme->getFunctionBlock(fromBlockName);
            CFunctionBlock* toBlock = FScheme->getFunctionBlock(toBlockName);
            if (fromBlock == nullptr || toBlock == nullptr) {
                FScheme->clear();
                return false;
            }

            COutput* output = fromBlock->getOutput(fromOutput);
            CInput* input = toBlock->getInput(toInput);
            if (output == nullptr || input == nullptr) {
                FScheme->clear();
                return false;
            }

            CConnection* connection = new CConnection();
            connection->connectBegin(output);
            connection->connectEnd(input);
            if (!FScheme->addConnection(connection)) {
                delete connection;
                FScheme->clear();
                return false;
            }
        }
    }

    return true;
}

bool CFBDBuilder::saveToJSON(const std::string& _path, unsigned _simulationSteps) const {
    if (FScheme == nullptr) {
        return false;
    }

    QJsonObject root;
    root.insert("samplingTime", static_cast<int>(FScheme->getSamplingTime()));
    root.insert("simulationSteps", static_cast<int>(_simulationSteps));

    QJsonArray blocks;
    for (std::size_t blockIndex = 0; blockIndex < FScheme->getFunctionBlockCount(); ++blockIndex) {
        CFunctionBlock* block = FScheme->getFunctionBlock(blockIndex);
        if (block == nullptr) {
            continue;
        }

        QJsonObject blockObject;
        blockObject.insert("name", QString::fromStdString(block->getName()));

        QJsonObject params;
        if (const auto* sinGen = dynamic_cast<const CSinGen*>(block)) {
            blockObject.insert("type", "SinGen");
            params.insert("frequency", sinGen->getFrequency());
            params.insert("amplitude", sinGen->getAmplitude());
            params.insert("phase", sinGen->getPhase());
            params.insert("offset", sinGen->getOffset());
            params.insert("roundingPrecision", sinGen->getRoundingPrecision());
        } else if (const auto* constVal = dynamic_cast<const CConstVal*>(block)) {
            blockObject.insert("type", "ConstVal");
            params.insert("value", constVal->getValue());
        } else {
            blockObject.insert("type", "FunctionBlock");
            params.insert("inputCount", static_cast<int>(block->getInputCount()));
            params.insert("constValue", block->getConstValue());
            params.insert("initialOutput", block->getInitialOutputValue());
        }

        blockObject.insert("params", params);
        blocks.push_back(blockObject);
    }
    root.insert("blocks", blocks);

    QJsonArray connections;
    for (std::size_t connectionIndex = 0; connectionIndex < FScheme->getConnectionCount(); ++connectionIndex) {
        CConnection* connection = FScheme->getConnection(connectionIndex);
        if (connection == nullptr) {
            continue;
        }

        std::string fromBlockName;
        unsigned fromOutput = 0;
        std::string toBlockName;
        unsigned toInput = 0;

        if (!resolveOutputEndpoint(FScheme, connection->getBegin(), fromBlockName, fromOutput) ||
            !resolveInputEndpoint(FScheme, connection->getEnd(), toBlockName, toInput)) {
            continue;
        }

        QJsonObject connectionObject;
        QJsonObject fromObject;
        fromObject.insert("block", QString::fromStdString(fromBlockName));
        fromObject.insert("output", static_cast<int>(fromOutput));
        connectionObject.insert("from", fromObject);

        QJsonObject toObject;
        toObject.insert("block", QString::fromStdString(toBlockName));
        toObject.insert("input", static_cast<int>(toInput));
        connectionObject.insert("to", toObject);

        connections.push_back(connectionObject);
    }
    root.insert("connections", connections);

    QFile outputFile(QString::fromStdString(_path));
    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        return false;
    }

    const QJsonDocument document(root);
    const qint64 written = outputFile.write(document.toJson(QJsonDocument::Indented));
    outputFile.close();

    return written >= 0;
}
