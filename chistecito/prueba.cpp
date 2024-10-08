#include <future>
#include <iostream>
#include <chrono>
#include "chamba.cpp"

using namespace std;

int main() {
    try{
        future<int> results = async(launch::async, chamba);
    } catch(const exception& e) {        
        cerr<<"Error: "<<e.what();
        this_thread::sleep_for(chrono::hours(3));
    }
    return 0;
}

