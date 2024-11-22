#include "HashMap.hpp"
    
int main(){

    HashMap<int, int> map(myHash);
    map.insert("0.", 10);
    map.insert(2, 20);
    map.insert(11, 30);

    map.show();

    return 0;
}