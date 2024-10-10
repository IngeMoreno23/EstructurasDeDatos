#include <iostream>
#include <sstream>
#include <cstring>

#pragma once

template <class T>
class SimpleNode{
    protected:
        T data;
        SimpleNode<T>* next;
    public:
        SimpleNode();
        SimpleNode(T data);
        SimpleNode(const SimpleNode<T>& nodeToCopy);
        ~SimpleNode();

        SimpleNode<T>* getNext();
        T getData() const;
        T& getData(); 

        void setData(T data);

        void setNext(SimpleNode<T>* nextNode);
        void operator= (const SimpleNode<T>& nodeToCopy);
        void operator= (const T newData);

        int operator>(const SimpleNode<T>& nodeB);
        void print();
};

template <class T>
SimpleNode<T>::SimpleNode(){
    this ->data=T();
    next=nullptr;
}

template <class T>
SimpleNode<T>::SimpleNode(T data){
    this ->data=data;
    next=nullptr;
}

template <class T>
void SimpleNode<T>::operator=(const SimpleNode<T>& nodeToCopy){
    this->data=nodeToCopy.data;
}

// Jun 3 13:11:26 543.89.843.57:5249 Failed password for illegal user guest
template <class T>
int SimpleNode<T>::operator>(const SimpleNode<T>& nodeB){
    return (this->data >nodeB.data);
}

template <class T>
SimpleNode<T>::SimpleNode(const SimpleNode<T>& nodeToCopy){
    this->data=nodeToCopy.data;
}


template <class T>
SimpleNode<T>::~SimpleNode(){
}

template <class T>
SimpleNode<T>* SimpleNode<T>::getNext(){
    return next;
}

template <class T> 
T SimpleNode<T>::getData() const {
    return data;
}

template <class T>
T& SimpleNode<T>::getData(){
    return data;
}

template <class T>
void SimpleNode<T>::setNext(SimpleNode<T>* next)
{
    this->next=next;
}

template <class T>
void SimpleNode<T>::setData(T data){
    this->data=data;
}

template <class T>
void SimpleNode<T>::operator=(const T newData){
    this->data=newData;
}

template <class T>
void SimpleNode<T>::print(){
    std::cout<<data;
}

template <class T>
class DoubleNode: public SimpleNode<T>{
    public:
        DoubleNode(T _data);
        DoubleNode();
        ~DoubleNode();

        DoubleNode<T>* getPrevious();
        void setPrevious(DoubleNode<T>* prev);

        DoubleNode<T>* getNext();
        virtual void setNext(DoubleNode<T>* next);

    private:
        DoubleNode<T> *prev;

};

template<class T>
DoubleNode<T>::DoubleNode(){
    prev=nullptr;
    this->next=nullptr;
    this->data=T();
};

template<class T>
DoubleNode<T>::DoubleNode(T _data){
    this->data=_data;
    prev=nullptr;
    this->next=nullptr;
};

template <class T>
DoubleNode<T>::~DoubleNode(){}

template <class T>
DoubleNode<T>* DoubleNode<T>::getPrevious(){
    return prev;
}

template <class T>
void DoubleNode<T>::setPrevious(DoubleNode<T>* previous){
    prev=previous;
}

template <class T>
DoubleNode<T>* DoubleNode<T>::getNext(){
    return static_cast<DoubleNode<T>*>(this->next);
}

template <class T>
void DoubleNode<T>::setNext(DoubleNode<T>* next){
    this->next=next;
}


template <class T, class NodeType>
class BaseLL{
    protected:
        int size;
        NodeType *head;
    public: 
        // Constructors
        BaseLL();
        BaseLL(const BaseLL<T,NodeType>& listToCopy);
        BaseLL(std::initializer_list<T> elements);
        virtual ~BaseLL();

        // Operators 
        auto& operator=(const BaseLL<T,NodeType>& listToCopy);
        T& operator[](unsigned int index); 

        // Data addition 
        virtual void append(T data) = 0;
        virtual void insert(T data, int index) = 0;

        virtual void update(T data, int index);

        //information
        int length() const; // Declarada constante puesto que se accede a esta en la sobrecarga del operador de asignación. Y regresar un valor no constante en una instancia constante causa errores. 
        bool isEmpty();
        int search(T data);
        NodeType* getNode(int index);

        virtual void print();
        void exchange(int index1, int index2);
        void invert();
        virtual void empty();
};

template <class T, class NodeType>
BaseLL<T, NodeType>::BaseLL():head(nullptr), size(0){}

