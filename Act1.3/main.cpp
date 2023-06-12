#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

struct LogEntry {
    int month;
    int day;
    int hour;
    int minute;
    int second;
    std::string ip;
    std::string user;
    std::string message;
};

bool operator<(const LogEntry& lhs, const LogEntry& rhs) {
    if (lhs.month != rhs.month) {
        return lhs.month < rhs.month;
    }
    if (lhs.day != rhs.day) {
        return lhs.day < rhs.day;
    }
    if (lhs.hour != rhs.hour) {
        return lhs.hour < rhs.hour;
    }
    if (lhs.minute != rhs.minute) {
        return lhs.minute < rhs.minute;
    }
    return lhs.second < rhs.second;
}

int getMonthIndex(std::string month) {
    const std::vector<std::string> months = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    auto it = find(months.begin(), months.end(), month);
    return distance(months.begin(), it);
}

void parseLine(std::string line, LogEntry& entry) {
    entry.month = getMonthIndex(line.substr(0, 3));
    line.erase(0, 4);
    entry.day = stoi(line.substr(0, 2));
    line.erase(0, 3);
    entry.hour = stoi(line.substr(0, 2));
    entry.minute = stoi(line.substr(3, 2));
    entry.second = stoi(line.substr(6, 2));
    line.erase(0, 9);
    entry.ip = line.substr(0, line.find(':'));
    line.erase(0, line.find(':') + 1);
    entry.message = line;
    size_t found = entry.message.find("for ");
    if (found != std::string::npos) {
        entry.user = entry.message.substr(found + 4);
        entry.user = entry.user.substr(0, entry.user.find(' '));
    } else {
        entry.user = "";
    }
}

int main() {
    std::ifstream infile("bitacora-1.txt");
    if (!infile.is_open()) {
        std::cerr << "Error: No se puede abrir el archivo.\n";
        return 1;
    }
    std::vector<LogEntry> entries;
    std::string line;
    while (getline(infile, line)) {
        LogEntry entry;
        parseLine(line, entry);
        entries.push_back(entry);
    }
    infile.close();
    sort(entries.begin(), entries.end());
    std::ofstream outfile("bitacora_ordenada.txt");
    if (!outfile.is_open()) {
        std::cerr << "Error: No se puede crear el archivo.\n";
        return 1;
    }

    std::cout << "Fecha Inicio (MMM DD hh:mm:ss): ";
    std::string start_str;
    getline(std::cin, start_str);
    LogEntry start;
    parseLine(start_str, start);

    std::cout << "Fecha Final (MMM DD hh:mm:ss): ";
    std::string end_str;
    getline(std::cin, end_str);
    LogEntry end;
    parseLine(end_str, end);

    const std::vector<std::string> months = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    for (const LogEntry& entry : entries) {
        outfile << months[entry.month] << ' ' << entry.day << ' ' << entry.hour << ':' << entry.minute << ':' << entry.second << ' '
                << entry.ip << ' ' << entry.user << ' ' << entry.message << '\n';
    }
    outfile.close();
    std::cout << "ordenado y salvado en  bitacora_ordenada.txt\n";

    int count = 0;
    for (const LogEntry& entry : entries) {
    if (entry < start) {
        continue;
    }
    if (entry.month > end.month ||
        (entry.month == end.month && entry.day > end.day) ||
        (entry.month == end.month && entry.day == end.day && entry.hour > end.hour) ||
        (entry.month == end.month && entry.day == end.day && entry.hour == end.hour && entry.minute > end.minute) ||
        (entry.month == end.month && entry.day == end.day && entry.hour == end.hour && entry.minute == end.minute && entry.second > end.second)) {
        break; 
    }
    count++;
    std::cout << months[entry.month] << ' ' << entry.day << ' ' << entry.hour << ':' << entry.minute << ':' << entry.second << ' '
            << entry.ip << ' ' << entry.user << ' ' << entry.message << '\n';
    }
    std::cout << " Resultado: " << count<< " Registros";
    return 0;
}