#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;

// Funcion para medir el tiempo  de ejeecucion
template<typename Func>
long long medirTiempo(Func funcion) {
    auto inicio = chrono::high_resolution_clock::now();
    funcion();
    auto fin = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::nanoseconds>(fin - inicio).count();
}

// Funcion para generear arrays
int* generarArray(int n) {
    // Inicializar la semilla de números aleatorios
    srand(time(0));

    // Crear el array dinámico
    int* array = new int[n];

    // Llenar el array con valores aleatorios
    for (int i = 0; i < n; ++i) {
        array[i] = rand() % 100; // Se generan números aleatorios entre 0 y 99
    }

    return array;
}


// Complejidad Lineal RadixSort
int getMax(int arr[], int n)
{
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}


void countSort(int arr[], int n, int exp)
{

    int output[n];
    int i, count[10] = { 0 };
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (i = 0; i < n; i++)
        arr[i] = output[i];
}


void radixsort(int arr[], int n)
{

    int m = getMax(arr, n);
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}



//Complejidad Cuadratica BubbleSort
void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)

        // Last i elements are already
        // in place
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}


// Complejidad  lineal logaritmica MergeSort
void merge(int array[], int const left, int const mid,
           int const right)
{
    int const subArrayOne = mid - left + 1;
    int const subArrayTwo = right - mid;
    auto *leftArray = new int[subArrayOne],
            *rightArray = new int[subArrayTwo];

    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];

    auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;

    while (indexOfSubArrayOne < subArrayOne
           && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne]
            <= rightArray[indexOfSubArrayTwo]) {
            array[indexOfMergedArray]
                    = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray]
                    = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }

    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray]
                = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }

    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray]
                = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
    delete[] leftArray;
    delete[] rightArray;
}

void mergeSort(int array[], int const begin, int const end)
{
    if (begin >= end)
        return;

    int mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}

// Complejidad logaritmica Binary Search

int binarySearch(int arr[], int l, int r, int x)
{
    while (l <= r) {
        int m = l + (r - l) / 2;


        if (arr[m] == x)
            return m;


        if (arr[m] < x)
            l = m + 1;


        else
            r = m - 1;
    }

    return -1;
}

// Complejidad exponencial secuencia de fibonacci
long long fibonacci(int n) {
    if (n <= 1)
        return n;
    else
        return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    int n = 30;
    int* array = generarArray(n);
    int x=10;
    radixsort(array, n);


    long long tiempoEjecucion = medirTiempo([n]() {
        fibonacci(n);
    });

    cout << "Tiempo de ejecución en nanosegundos: " << tiempoEjecucion << endl;

    delete[] array;

    return 0;
}