//Victor Manuel Huerta Loretz A01365532
//Jesús Alonso Galaz Reyes A00832930

//Referencias:
//https://www.cplusplus.com/doc/tutorial/files/
//https://www.cplusplus.com/reference/vector/vector/
//https://www.cplusplus.com/reference/map/map/
//https://www.geeksforgeeks.org/heap-sort/
//https://www.cplusplus.com/reference/string/string/substr/
//https://www.cplusplus.com/reference/queue/priority_queue/
//https://www.cplusplus.com/reference/string/string/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "Registros.h"
#include "MaxHeap.h"

std::vector<std::string> readLogFile(const std::string& filename);
std::vector<std::string> extractIPs(const std::vector<std::string>& logLines);
void heapSortIPs(std::vector<std::string>& ips);
std::vector<Registros> countAccessesByIP(const std::vector<std::string>& sortedIPs);

int main() {
    // Leer el archivo y extraer las IPs
    std::vector<std::string> logLines = readLogFile("bitacoraHeap.txt");
    std::vector<std::string> ips = extractIPs(logLines);

    // Ordenar las IPs utilizando Heap Sort
    heapSortIPs(ips);

    // Contar los accesos por IP y almacenar en un vector de objetos Registros
    std::vector<Registros> registros = countAccessesByIP(ips);

    // Insertar los registros en un MaxHeap
    MaxHeap maxHeap;
    for (const Registros& registro : registros) {
        maxHeap.insert(registro);
    }

    // Extraer las cinco IPs con más accesos
    std::cout << "Las cinco IPs con más accesos son:" << std::endl;
    for (int i = 0; i < 5 && maxHeap.size() > 0; i++) {
        Registros max = maxHeap.extractMax();
        std::cout << i + 1 << ". " << max.getIp() << " - Accesos: " << max.getAccesos() << std::endl;
    }

    return 0;
}

std::vector<std::string> readLogFile(const std::string& filename) {
    std::vector<std::string> logLines;
    std::ifstream file(filename);
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            logLines.push_back(line);
        }
        file.close();
    } else {
        std::cerr << "No se pudo abrir el archivo: " << filename << std::endl;
    }

    return logLines;
}

std::vector<std::string> extractIPs(const std::vector<std::string>& logLines) {
    std::vector<std::string> ips;
    for (const std::string& line : logLines) {
        size_t startPos = line.find(' ', line.find(' ', line.find(' ') + 1) + 1) + 1;
        size_t endPos = line.find(':', startPos);
        std::string ip = line.substr(startPos, endPos - startPos);
        ips.push_back(ip);
    }
    return ips;
}


void buildMaxHeap(std::vector<std::string>& ips, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && ips[left] > ips[largest]) {
        largest = left;
    }

    if (right < n && ips[right] > ips[largest]) {
        largest = right;
    }

    if (largest != i) {
        std::swap(ips[i], ips[largest]);
        buildMaxHeap(ips, n, largest);
    }
}

void heapSortIPs(std::vector<std::string>& ips) {
    int n = ips.size();

    // Construir el Max Heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        buildMaxHeap(ips, n, i);
    }

    // Extraer el máximo y reconstruir el Max Heap
    for (int i = n - 1; i > 0; i--) {
        std::swap(ips[0], ips[i]);
        buildMaxHeap(ips, i, 0);
    }
}

std::vector<Registros> countAccessesByIP(const std::vector<std::string>& sortedIPs) {
    std::vector<Registros> registros;
    for (const std::string& ip : sortedIPs) {
        if (registros.empty() || registros.back().getIp() != ip) {
            registros.push_back(Registros(ip, 1));
        } else {
            registros.back().incrementarAccesos();
        }
    }
    return registros;
}
