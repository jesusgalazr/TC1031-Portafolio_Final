#include "hash_table.h"
#include <iostream>

int HashTable::hashCode(const std::string& ip) {
    unsigned long hash = 5381;
    for (char c : ip) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % TABLE_SIZE;
}

HashTable::HashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = nullptr;
    }
    colisiones = 0;
}

HashTable::~HashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        delete hashTable[i];
    }
}

void HashTable::insert(const InfoIP& info) {
    int index = hashCode(info.ip);
    int i = 0;
    while (hashTable[(index + i*i) % TABLE_SIZE] != nullptr) {
        i++;
        colisiones++;
    }
    hashTable[(index + i*i) % TABLE_SIZE] = new InfoIP(info);
}

InfoIP* HashTable::search(const std::string& ip) {
    int index = hashCode(ip);
    int i = 0;
    while (hashTable[(index + i*i) % TABLE_SIZE] != nullptr && hashTable[(index + i*i) % TABLE_SIZE]->ip != ip) {
        i++;
    }
    return hashTable[(index + i*i) % TABLE_SIZE];
}

int HashTable::getColisiones() const {
    return colisiones;
}