template <class T, class NodeType>
BaseLL<T, NodeType>::BaseLL(std::initializer_list<T> elements){

    if(elements.size() == 0){
        head=nullptr;
    } else{
        auto iterador=elements.begin(); // crea un iterador que detecta automáticamente el tipo. 

        head = new NodeType (*iterador); // new (parametros). Manda a llamar al constructor que toma const T& como parámetro
        NodeType* currentNode = head;
        iterador++;
        size=1;

        for (; iterador != elements.end(); ++iterador){ // se puede no inicializar nada en for
            NodeType* nextNode = new NodeType (*iterador); 

            currentNode->setNext(nextNode);
            currentNode=nextNode;
            size++;
        }
        currentNode->setNext(nullptr);

    }
}

template <class T, class NodeType> 
BaseLL<T, NodeType>:: BaseLL(const BaseLL<T, NodeType>& listToCopy):head(nullptr), size(0){
    operator=(listToCopy);
}

template <class T, class NodeType>
BaseLL<T, NodeType>:: ~BaseLL(){
    if (size != 0){

        while(head != nullptr){ 
            NodeType *temp=head; 
            head=head->getNext();
            delete temp; 
        }
        size=0;
    }
}

template <class T, class NodeType>
auto & BaseLL<T, NodeType>::operator=(const BaseLL<T, NodeType>& listToCopy){

    if (this == &listToCopy){ 
        return *this;
    }

    empty();
    
    if (listToCopy.head == nullptr){
        return *this;
    }
    
    NodeType* currentNodeCopy = listToCopy.head, *currentNode = new NodeType (currentNodeCopy->getData());
    head=currentNode;

    currentNodeCopy = currentNodeCopy->getNext();

    while(currentNodeCopy != nullptr){

        NodeType* nextNode = new NodeType (currentNodeCopy.data); //usar los getters.
        currentNode->setNext(nextNode);

        currentNodeCopy = currentNodeCopy->getNext();
        currentNode = nextNode;
    }

    currentNode->setNext(nullptr);
    size = listToCopy.length();
    
    return *this;
}

template <class T, class NodeType>
T& BaseLL<T, NodeType>::operator[](unsigned int index){
    
    if (index >= size || index < 0){
        std::cout<<"Index "<<index<<" is out of range";
        throw(std::invalid_argument("Out of range"));
    }
    NodeType* currentNode = this->head;

    for(int i = 0; i < index; i++){
        currentNode=currentNode->getNext();
    }

    return currentNode->getData();
}

template <class T, class NodeType>
void BaseLL <T, NodeType>::empty(){
    while(head != nullptr){ // Se utiliza la variable head en vez de crear otra para ir accediendo los elementos. 
        NodeType *temp=this->head; 
        head=head->getNext();
        delete temp; // No se borra el apuntador, se borra lo almacenado en la dirección.
    }
    size=0;
}

template <class T, class NodeType>
void BaseLL<T, NodeType>::update(T data, int index){
    
    if(index < 0 || index >= size){
        return; 
    }

    operator[](index)=data;
}

template <class T, class NodeType>
NodeType* BaseLL<T, NodeType>::getNode(int index){
        
    if (index >= size || index < 0){
        std::cout<<"Index "<<index<<" is out of range";
        throw(std::invalid_argument("Out of range"));
    }
    NodeType* currentNode = this->head;

    for(int i = 0; i < index; i++){
        currentNode=currentNode->getNext();
    }

    return currentNode; 
}

template <class T, class NodeType>
int BaseLL<T,NodeType>::length() const {
    return size;
}

template <class T,class NodeType>
bool BaseLL<T,NodeType>::isEmpty(){
    if (head == nullptr){
        return true;
    }
    return false;
}


template <class T, class NodeType>
int BaseLL<T,NodeType>::search(T data){
    NodeType* currentNode=this->head;

    int i=0;
    while(currentNode->getNext() != nullptr && currentNode->getNext() != head ){
        if (currentNode->getData() == data){
            return i;
        }
        i++;
        currentNode=currentNode->getNext();
    }
    return -1;
}

template <class T, class NodeType>
void BaseLL<T,NodeType>::exchange(int indexA, int indexB){
    T buffer = operator[](indexA);
    operator[](indexA) = operator[](indexB);
    operator[](indexB) = buffer;
}

