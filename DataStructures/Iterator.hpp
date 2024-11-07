template <class dsElement>
class Iterator{
    private:
        dsElement *current;
    public:
        Iterator(dsElement *currentNode);

        T& operator*();
        Iterator& operator++();
        Iterator& operator--();
        Iterator& operator+(unsigned int transIndex);
        Iterator& operator-(unsigned int transIndex);
        bool operator!=(const Iterator& otro) const;
};
        