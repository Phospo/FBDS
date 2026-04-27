#ifndef CCONTAINERFBD_H
#define CCONTAINERFBD_H

#include <cstddef>
#include <list>
#include <map>

#include "cfunctionblock.h"
#include "cconnection.h"

/** CContainerFBD

    Kontener przechowujący bloki oraz połączenia schematu FBD
*/
class CContainerFBD {
    unsigned FSamplingTime{1000};
    std::map<std::string,CFunctionBlock*> FFunctionBlocksByName;
    std::list<CFunctionBlock*> FFunctionBlocks;
    std::list<CConnection*> FConnections;

public:
    /**
        Konstruktor podstawowy
    */
    CContainerFBD();
    /**
        Destruktor podstawowy
    */
    ~CContainerFBD();
    /**
        Dodanie bloku funkcyjnego do kontenera.

        @param	_block	Wskaźnik do dodawanego bloku
        @return	True, jeśli blok został dodany
    */
    bool addFunctionBlock(CFunctionBlock* _block);
    /**
        Dodanie połączenia do kontenera.

        @param	_con	Wskaźnik do dodawanego połączenia
        @return	True, jeśli połączenie zostało dodane
    */
    bool addConnection(CConnection* _con);
    /**
        Pobranie bloku o zadanej nazwie.

        @param	_name	Nazwa bloku
        @return	Wskaźnik do bloku lub nullptr
    */
    CFunctionBlock* getFunctionBlock(const std::string& _name) const;
    /**
        Pobranie bloku o zadanym indeksie.

        @param	_index	Indeks bloku w kolejności przechowywania
        @return	Wskaźnik do bloku lub nullptr
    */
    CFunctionBlock* getFunctionBlock(std::size_t _index) const;
    /**
        Pobranie liczby bloków w kontenerze.

        @return	Liczba bloków funkcyjnych
    */
    std::size_t getFunctionBlockCount() const;
    /**
        Pobranie połączenia o zadanym indeksie.

        @param _index Indeks połączenia w kolejności przechowywania
        @return Wskaźnik do połączenia lub nullptr
    */
    CConnection* getConnection(std::size_t _index) const;
    /**
        Pobranie liczby połączeń w kontenerze.

        @return Liczba połączeń
    */
    std::size_t getConnectionCount() const;
    /**
        Pobranie czasu próbkowania symulacji.

        @return	Czas próbkowania w milisekundach
    */
    unsigned getSamplingTime() const;

    /**
        Ustawienie czasu próbkowania symulacji.

        @param _samplingTime Czas próbkowania w milisekundach
    */
    void setSamplingTime(unsigned _samplingTime);
    /**
        Usunięcie całej konfiguracji schematu.
    */
    void clear();
};

#endif // CCONTAINERFBD_H
