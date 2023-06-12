#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <string>
#include <list>

struct InfoIP {
    std::string ip;
    int totalSalientes;
    int totalEntrantes;
};

const int TABLE_SIZE = 100000;

class HashTable {
private:
    InfoIP* hashTable[TABLE_SIZE];
    int colisiones;

    int hashCode(const std::string& ip);

public:
    HashTable();
    ~HashTable();

    void insert(const InfoIP& info);
    InfoIP* search(const std::string& ip);
    int getColisiones() const;
};

#endif  // HASH_TABLE_H
