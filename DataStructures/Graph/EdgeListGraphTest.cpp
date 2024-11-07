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
    

    EdgeListGraph<int, int> graphDefault;
    graphDefault.print();
    

    end = clock(); // Time counting ends.
    std::cout<<"Execution time: "<<1000*(double)(end-start)/CLOCKS_PER_SEC<<" ms.\n-------------------\n";
//
    std::cout << "Test of default constructor of manually inserted vertex:\n\n";
    start = clock(); // Time counting begins.
    

    EdgeListGraph<int, int> graphManual;
    EdgeListVertex<int, int> vertex1, vertex2, vertex3;
    vertex1.setVertex(1); vertex2.setVertex(2); vertex3.setVertex(3);
    vertex1.setNextVertex(&vertex2); vertex2.setNextVertex(&vertex3);
    graphManual.setVertex(&vertex1);
    graphManual.print();
    

    end = clock(); // Time counting ends.
    std::cout<<"Execution time: "<<1000*(double)(end-start)/CLOCKS_PER_SEC<<" ms.\n-------------------\n";
//
    std::cout << "Test of default constructor with edges:\n\n";
    start = clock(); // Time counting begins.


    EdgeListGraph<int, int> graphManualEdges;
    EdgeListVertex<int, int> vertex4, vertex5, vertex6;
    vertex4.setVertex(4); vertex5.setVertex(5); vertex6.setVertex(6);
    int num1=1, num2=2, num3=3, num4=4, num5=5, num6=6;
    EdgeListEdge<int, int> edge4_5(num4, num5, num1), edge4_6(num4, num6, num4), edge5_6(num5, num6, num2), edge6_4(num6, num4, num3);
    // Unable due to the reference of the vertex.
    // edge4_5.setVertexOrigin(4); edge4_5.setVertexDestination(5); edge4_5.setWeight(1);
    // edge4_6.setVertexOrigin(4); edge4_6.setVertexDestination(6); edge4_6.setWeight(4);
    // edge5_6.setVertexOrigin(5); edge5_6.setVertexDestination(6); edge5_6.setWeight(2);
    // edge6_4.setVertexOrigin(6); edge6_4.setVertexDestination(4); edge6_4.setWeight(3);

    vertex4.setNextEdgeOrigin(&edge4_5); vertex4.getNextEdgeOrigin()->setNextEdgeOrigin(&edge4_6); vertex5.setNextEdgeOrigin(&edge5_6); vertex6.setNextEdgeOrigin(&edge6_4);
    vertex5.setNextEdgeDestination(&edge4_5); vertex6.setNextEdgeDestination(&edge4_6); vertex6.getNextEdgeDestination()->setNextEdgeDestination(&edge5_6); vertex4.setNextEdgeDestination(&edge6_4);

    vertex4.setNextVertex(&vertex5); vertex5.setNextVertex(&vertex6);
    graphManual.setVertex(&vertex4);

    graphManual.print();
    graphManual.printOrigin();
    graphManual.printDestination();


    end = clock(); // Time counting ends.
    std::cout<<"Execution time: "<<1000*(double)(end-start)/CLOCKS_PER_SEC<<" ms.\n-------------------\n";
//
    std::cout << "Test of graph param constructor:\n\n";
    start = clock(); // Time counting begins.


    EdgeListGraph<int, int> graphWithoutWeights({
        {1, {3, 2}},
        {2, {3}},
        {3, {1}},
        {0, {}}
    });
    

    graphWithoutWeights.print();
    graphWithoutWeights.printOrigin();
    graphWithoutWeights.printDestination();


    end = clock(); // Time counting ends.
    std::cout<<"Execution time: "<<1000*(double)(end-start)/CLOCKS_PER_SEC<<" ms.\n-------------------\n";
//
    std::cout << "Test of addition of vertex:\n\n";
    start = clock(); // Time counting begins.

    int vertexToAdd = 4;
    graphWithoutWeights.addVertex(vertexToAdd);

    graphWithoutWeights.updateVertex(1, 5);
    

    graphWithoutWeights.print();
    graphWithoutWeights.printOrigin();
    graphWithoutWeights.printDestination();


    end = clock(); // Time counting ends.
    std::cout<<"Execution time: "<<1000*(double)(end-start)/CLOCKS_PER_SEC<<" ms.\n-------------------\n";
//
    std::cout << "Test 1000 vertex:\n\n";
    std::map<int, std::initializer_list<int>> graph1000;
    for(int i=0; i<1000; i++){
        graph1000[i] = {i+1};
        for(int j=0; j<1000; j++){
            graph1000[i] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
                21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
                31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
                41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
                51, 52, 53, 54, 55, 56, 57, 58, 59, 60,
                61, 62, 63, 64, 65, 66, 67, 68, 69, 70,
                71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
                81, 82, 83, 84, 85, 86, 87, 88, 89, 90,
                91, 92, 93, 94, 95, 96, 97, 98, 99, 100};
        }
    };
    start = clock(); // Time counting begins.

    EdgeListGraph<int, int> graph1000Vertices(graph1000);
    // graph1000Vertices.print();
    // graph1000Vertices.printOrigin();
    // graph1000Vertices.printDestination();


    end = clock(); // Time counting ends.
    std::cout<<"Execution time: "<<1000*(double)(end-start)/CLOCKS_PER_SEC<<" ms.\n-------------------\n";
//
    std::cout << "Test inverted 1000 vertex (Worst case due to linked list spliting maybe):\n\n";
    std::map<int, std::initializer_list<int>> graphMinus1000;
    for(int i=0; i<1000; i++){
        graphMinus1000[i] = {1000-i};
        for(int j=0; j<1000; j++){
            graphMinus1000[i] = {
                100, 99, 98, 97, 96, 95, 94, 93, 92, 91,
                90, 89, 88, 87, 86, 85, 84, 83, 82, 81,
                80, 79, 78, 77, 76, 75, 74, 73, 72, 71,
                70, 69, 68, 67, 66, 65, 64, 63, 62, 61,
                60, 59, 58, 57, 56, 55, 54, 53, 52, 51,
                50, 49, 48, 47, 46, 45, 44, 43, 42, 41,
                40, 39, 38, 37, 36, 35, 34, 33, 32, 31,
                30, 29, 28, 27, 26, 25, 24, 23, 22, 21,
                20, 19, 18, 17, 16, 15, 14, 13, 12, 11,
                10, 9, 8, 7, 6, 5, 4, 3, 2, 1
            };
        }
    };
    start = clock(); // Time counting begins.

    EdgeListGraph<int, int> graphMinus1000Vertices(graphMinus1000);
    // graphMinus1000Vertices.print();
    // graphMinus1000Vertices.printOrigin();
    // graphMinus1000Vertices.printDestination();


    end = clock(); // Time counting ends.
    std::cout<<"Execution time: "<<1000*(double)(end-start)/CLOCKS_PER_SEC<<" ms.\n-------------------\n";


    return 0;
}