template <class T, class NodeType>
void BaseLL<T,NodeType>::invert(){
    int positionA = 0, half = (size % 2 ==0) ? size/2: 1 + size/2;
    while(positionA < half){
        exchange(positionA,size-positionA-1);
        positionA++;
    }
}

template <class T, class NodeType>
void BaseLL<T,NodeType>::print(){
    NodeType* currentNode = this->head;

    std::cout<<"size= "<<this->size<<" elements: ";
    while(currentNode != nullptr){
        std::cout<<currentNode->getData()<<" ";
        currentNode=currentNode->getNext();
    }
    std::cout<<std::endl;
}


template <class T>
class SimpleLL:public BaseLL<T, SimpleNode<T>>{
    public: 
        SimpleLL();
        SimpleLL(const SimpleLL<T>& listToCopy);
        SimpleLL(std::initializer_list<T> elements);

        ~SimpleLL() override;

        const SimpleLL<T>& operator =(const SimpleLL<T>& listToCopy);

        void append(const SimpleNode<T>& nodeToAppend);
        void append(const SimpleLL<T>& listToAppend); // Agrega los elementos de la segunda lista sin borrarla
        void merge(SimpleLL<T>& listToMerge); // Conecta el último elemento de la primera al primero de la segunda. 

        void erase(int index);
        void insert(SimpleNode<T>& nodeToInsert, int index);
                
        virtual void insert(T data, int index) override;
        virtual void append(T data) override;


};

template <class T>
SimpleLL<T>::SimpleLL():BaseLL<T, SimpleNode<T>>(){}

template <class T>
SimpleLL<T>::SimpleLL(std::initializer_list<T> elements):BaseLL<T, SimpleNode<T>>(elements){};

template <class T>
SimpleLL<T>::SimpleLL(const SimpleLL<T>& listToCopy){}

template <class T>
SimpleLL<T>::~SimpleLL(){
    this->empty();
}

template<class T>
void SimpleLL<T>::append(const SimpleNode<T>& nodeToAppend){
    if(this->head == nullptr){
        this->head = new SimpleNode<T> (nodeToAppend.getData());
        this->size++;
        return;
    }

    SimpleNode<T>* currentNode = this->head;
    while(currentNode->getNext() != nullptr){
        currentNode = currentNode->getNext();
    }

    currentNode->setNext(new SimpleNode<T> (nodeToAppend.getData()));
    this->size++;
}

template <class T>
const SimpleLL<T>& SimpleLL<T>::operator=(const SimpleLL<T>& listToCopy){

    if (this == &listToCopy){ 
        return *this;
    }
    this->empty();
    
    if (listToCopy.head == nullptr){
        return *this;
    }

    SimpleNode<T>* currentNodeCopy = listToCopy.head, *currentNode = new SimpleNode<T> (currentNodeCopy->getData());
    this->head=currentNode;

    currentNodeCopy = currentNodeCopy->getNext();

    while(currentNodeCopy != nullptr){
        SimpleNode<T>* nextNode = new SimpleNode<T> (currentNodeCopy->getData()); //usar los getters.
        currentNode->setNext(nextNode);
        currentNodeCopy = currentNodeCopy->getNext();
        currentNode = nextNode;
    }

    currentNode->setNext(nullptr);
    this->size = listToCopy.length();
    
    return *this;
}

template <class T>
void SimpleLL<T>::erase(int index){

    if(index >= this->size || index < 0 || this->head == nullptr){
        std::cerr<<"Out of range";
        return;
    } else if (this->size == 1){
        delete this->head; 
        this->head=nullptr;
        this->size=0;
        return;
    }

    SimpleNode<T> * prevNode = (index != 0) ? this->getNode(index-1): this->head;
    SimpleNode<T> * nodeToErase = prevNode->getNext();
    prevNode->setNext(nodeToErase->getNext());

    delete nodeToErase;

}

template <class T>
void SimpleLL<T>::merge(SimpleLL<T>& listToAppend){
    getNode(this->size-1)->setNext(listToAppend.head);
    listToAppend.head=nullptr;
}

template <class T>
void SimpleLL<T>::append(const SimpleLL<T>& listToAppend){
    SimpleNode<T>* currentNode=getNode(this->size-1), *currentCopyNode=listToAppend.head;
    while(currentCopyNode != nullptr){
        SimpleNode<T> *newNode = new SimpleNode<T> (currentCopyNode.data);
        currentNode -> setNext(currentCopyNode);
        currentNode = currentNode -> getNext();
        currentCopyNode = currentCopyNode -> getNext();
    }
    listToAppend.head=nullptr;
}

