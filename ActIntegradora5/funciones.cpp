#include "funciones.h"
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <list>
#include <sstream>
#include "hash_table.h"

void ordenarAdyacencias(std::list<std::pair<std::string, int>>& adyacencias) {
    adyacencias.sort([](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return a.second > b.second;
    });
}

void getIPSummary(const std::string& ip, const std::map<std::string, std::list<std::pair<std::string, int>>>& adjList, HashTable& hashTable) {
    InfoIP* info = hashTable.search(ip);
    if (info != nullptr) {
        std::cout << "Información para la IP " << ip << ":\n";
        std::cout << "Total de direcciones accesadas desde dicha IP: " << info->totalSalientes << "\n";
        std::cout << "Total de direcciones que intentaron acceder a dicha IP: " << info->totalEntrantes << "\n";

        auto it = adjList.find(ip);
        if (it != adjList.end()) {
            std::cout << "Direcciones accesadas desde dicha IP (ordenadas de forma descendente):\n";
            auto adyacencias = it->second;
            ordenarAdyacencias(adyacencias);
            for (const auto& adj : adyacencias) {
                std::cout << "- " << adj.first << " (peso: " << adj.second << ")\n";
            }
        } else {
            std::cout << "No se encontraron direcciones accesadas desde la IP " << ip << ".\n";
        }
    } else {
        std::cout << "No se encontró información para la IP " << ip << ".\n";
    }
}

void leerArchivo(std::ifstream& inFile, std::map<std::string, std::list<std::pair<std::string, int>>>& adjList, HashTable& hashTable) {
    int numIps, numIncidencias;
    inFile >> numIps >> numIncidencias;
    
    std::string ip;
    for (int i = 0; i < numIps; i++) {
        inFile >> ip;
        adjList[ip] = std::list<std::pair<std::string, int>>();  // inicializamos la lista para cada ip
    }

    std::string line;
    std::getline(inFile, line); // Para consumir la línea restante después de leer numIps y numIncidencias

    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        Incidente inc;
        std::string ipOrigen, ipDestino;
        int puertoOrigen, puertoDestino;

        iss >> inc.mes >> inc.dia >> inc.hora >> ipOrigen >> ipDestino >> inc.peso;
        std::getline(iss, inc.razon);

        // eliminamos los puertos de las ips (opcional, según necesidad)
        inc.ipOrigen = ipOrigen.substr(0, ipOrigen.find(':'));
        inc.ipDestino = ipDestino.substr(0, ipDestino.find(':'));

        // añadimos la adyacencia al grafo
        adjList[inc.ipOrigen].push_back(std::make_pair(inc.ipDestino, inc.peso));
    }

    std::map<std::string, InfoIP> infoMap;

    // llenar el mapa con la información inicial
    for (const auto& ip : adjList) {
        infoMap[ip.first] = InfoIP{ip.first, static_cast<int>(ip.second.size()), 0};
    }

    // actualizar los totales de las direcciones entrantes
    for (const auto& ip : adjList) {
        for (const auto& adj : ip.second) {
            if (infoMap.find(adj.first) != infoMap.end()) {
                infoMap[adj.first].totalEntrantes++;
            }
        }
    }

    // llenar la tabla hash con la información del mapa
    for (const auto& ip : infoMap) {
        hashTable.insert(ip.second);
    }
  
    std::cout << "Total de colisiones: " << hashTable.getColisiones() << std::endl;
}

void buscarIP(const std::string& ipBusqueda, const std::map<std::string, std::list<std::pair<std::string, int>>>& adjList, HashTable& hashTable) {
    getIPSummary(ipBusqueda, adjList, hashTable);
}

void manejarArchivo(const std::string& nombreArchivo, std::map<std::string, std::list<std::pair<std::string, int>>>& adjList, HashTable& hashTable) {
    std::ifstream inFile(nombreArchivo);
    if (!inFile) {
        throw std::runtime_error("No se puede abrir el archivo " + nombreArchivo);
    }

    leerArchivo(inFile, adjList, hashTable);

    inFile.close();
}

void interactuarUsuario(const std::map<std::string, std::list<std::pair<std::string, int>>>& adjList, HashTable& hashTable) {
    std::string ipBusqueda;
    std::cout << "Ingrese la IP que desea buscar: ";
    std::getline(std::cin, ipBusqueda);

    buscarIP(ipBusqueda, adjList, hashTable);
}

void ejecutarAplicacion() {
    try {
        std::map<std::string, std::list<std::pair<std::string, int>>> adjList; // lista de adyacencias
        HashTable hashTable;

        manejarArchivo("bitacoraGrafos.txt", adjList, hashTable);
        interactuarUsuario(adjList, hashTable);
    }
    catch (const std::exception& e) {
        std::cerr << "Se encontró un error: " << e.what() << '\n';
    }
}
