# CP09
STL
## Anotaciones

- Para este modulo te limitan los contenedores a uno por ejercicio y el que uses ya no lo vas a poder usar

## ex00

- Para el primer ejercicio usare el contenedor mapa
	- ¿por que? tenemos la fecha como clave y el valor del bitcoin  como valor

1. Cargar el CSV con el data historico
```cpp
void BitcoinExchange::loadCSVData(const std::string& csvFilePath) {
    std::ifstream file(csvFilePath.c_str());
    if (!file.is_open()) {
        throw std::runtime_error("Error: could not open file.");
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string date, price;
        if (std::getline(ss, date, ',') && std::getline(ss, price)) {
            historicalPrices[date] = std::atof(price.c_str());
        }
    }
}
```
- En este metodo estamos separando fecha y valor y lo guardamos en el mapa.

2. Parseo de fecha
```cpp
	void BitcoinExchange::processLine(const std::string& line) 
	{
    std::stringstream ss(line);
    std::string date, value;
    if (std::getline(ss, date, '|') && std::getline(ss, value)) {
        date = date.substr(0, date.find_last_not_of(" ") + 1);
        value = value.substr(value.find_first_not_of(" "));

        if (!isValidDate(date)) {
            std::cerr << "Error: bad input date => " << date << std::endl;
            return;
        }
        if (!isValidValue(value)) {
            std::cerr << "Error: not a valid number." << std::endl;
            return;
        }

        double val = std::atof(value.c_str());
        if (val < 0) {
            std::cerr << "Error: negative value." << std::endl;
            return;
        }
        if (val > INT_MAX) {
            std::cerr << "Error: value too large." << std::endl;
            return;
        }

        double rate = getExchangeRate(date);
        std::cout << date << " => " << value << " = " << std::fixed << std::setprecision(2) << (val * rate) << std::endl;
    } else {
        std::cerr << "Error: bad input format." << std::endl;
    }
}
```
- Parseo de la fecha a traves de !isValidDate()
```cpp
	bool BitcoinExchange::isValidDate(const std::string& date) const {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
        return false;
    }
    std::string yearStr = date.substr(0, 4);
    std::string monthStr = date.substr(5, 2);
    std::string dayStr = date.substr(8, 2);
    if (!isdigit(yearStr[0]) || !isdigit(yearStr[1]) || !isdigit(yearStr[2]) || !isdigit(yearStr[3]) ||
        !isdigit(monthStr[0]) || !isdigit(monthStr[1]) ||
        !isdigit(dayStr[0]) || !isdigit(dayStr[1])) {
        return false;
    }
    int year = std::atoi(yearStr.c_str());
    int month = std::atoi(monthStr.c_str());
    int day = std::atoi(dayStr.c_str());
    
    if (month < 1 || month > 12 || day < 1 || year < 2000) {
        return false;
    }
    
    static const int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int maxDay = daysInMonth[month - 1];
    
    if (month == 2 && (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))) {
        maxDay = 29; // leap year
    }
    
    if (day > maxDay) {
        return false;
    }
    
    return true;
}
```
- Primero compruebo que esta en el formato `YYYY-MM-DD`
	- Es decir que el tamaño del string sea 10, que e la posicion del string[4] y string[7] haya un guion
- Luego utilizo substr para guardar la fecha en 3 strings y compruebo que sea numeros lo que hay dentro.
- un array con los dias de cada mes para comprobar que ese mes puede estar en ese dia 

3. Parseo de valor
	- comprobar que sea digito  y sea menor que el max int
4. Calcurar rate
```cpp
	double BitcoinExchange::getExchangeRate(const std::string& date) const {
    std::map<std::string, double>::const_iterator it = historicalPrices.lower_bound(date);
    if (it == historicalPrices.end() || it->first != date) {
        if (it == historicalPrices.begin()) {
            return 0.0;
        }
        --it;
    }
    return it->second;
}	
```
- •	getExchangeRate busca la tasa de cambio para una fecha específica.
- •	Utiliza lower_bound para encontrar la fecha igual o mayor que la buscada.
- •	Si no hay una fecha exacta, retrocede para encontrar la fecha anterior más cercana.
- •	Si no hay fechas anteriores, retorna 0.0.
- •	Finalmente, retorna la tasa de cambio encontrada.

## ex 01
### RPN

#### ¿que nos piden?

- Para este ejercicio tenemos que hacer operacion polaca "5 5 +" nos tiene que devolver 10
- Para este ejercicio he elegido el stack
- Cada numero sera un elemento del stack y a medida que vayamos leyendo se ira destruyendo el ultimo nodo
- el resultado de la operacion se guardara como ultimo nodo asi el siguiente numero entrara en el stack y asi sucesivamente.

### explicacion del code
- Pequeño Parseo 
	- Usando el metodo find_first_of(("0123456789+-/* ")) nos aseguramos que no haya nada diferente a numeros o simbolos de operacion;
- Creo un `std::stringstream` a partir de la expresión. Esto permite leer la expresión carácter por carácter.
- entramos en un bucle mientras haya caracteres en el stringstream.
- si es un operador hacemos una operacion sino pusheamos el caracter con un atoi
- en el metodo de la operacion hacemos una pequeña comprobacion con el metodo size del stack
si es menor que 2 es decir no hay numeros suficientes para la operacion retornamos una excepcion si no hacemos las operaciones
- en el caso de la division entre 0 
	retorno error;

## ex02

- el objetivo del ejercicio es implementar un programa en C++ llamado PmergeMe que:

	1.	Recibir unsa secuencia de Numeros positivos
	2.	Ordenar estos Numeros usando el algoritmo merge-insert (también conocido como el algoritmo de Ford-Johnson).
	3.	Use al menos dos contenedores diferentes de la STL de C++ (en este caso, std::vector y std::deque).
	4.	Manejo de errores
	5.	Medir y mostrar el tiempo de ejecucion en microsegundos(µs).
### Algoritmo Merge-Insert (Ford-Johnson)

El algoritmo merge-insert es una combinación de dos algoritmos:

	•	Merge Sort: Un algoritmo de ordenación basado en el paradigma divide y vencerás. Divide la secuencia en mitades, ordena cada mitad de manera recursiva y luego fusiona las mitades ordenadas.
	•	Insertion Sort: Un algoritmo simple de ordenación que construye la lista ordenada de uno en uno insertando cada nuevo elemento en su lugar adecuado.
#### Pasos del Algoritmo
Contenedores STL Usados

	•	std::vector: Un arreglo dinámico que permite acceso aleatorio rápido.
	•	std::deque: Una cola de doble extremo que permite inserciones y borrados eficientes tanto al principio como al final.
	1.	Divide: Si la secuencia tiene más de 5 elementos, se divide en dos mitades.
	2.	Orden Recursivo: Cada mitad se ordena recursivamente utilizando el mismo algoritmo merge-insert.
	3.	Fusiona: Las dos mitades ordenadas se fusionan para formar una secuencia ordenada completa.
	4.	Ordena Directamente: Si la secuencia tiene 5 o menos elementos, se usa Insertion Sort para ordenarla directamente.
#### Contenedores STL Usados

	•	std::vector: Un arreglo dinámico que permite acceso aleatorio rápido.
	•	std::deque: Una cola de doble extremo que permite inserciones y borrados eficientes tanto al principio como al final.