template <class T>
void SimpleLL<T>::insert(SimpleNode<T>& nodeToInsert, int index){
    SimpleNode<T>* currentNode= this->getNode(index);
    SimpleNode<T>* nextCurrentNode=currentNode->getNext();

    currentNode->setNext(new SimpleNode<T> (nodeToInsert.getData()));
    currentNode->getNext()->setNext(nextCurrentNode);
}


template <class T>
void SimpleLL<T>::insert(T data, int index){
    this->insert(* new SimpleNode<T> (data), index);
}

template <class T>
void SimpleLL<T>::append(T data){
    SimpleNode<T>* temp = new SimpleNode<T> (data);
    this->append(*temp);
    delete temp;
}



template<class T>
class DoubleLL:public BaseLL<T, DoubleNode<T>>{
    public:
        DoubleLL();
        DoubleLL(const DoubleLL<T>& listToCopy);
        DoubleLL(std::initializer_list<T> elements);
        ~DoubleLL() override;

        const DoubleLL<T>& operator=(DoubleLL<T> & listToCopy);

        void append(const DoubleNode<T>& nodeToAppend);
        virtual void append(T data) override;

        void append(const DoubleLL<T>& listToAppend); // Agrega los elementos de la segunda lista sin borrarla
        void merge(DoubleLL<T>& listToAppend); // Conecta el último elemento de la primera al primero de la segunda. 

        virtual void erase(int index) ;

        virtual void insert(T data, int index) override;
        virtual void insert(DoubleNode<T>& nodeToInsert, int index);

        void empty() override;
        void print();

        class Iterator{
            private:
                DoubleNode<T> *current;
                DoubleNode<T> *head;
            public:
                Iterator(DoubleNode<T> *currentNode, DoubleNode<T> *headNode);

                T& operator*();
                Iterator& operator++();
                Iterator& operator--();
                bool operator!=(const Iterator& otro) const;
        };
        Iterator begin();
        Iterator end();
};

template <class T>
DoubleLL<T>::DoubleLL(){ 
    this->head = nullptr;        
}

template <class T> 
DoubleLL<T>::~DoubleLL(){
    empty();
    delete this->head;
}

template <class T>
void DoubleLL<T>::empty(){
    if(this->size == 0){
        return;
    }

    DoubleNode<T>* current = this->head;

    while ( current != this->head){
        DoubleNode<T> *temp = current; 
        current = current->getNext();
        delete temp; 
    }
    this->head->setNext(nullptr);
    this->head->setPrevious(nullptr);   
    this->head =nullptr;
 
    this->size=0;
}

template <class T>
DoubleLL<T>::DoubleLL(std::initializer_list<T> elements){
    
    this->size=0;
    
    if(elements.size() == 0){
        this->head = nullptr;
    } else{
        auto iterador = elements.begin(); 

        this->head = new DoubleNode<T> (*iterador); 
        DoubleNode<T>* currentNode = this->head;
        currentNode->setPrevious(this->head);
        iterador++;
        this->size = 1;

        for (; iterador != elements.end(); ++iterador){
            DoubleNode<T>* nextNode = new DoubleNode<T> (*iterador); 
            currentNode->setNext(nextNode);
            nextNode->setPrevious(currentNode);
            currentNode = nextNode;
            this->size++;
        }
        
        currentNode->setNext(this->head);
        this->head->setPrevious(currentNode);
    }
}

template <class T>
DoubleLL<T>:: DoubleLL(const DoubleLL<T>& listToCopy){
    this->head = new DoubleNode<T>;

    this->head->setNext(this->head);
    this->head->setPrevious(this->head);
        
    *this = listToCopy; // Usar *this para referirse al objeto y poder mandar llamar a la sobrecarga de asignación. 
}

template <class T>
void DoubleLL<T>::append(const DoubleNode<T>& nodeToAppend){
    if(this->head == nullptr){
        DoubleNode<T>* newNode=new DoubleNode<T> (nodeToAppend.getData());
        this->head=newNode;
        newNode->setPrevious(this->head);
        newNode->setNext(this->head);
        this->size++;
        return;
    }

    DoubleNode<T>* newNode=new DoubleNode<T> (nodeToAppend.getData());
    this->head->getPrevious()->setNext(newNode);
    newNode->setNext(this->head);
    newNode->setPrevious(this->head->getPrevious());
    this->head->setPrevious(newNode);
    this->size++;
}

