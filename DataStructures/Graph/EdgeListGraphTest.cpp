#include <iostream>
#include <time.h>
#include "EdgeListGraph.hpp"

int main(){
    clock_t start, end;

    std::cout << "EdgeListGraph Test\n";
    std::cout << "-------------------\n";

//
    std::cout << "Test of default constructor:\n\n";
    start = clock(); // Time counting begins.
    

    EdgeListGraph<int> graphDefault;
    graphDefault.print();
    

    end = clock(); // Time counting ends.
    std::cout<<"Execution time: "<<1000*(double)(end-start)/CLOCKS_PER_SEC<<" ms.\n-------------------\n";
//
    std::cout << "Test of default constructor of manually inserted vertex:\n\n";
    start = clock(); // Time counting begins.
    

    EdgeListGraph<int> graphManual;
    EdgeListVertex<int> vertex1, vertex2, vertex3;
    vertex1.setVertex(1); vertex2.setVertex(2); vertex3.setVertex(3);
    vertex1.setNextVertex(&vertex2); vertex2.setNextVertex(&vertex3);
    graphManual.setVertex(&vertex1);
    graphManual.print();
    

    end = clock(); // Time counting ends.
    std::cout<<"Execution time: "<<1000*(double)(end-start)/CLOCKS_PER_SEC<<" ms.\n-------------------\n";
//
    std::cout << "Test of default constructor of manually inserted vertex:\n\n";
    start = clock(); // Time counting begins.
    

    
    
    
    end = clock(); // Time counting ends.
    std::cout<<"Execution time: "<<1000*(double)(end-start)/CLOCKS_PER_SEC<<" ms.\n-------------------\n";

    return 0;
}