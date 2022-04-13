#include "MyVector.h"
#include <iostream>

void printV(Vector& Vector){
    std::cout << "LoadFactor: " << Vector.loadFactor() << "," << std::endl;
    std::cout << "Capacity: " << Vector.capacity() << "," << std::endl;
    std::cout << "Size: " << Vector.size() << "." << std::endl;
    for (size_t i = 0; i < Vector.size(); i++){
        std::cout << Vector[i] << " ";
    }
    std::cout << '\n' << '\n';
}
    
int main(){
    Vector v;
    std::cout << "reserve memory for 100 values, add only 5" << std::endl;
    v.reserve(100);
    v.pushBack(10);
    v.pushFront(8);
    v.pushFront(5);
    v.pushBack(20);
    v.pushFront(9);
    printV(v);
    
    std::cout << "add 3 more values, shrink allocation to size" << std::endl;
    v.pushBack(30);
    v.pushFront(3);
    v.pushFront(7);
    v.shrinkToFit();
    printV(v);
    
    std::cout << "test insert methods" << std::endl;
    v.insert(15, 4);
    Value array[] = {22, 24, 26, 28, 45};
    v.insert(array, 5, 6);
    Vector additional;
    additional.pushBack(-8);
    additional.pushBack(-5);
    additional.pushBack(-2);
    additional.pushBack(-3);
    v.insert(additional, 0);
    printV(v);

    std::cout << "test find method" << std::endl;
    std::cout << "Index of 10 (exists): " << v.find(7) << std::endl;
    std::cout << "Index of 888 (not exists): " << v.find(88) << std::endl;
    std::cout << "test pop methods" << std::endl;
    v.popBack();
    v.popFront();
    printV(v);
    
    std::cout << "test erase methods" << std::endl;
    v.erase(1, 2);
    v.eraseBetween(3, 8);
    printV(v);
    return 0;
}