template <class T>
void DoubleLL<T>::append(const DoubleLL<T>& listToAppend){
    if (listToAppend.size == 0){
        return;
    }
    
    DoubleNode<T>* currentNode=this->head->getPrevious(), *currentNodeCopy=listToAppend.head;

    if(this->head == nullptr){
        this -> head = new DoubleNode<T> (listToAppend.head->getData());
        currentNode=this->head;
        this->head->setNext(currentNode);
        this->head->setPrevious(currentNode);
    } else{
        DoubleNode<T>* nextNode = new DoubleNode<T> (currentNodeCopy->getData());
        currentNode->setNext(nextNode);
        nextNode->setPrevious(currentNode);
        currentNode = nextNode;
    }
    currentNodeCopy= currentNodeCopy->getNext();

    while(currentNodeCopy != listToAppend.head){
        DoubleNode<T>* nextNode = new DoubleNode<T> (currentNodeCopy->getData());
        currentNode->setNext(nextNode);
        nextNode->setPrevious(currentNode);
        currentNode = nextNode;
        
        currentNodeCopy = currentNodeCopy->getNext();
    }
    
    currentNode->setNext(this->head);
    currentNode->setPrevious(this->head->getPrevious());
    this->head->setPrevious(currentNode);
    this->size += listToAppend.size;
}

template <class T>
void DoubleLL<T>::merge(DoubleLL<T>& listToAppend){
    if (listToAppend.size == 0){
        return;
    }
    if(this->size==0){
        this->head=listToAppend.head;
        listToAppend.head=nullptr;
        return;
    }

    DoubleNode<T>* listToAppendHeadCopy = new DoubleNode<T> (listToAppend.head->getData());    
    DoubleNode<T>* temp = this->head->getPrevious();

    temp->setNext(listToAppendHeadCopy);
    listToAppend.head->getPrevious()->setNext(this->head);
    
    listToAppendHeadCopy->setPrevious(temp);
    this->head->setPrevious(listToAppend.head->getPrevious()); // cambié aquí
    listToAppendHeadCopy->setNext(listToAppend.head->getNext());
    this->size+=listToAppend.size;

    listToAppend.head->setNext(nullptr);
    listToAppend.head->setPrevious(nullptr);
    listToAppend.size=0;
}

template<class T>
const DoubleLL<T> & DoubleLL<T>::operator=(DoubleLL<T> & listToCopy) {
    if (this == &listToCopy){ 
        return *this;
    }
    
    empty();    

    if (listToCopy.head == nullptr){
        return *this;
    }

    DoubleNode<T>* currentNodeCopy = listToCopy.head, *currentNode = new DoubleNode<T> (currentNodeCopy->getData());
    this->head = currentNode;

    currentNodeCopy = currentNodeCopy->getNext();

    while(currentNodeCopy != listToCopy.head){

        DoubleNode<T>* nextNode = new DoubleNode<T> (currentNodeCopy->getData());
        currentNode->setNext(nextNode);
        nextNode->setPrevious(currentNode);
        currentNodeCopy=currentNodeCopy->getNext();
        currentNode=nextNode;
    }

    currentNode->setNext(this->head);
    this->head->setPrevious(currentNode);

    this->size = listToCopy.size;

    return *this;
}

template <class T>
void DoubleLL<T>::erase(int index){


    if(index >= this->size || index < 0 || this->head==nullptr){
        std::cerr<<"Out of range";
        return;
    } else if (this->size == 1){
        delete this->head; 
        this->head=nullptr;
        this->size=0;
        return;
    }


    DoubleNode<T>* currentNode = this->head; // una variable que guarda un apuntador. NO es memoria dinámica.

    if (index == 1){
        this->head = currentNode->getNext();
        delete currentNode; // se puede borrar con delete el contenido de una variable que almacena un apuntador, aún cuando esta variable en particular no fue la que asignó memoria con new.
    } else{
        for(int i = 0;i <= index; i++){
            currentNode = currentNode->getNext();
        }
        DoubleNode<T>*temp = currentNode->getNext();
        temp->getNext()->setPrevious(currentNode);
        currentNode->setNext(temp->getNext());
        delete temp;
    }
    this->size--;
}

template <class T>
void DoubleLL<T>::insert(T data, int index){
    this->insert(* new DoubleNode<T> (data), index);
}

template <class T>
void DoubleLL<T>::append(T data){
    DoubleNode<T>* temp = new DoubleNode<T> (data);
    this->append(*temp);
    delete temp;
}

