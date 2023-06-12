//Victor Manuel Huerta Loretz A01365532
// Jesús Alonso Galaz Reyes 

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <list>
#include <sstream>
#include <string>
#include <chrono>

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

template <typename T>
class DoublyLinkedList {
public:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& data) : data(data), prev(nullptr), next(nullptr) {}
    };
    
    class iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        
        iterator(Node* node) : node_(node) {}
        
        iterator& operator++() {
            node_ = node_->next;
            return *this;
        }
        
        iterator operator++(int) {
            auto temp = *this;
            node_ = node_->next;
            return temp;
        }
        
        iterator& operator--() {
            node_ = node_->prev;
            return *this;
        }
        
        iterator operator--(int) {
            auto temp = *this;
            node_ = node_->prev;
            return temp;
        }
        
        bool operator==(const iterator& other) const {
            return node_ == other.node_;
        }
        
        bool operator!=(const iterator& other) const {
            return node_ != other.node_;
        }
        
        reference operator*() { return node_->data; }
        
        const reference operator*() const { return node_->data; }
        
    private:
        Node* node_;
    };
    
    DoublyLinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}
    
    ~DoublyLinkedList() {
        while (head_) {
            auto temp = head_;
            head_ = head_->next;
            delete temp;
        }
    }
    
    void push_back(const T& data) {
        auto node = new Node(data);
        if (!tail_) {
            head_ = tail_ = node;
        } else {
            tail_->next = node;
            node->prev = tail_;
            tail_ = node;
        }
        ++size_;
    }
    
    void push_front(const T& data) {
        auto node = new Node(data);
        if (!head_) {
            head_ = tail_ = node;
        } else {
            head_->prev = node;
            node->next = head_;
            head_ = node;
        }
        ++size_;
    }
    
    void pop_back() {
        if (!tail_) return;
        auto temp = tail_;
        if (head_ == tail_) {
            head_ = tail_ = nullptr;
        } else {
            tail_ = tail_->prev;
            tail_->next = nullptr;
        }
        delete temp;
        --size_;
    }
    
    void pop_front() {
        if (!head_) return;
        auto temp = head_;
        if (head_ == tail_) {
            head_ = tail_ = nullptr;
        } else {
            head_ = head_->next;
            head_->prev = nullptr;
        }
        delete temp;
        --size_;
    }
    
    std::size_t size() const { return size_; }
    
    bool empty() const { return size_ == 0; }
    
    T& front() { return head_->data; }
    
    const T& front() const { return head_->data; }
    
    T& back() { return tail_->data; }
    
    const T& back() const { return tail_->data; }

    iterator begin() { return iterator(head_); }

    iterator end() { return iterator(nullptr); }

private:
    Node* head_;
    Node* tail_;
    std::size_t size_;
};

//quick sort
template <typename T>
void quickSort(DoublyLinkedList<T>& entries, typename DoublyLinkedList<T>::iterator first, typename DoublyLinkedList<T>::iterator last) {
    if (first == last) return;
    auto pivot = *first;
    auto i = first;
    auto j = std::next(first);
    while (j != last) {
        if (*j < pivot) {
            i = std::next(i);
            std::swap(*i, *j);
        }
        j = std::next(j);
    }
    std::swap(*first, *i);
    quickSort(entries, first, i);
    quickSort(entries, std::next(i), last);
}

template <typename T>
void mergeSort(DoublyLinkedList<T>& entries, typename DoublyLinkedList<T>::iterator first, typename DoublyLinkedList<T>::iterator last) {
    if (std::distance(first, last) <= 1) return;
    auto middle = std::next(first, std::distance(first, last) / 2);
    mergeSort(entries, first, middle);
    mergeSort(entries, middle, last);
    DoublyLinkedList<T> temp;
    auto i = first;
    auto j = middle;
    while (i != middle && j != last) {
        if (*i < *j) {
            temp.push_back(*i);
            i = std::next(i);
        } else {
            temp.push_back(*j);
            j = std::next(j);
        }
    }
    while (i != middle) {
        temp.push_back(*i);
        i = std::next(i);
    }
    while (j != last) {
        temp.push_back(*j);
        j = std::next(j);
    }
    std::move(temp.begin(), temp.end(), first);
}

template <typename T>
std::pair<typename DoublyLinkedList<T>::iterator, typename DoublyLinkedList<T>::iterator> binarySearch(DoublyLinkedList<T>& entries, const T& start, const T& end) {
    auto lower = std::lower_bound(entries.begin(), entries.end(), start);
    auto upper = std::upper_bound(entries.begin(), entries.end(), end);
    return {lower, upper};
}
int main() {
   std::ifstream infile("bitacora-1.txt");
   if (!infile.is_open()) {
       std::cerr << "Error: No se puede abrir el archivo.\n";
       return 1;
   }
   DoublyLinkedList<LogEntry> entries;
   std::string line;
   while (getline(infile, line)) {
       LogEntry entry;
       parseLine(line, entry);
       entries.push_back(entry);
   }
   infile.close();
    
    // Quick sort O(n log n)
    auto startTime = std::chrono::high_resolution_clock::now();
    quickSort(entries, entries.begin(), entries.end());
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
    std::cout << "Quick sort took " << duration << " microseconds.\n";
    
    // Merge sort O(n log n)
    startTime = std::chrono::high_resolution_clock::now();
    mergeSort(entries, entries.begin(), entries.end());
    endTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
    std::cout << "Merge sort took " << duration << " microseconds.\n";
    
   std::ofstream outfile("bitacora_ordenada.txt");
   if (!outfile.is_open()) {
       std::cerr << "Error: No se puede crear el archivo.\n";
       return 1;
   }

   const std::vector<std::string> months = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    
   for (const LogEntry& entry : entries) {
       outfile << months[entry.month] << ' ' << entry.day << ' ' << entry.hour << ':' << entry.minute << ':' << entry.second << ' '
               << entry.ip << ' ' << entry.user << ' ' << entry.message << '\n';
   }
    
   outfile.close();
    
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
  
    // Binary searchO(log n)
    auto range = binarySearch(entries, start, end);

    std::ofstream search_outfile("resultado_busqueda.txt");
    if (!search_outfile.is_open()) {
        std::cerr << "Error: No se puede crear el archivo.\n";
        return 1;
    }

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
  
    for (auto it = range.first; it != range.second; ++it) {
        const LogEntry& entry = *it;
        search_outfile << months[entry.month] << ' ' << entry.day << ' ' << entry.hour << ':' << entry.minute << ':' << entry.second << ' '
            << entry.ip << ' ' << entry.user << ' ' << entry.message << '\n';
    }
    
    search_outfile.close();
}