#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <string>
#include <map>
#include <list>
#include "hash_table.h"

struct Incidente {
    std::string mes;
    int dia;
    std::string hora;
    std::string ipOrigen;
    std::string ipDestino;
    int peso;
    std::string razon;
};

void ordenarAdyacencias(std::list<std::pair<std::string, int>>& adyacencias);
void getIPSummary(const std::string& ip, const std::map<std::string, std::list<std::pair<std::string, int>>>& adjList, HashTable& hashTable);
void leerArchivo(std::ifstream& inFile, std::map<std::string, std::list<std::pair<std::string, int>>>& adjList, HashTable& hashTable);
void buscarIP(const std::string& ipBusqueda, const std::map<std::string, std::list<std::pair<std::string, int>>>& adjList, HashTable& hashTable);
void manejarArchivo(const std::string& nombreArchivo, std::map<std::string, std::list<std::pair<std::string, int>>>& adjList, HashTable& hashTable);
void interactuarUsuario(const std::map<std::string, std::list<std::pair<std::string, int>>>& adjList, HashTable& hashTable);
void ejecutarAplicacion();

#endif  // FUNCIONES_H
