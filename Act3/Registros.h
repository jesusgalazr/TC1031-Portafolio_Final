#ifndef REGISTROS_H
#define REGISTROS_H

#include <string>

class Registros {
private:
    std::string ip;
    int accesos;

public:
    // Constructor
    Registros(const std::string& ip = "", int accesos = 0) : ip(ip), accesos(accesos) {}

    // Getters
    std::string getIp() const {
        return ip;
    }

    int getAccesos() const {
        return accesos;
    }

    // Setters
    void setIp(const std::string& ip) {
        this->ip = ip;
    }

    void setAccesos(int accesos) {
        this->accesos = accesos;
    }

    // Incrementar accesos
    void incrementarAccesos() {
        accesos++;
    }
};

#endif // REGISTROS_H
