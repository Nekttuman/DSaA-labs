#include "LinkedList.cpp"
#include <iostream>



int main(){
    // constructors
    LinkedList<int> list1;
    std::cout<<"create empty ll: "<<list1;


    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    LinkedList<int> list2(arr,10);
    std::cout<<"create list based on int array[10] : "<<list2;

    LinkedList<int> list3(list2);
    std::cout<<"create copy of list2 throw copy constractor: "<<list3;

    list3.replace(5,111);
    std::cout << "replace 5 element in list3 to 111 :" << list3;
    std::cout << "list 2 want changed: " << list2;

    std::cout<<"\npush_back tests:\n\n";
    list1.push_back(123);
    std::cout<<"push_back in empty list: "<<list1;
    list2.push_back(11);
    std::cout<<"push_back in nonempty list: "<<list2;

    std::cout<<"\npop_back tests:\n\n";
    list1.pop_back();
    std::cout<<"pop_back from ll with 1 elem: "<<list1;

    std::cout<<"\n\ninsert ll into ll test\n\n";
    std::cout<<"ll1: "<<list2;
    std::cout<<"ll2: "<<list3;
    list3.insert_ll(list2, 3);
    std::cout<<"list2.insert_ll(list1, 3) ll2: "<<list3;
    return 0;
}