template <class T>
void DoubleLL<T>::print(){
    DoubleNode<T>* currentNode = this->head;

    std::cout<<"size= "<<this->size<<" elements: ";
    while(currentNode != nullptr){
        std::cout<<currentNode->getData()<<" ";
        currentNode=currentNode->getNext();
    }
    std::cout<<std::endl;
}

template <class T>
void DoubleLL<T>::insert(DoubleNode<T>& nodeToInsert, int index){
    if(index >= this->size || index < 0){
        std::cerr<<"Out of range, appending instead";
        append(nodeToInsert);
        return;
    }

    DoubleNode<T>* currentNode = this->head;
    for(int i = 1; i < index; i++){
        currentNode= currentNode->getNext();
    }

    // nodeToInsert.setNext(currentNode -> getNext()); Antes usaba este código, pero me di cuenta que es mejor asignar la memoria nuevamente. Aunque esto también se puede hacer antes de llamar a la función, siento que hacerlo desde la función es más sólido. 
    DoubleNode<T>* newNode = new DoubleNode<T> (nodeToInsert.getData());
    newNode->setNext(currentNode->getNext());
    newNode->setPrevious(currentNode);
    
    newNode->getNext() -> setPrevious(newNode);

    currentNode->setNext(newNode);
    this->size++;
}

template <class T>
DoubleLL<T>::Iterator::Iterator(DoubleNode<T>* currentNode, DoubleNode<T>* headNode) 
    : current(currentNode), head(headNode) {}

template <class T>
T& DoubleLL<T>::Iterator::operator*() {
    return current->getData();
}

template <class T>
class DoubleLL<T>::Iterator& DoubleLL<T>::Iterator::operator++() {
    current = current->getNext();
    return *this;
}

template <class T>
class DoubleLL<T>::Iterator& DoubleLL<T>::Iterator::operator--() {
    current = current->getPrevious();
    return *this;
}

template <class T>
bool DoubleLL<T>::Iterator::operator!=(const Iterator& otro) const {
    return current != otro.current;
}

template <class T>
class DoubleLL<T>::Iterator DoubleLL<T>::begin() {
    return Iterator(this->head, this->head);
}

template <class T>
class DoubleLL<T>::Iterator DoubleLL<T>::end() {
    return Iterator(this->head, this->head);
}

template <class T>
int busquedaBinaria(const DoubleLL<T>& l, std::string clave, bool upper){
    int inicio=0, final=l.length(), ultimaInstancia=0;
    
    while (inicio <= final){
        int mitad = inicio+(final-inicio)/2;
        std::string ip = obtainIp(l[mitad]);
        int comparacion = ip > clave;

        if (upper ){
            ultimaInstancia=mitad;
        }
        if (comparacion){
            final = mitad-1;
        } else{
            inicio = mitad+1;
        }
    }
    return ultimaInstancia;
}

int operator>( std::string& a,  std::string& b){
    int numAct1=0, numAct2=0;

    std::stringstream ssStr1(a), ssStr2(b);
    while(ssStr1>>numAct1 && ssStr2 >> numAct2)
    {    
        if (numAct1>numAct2){
            return 1;
        } else if (numAct2>numAct1) {
            return 0;
        }
        ssStr1.ignore();
        ssStr2.ignore();
    }
    return 0;
}

std::string obtainIp(const std::string& str){
    std::stringstream ssStr(str);
    std::string ip;
    for(int i=0; i<4; i++){
        ssStr>>ip;
    }
    return ip;
}

template <class T>
void ordMerge(DoubleLL<T> &l, int n) {
    if (n == 1) return;

    int mitad = n / 2;
    DoubleLL<T> l1, l2;
    
    for (int i = 0; i < mitad; i++) l1.append(l[i]);
    for (int i = mitad; i < n; i++) l2.append(l[i]);

    ordMerge(l1, mitad);
    ordMerge(l2, n - mitad);

    int i = 0, j = 0, k = 0;

    while (i < mitad && j < n - mitad) {
        std::string a = obtainIp(l1[i]), b=obtainIp(l2[j]);
        if (a>b) {
            l[k] = l2[j];
            j++;
        } else {
            l[k] = l1[i];
            i++;
        }
        k++;
    }

    while (i < mitad) {
        l[k] = l1[i];
        i++;
        k++;
    }

    while (j < n - mitad) {
        l[k] = l2[j];
        j++;
        k++;
    }
}
