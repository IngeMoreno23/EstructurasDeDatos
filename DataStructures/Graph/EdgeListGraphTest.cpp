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
    std::cout << "Test of default constructor with edges:\n\n";
    start = clock(); // Time counting begins.


    EdgeListGraph<int> graphManualEdges;
    EdgeListVertex<int> vertex4, vertex5, vertex6;
    vertex4.setVertex(4); vertex5.setVertex(5); vertex6.setVertex(6);
    EdgeListEdge<int> edge4_5, edge4_6, edge5_6, edge6_4;
    edge4_5.setVertexOrigin(4); edge4_5.setVertexDestination(5); edge4_5.setWeight(1);
    edge4_6.setVertexOrigin(4); edge4_6.setVertexDestination(6); edge4_6.setWeight(4);
    edge5_6.setVertexOrigin(5); edge5_6.setVertexDestination(6); edge5_6.setWeight(2);
    edge6_4.setVertexOrigin(6); edge6_4.setVertexDestination(4); edge6_4.setWeight(3);

    vertex4.setNextEdgeOrigin(&edge4_5); vertex4.getNextEdgeOrigin()->setNextEdgeOrigin(&edge4_6); vertex5.setNextEdgeOrigin(&edge5_6); vertex6.setNextEdgeOrigin(&edge6_4);
    vertex5.setNextEdgeDestination(&edge4_5); vertex6.setNextEdgeDestination(&edge4_6); vertex6.getNextEdgeDestination()->setNextEdgeDestination(&edge5_6); vertex4.setNextEdgeDestination(&edge6_4);

    vertex4.setNextVertex(&vertex5); vertex5.setNextVertex(&vertex6);
    graphManual.setVertex(&vertex4);

    graphManual.print();
    graphManual.printOrigin();
    graphManual.printDestination();


    end = clock(); // Time counting ends.
    std::cout<<"Execution time: "<<1000*(double)(end-start)/CLOCKS_PER_SEC<<" ms.\n-------------------\n";

    return 0;
}