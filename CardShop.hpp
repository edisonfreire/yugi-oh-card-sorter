// Name: Edison Freire
// Date: 4/4/23

#ifndef CARD_SHOP_HPP_
#define CARD_SHOP_HPP_
#include "DoublyLinkedList.hpp"
#include "YGOCard.hpp"
#include <iostream>
#include <fstream>
#include <sstream>


class CardShop : public DoublyLinkedList<YGOCard *>
{
public:
  CardShop() = default; //default constructor
  ~CardShop();          //destructor calls clear

  /**
  @pre  : the input file is in csv format: "name,type,level_rank,race,attribute,atk,def"
  @param: the name of the input file
  @post:  Reads the input file and adds pointers to YGOCard objects 
          instantiated with the information read from the file. 
    */
  CardShop(std::string input_file_name); //parameterized constructor

  //@post: displays information of all cards in the shop, one per line
  void display();

  //@param: the index of the first card to be displayed
  //@param: the index of the last card to be displayed
  //@post: displays the names of all cards in the shop with startRange and endRange, 
  //       inclusive, one per line
  void displayName(int startRange, int endRange);

  //@post: removes all cards from the shop
  void clear();                               

  //@return:  true if all the cards in rhs are equal to the cards in the shop, false otherwise
  bool operator==(const CardShop &rhs) const; 

  /**
    @param: comp can be std::less<int>{} (This is used for sorting in descending order.) 
    or std::greater<int>{} (This is used for sorting in ascending order.)
    @param: key can be "atk" (to sort by attack values) or "def" (to sort by defense values)
    @return: number of swaps used in Bubble Sort
  */
  template<typename Comparator>
  int bubbleSort(Comparator comp, const std::string &key);

  /**
    @param: comp can be std::less<int>{} (This is used for sorting in descending order.) 
    or std::greater<int>{} (This is used for sorting in ascending order.)
    @param: key can be "atk" (to sort by attack values) or "def" (to sort by defense values)
    @return: number of swaps used in Insertion Sort
  */
  template<typename Comparator>
  int insertionSort(Comparator comp, const std::string &key);
  
  /**
    @param: comp can be std::less<int>{} (This is used for sorting in descending order.) 
    or std::greater<int>{} (This is used for sorting in ascending order.)
    @param: key can be "atk" (to sort by attack values) or "def" (to sort by defense values)
    @return: number of swaps used in Quick Sort
  */
  template<typename Comparator>
  int quickSort(Comparator comp, const std::string &key);

  /**
    @param: comp can be std::less<int>{} (This is used for sorting in descending order.) 
    or std::greater<int>{} (This is used for sorting in ascending order.)
    @param: key can be "atk" (to sort by attack values) or "def" (to sort by defense values)
    @param: low index
    @param: high index
    @param: count
    @return: partition index
  */
  template<typename Comparator>
  int partition(Comparator comp, const std::string &key, int low, int high, int &count);

  /**
    @param: comp can be std::less<int>{} (This is used for sorting in descending order.) 
    or std::greater<int>{} (This is used for sorting in ascending order.)
    @param: key can be "atk" (to sort by attack values) or "def" (to sort by defense values)
    @param: low index
    @param: high index
    @param: count
    @post: implements the quicksort recursive alogorithm
  */
  template<typename Comparator>
  void quickSortRecursive(Comparator comp, const std::string &key, int low, int high, int &count);

  // not implemented
  template<typename Comparator>
  int mergeSort(Comparator comp, const std::string &key);
};

#endif