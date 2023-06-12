
/*
Integrantes del equipo:

Victor Manuel Huerta Loretz A01365532
Jesús Alonso Galaz Reyes A00832930
*/

/*
Referencias:

Cplusplus.com. (2020). List (STL C++ Library). Recuperado de: http://www.cplusplus.com/reference/list/list/

Cplusplus.com. (2020). Map (STL C++ Library). Recuperado de: http://www.cplusplus.com/reference/map/map/

cppreference.com. (s.f.). std::map - cppreference.com. Recuperado de https://en.cppreference.com/w/cpp/container/map

GeeksforGeeks. (s.f.). File Handling through C++ Classes - GeeksforGeeks. Recuperado de https://www.geeksforgeeks.org/file-handling-c-classes/

Stack Overflow. (2018). How does a hash table work? Recuperado de: https://stackoverflow.com/questions/730620/how-does-a-hash-table-work

TutorialsPoint. (2020). C++ File Handling. Recuperado de: https://www.tutorialspoint.com/cplusplus/cpp_files_streams.htm

User1. (2009, julio 13). How can I read and parse CSV files in C++? - Stack Overflow. Recuperado de https://stackoverflow.com/questions/1120140/how-can-i-read-and-parse-csv-files-in-c

Microsoft. (s.f.). Procedimientos recomendados de C++ moderno para el control de errores y excepciones. https://learn.microsoft.com/es-es/cpp/cpp/errors-and-exception-handling-modern-cpp?view=msvc-170

GeeksforGeeks. (n.d.). Data Structures - GeeksforGeeks. Recuperado de: https://www.geeksforgeeks.org/data-structures/

Hashing | Set 3 (Open Addressing) - GeeksforGeeks. (n.d.). Recuperado de: https://www.geeksforgeeks.org/hashing-set-3-open-addressing/
*/

/*
Complejidades computacionales:

ordenarAdyacencias(): O(N log N) 
getIPSummary(): O(N log N) por llamar a ordenarAdyacencias(), pero ignorando eso, es O(1)
leerArchivo(): O(N)
buscarIP(): O(N log N)
manejarArchivo(): O(N)
interactuarUsuario(): O(N log N)
ejecutarAplicacion(): O(N log N)
HashTable::insert(): O(1) en el mejor caso, O(N) en el peor caso
HashTable::search(): O(1) en el mejor caso, O(N) en el peor caso
*/


#include <iostream>
#include "funciones.h"

int main() {
    ejecutarAplicacion();
    return 0;
}