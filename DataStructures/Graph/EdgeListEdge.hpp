#include <iostream>

template <typename T>
class EdgeListEdge{
    private:
        T vertexOrigin; // Origin vertex of the edge.
        T vertexDestination; // Destination vertex of the edge.
        double weight;
        EdgeListEdge<T>* nextEdgeOrigin; // ptr to the next edge that has the same origin.
        EdgeListEdge<T>* nextEdgeDestination; // ptr to the next edge that has the same destination.
    public:
        EdgeListEdge();
        EdgeListEdge(T vertexOrigin, T vertexDestination, double weight);
        EdgeListEdge(const EdgeListEdge& otherEdge);
        const EdgeListEdge& operator=(const EdgeListEdge& otherEdge);
        ~EdgeListEdge();

        T getVertexOrigin();
        T getVertexDestination();
        double getWeight();
        EdgeListEdge<T>* getNextEdgeOrigin();
        EdgeListEdge<T>* getNextEdgeDestination();

        void setVertexOrigin(T vertexOrigin);
        void setVertexDestination(T vertexDestination);
        void setWeight(double weight);
        void setNextEdgeOrigin(EdgeListEdge<T>* nextEdgeOrigin);
        void setNextEdgeDestination(EdgeListEdge<T>* nextEdgeDestination);

        void print();
};

/*
PARAMETERS: None.
METHOD: Prints the edge in the format "(vertexOrigin, vertexDestination, weight)".
ORDER OF EXECUTION: O(1).
RETURN: None.
*/
template <typename T>
void EdgeListEdge<T>::print(){
    std::cout<<"("<<vertexOrigin<<", "<<vertexDestination<<", "<<weight<<")";
}