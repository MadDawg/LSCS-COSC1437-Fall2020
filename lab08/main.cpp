#include <iostream>

using namespace std;

// https://en.wikipedia.org/wiki/Insertion_sort
void insertion_sort(int* array, unsigned size){
    for (unsigned i = 1; i < size; ++i){
        for (unsigned j = i; j > 0 && array[j-1] > array[j]; --j){
            int temp = array[j];
            array[j] = array[j-1];
            array[j-1] = temp;
        }
    }
}

void print_array(int* array, unsigned size){
    if (array == nullptr){
        cout << "[]\n";
        return;
    }
    
    cout << '[';
    // print every element except last element
    for (unsigned i = 0; i < size-1; ++i){
        cout << array[i] << ", ";
    }
    cout << array[size-1] << "]\n"; // print last element
}

int main(){
    int array[10] = {-5,3,4,0,2,-2,1,-4,-1,-3};
    
    cout << "Input array: ";
    print_array(array, 10);
    insertion_sort(array, 10);

    cout << "Sorted array: ";
    print_array(array, 10);
    
    return 0;
}
