// Name: Edison Freire
// Date: 4/4/23

#include "DoublyLinkedList.hpp"
#include "CardShop.cpp"

int main() {
    std::cout << "TEST CASE: SWAP WITH 2 ELEMENTS\n";
    DoublyLinkedList<int> list1;
    list1.insert(0, 9);
    list1.insert(1, 8);
    list1.display();
    list1.swap(0,1);
    list1.display();
    // worked
    std::cout << std::endl;
    std::cout << "TEST CASE: SWAP FIRST AND LAST ELEMENTS WHEN THERE IS MORE THAN 2 ELEMENTS\n";
    DoublyLinkedList<int> list2;
    list2.insert(0, 5);
    list2.insert(1, 6);
    list2.insert(2, 7);
    list2.insert(3, 8);
    list2.insert(4, 9);
    list2.display();
    list2.swap(0,4); // swapping index 0 and 4
    list2.display();
    // worked
    std::cout << std::endl;
    std::cout << "TEST CASE: SWAP 2 MIDDLE ELEMENTS THAT ARE NOT SUCCESSIVE\n";
    DoublyLinkedList<int> list3;
    list3.insert(0, 10);
    list3.insert(1, 11);
    list3.insert(2, 12);
    list3.insert(3, 13);
    list3.insert(4, 14);
    list3.display();
    list3.swap(1, 3);
    list3.display();
    // worked
    std::cout << std::endl;
}