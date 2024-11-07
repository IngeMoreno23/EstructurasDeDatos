#include <iostream>


int main(){

    std::string str1 = "Jun 3 13:11:26 543.89.843.57:5249 Failed password for illegal user guest";
    std::string str2 = "Jul 14 10:06:22 484.5.450.83:5926 Illegal user";
    int str1BaseIndex= str1.find_first_of(' ', 4);
    int str2BaseIndex= str2.find_first_of(' ', 4);
    int str1FirstIndex = (str1BaseIndex == 5) ? 15 : 16;
    int str2FirstIndex = (str2BaseIndex == 5) ? 15 : 16;
    int str1SecondIndex = str1.find_first_of(' ', str1FirstIndex);
    int str2SecondIndex = str2.find_first_of(' ', str2FirstIndex);
    std::string ip1= str1.substr(str1FirstIndex, 5), ip2= str2.substr(str2FirstIndex, 5);
    std::cout << str1 << "   " << str2 << std::endl;
    std::cout << str1BaseIndex << "   " << str2BaseIndex << std::endl;
    std::cout << ip1 << "   " << ip2;
    return 0;
}



    if (n == 1) return;
    int mitad = n / 2;
    LinkedList<T> l1, l2;
    for (int i = 0; i < mitad; i++) l1.append(l[i]);
    for (int i = mitad; i < n; i++) l2.append(l[i]);
    ordMerge(l1, mitad);
    ordMerge(l2, n - mitad); 
    int i = 0, j = 0, k = 0;
    while (i < mitad && j < n - mitad) {
        if (cmpIP(l1[i],l2[i]) > 0 ) {
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


    if (n == 1) return;
    int mitad = n / 2;
    LinkedList<T> l1, l2;
    for (int i = 0; i < mitad; i++) l1.append(l[i]);
    for (int i = mitad; i < n; i++) l2.append(l[i]);
    ordMerge(l1, mitad);
    ordMerge(l2, n - mitad);
    int i = 0, j = 0, k = 0;
    while (i < mitad && j < n - mitad) {
        if (cmpIP(l1[i], l2[j]) > 0) {
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