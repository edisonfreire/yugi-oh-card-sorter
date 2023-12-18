// Name: Edison Freire
// Date: 4/4/23

#include "CardShop.hpp"
#include "Node.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

/**
  @pre  : the input file is in csv format: "name,type,level_rank,race,attribute,atk,def"
  @param: the name of the input file
  @post:  Reads the input file and adds pointers to YGOCard objects
          instantiated with the information read from the file.
    */
CardShop::CardShop(std::string input_file_name)
{
  std::ifstream fin(input_file_name);
  if (fin.fail())
  {
    std::cerr << "File cannot be opened for reading. \n";
    exit(1); // exit if failed to open the file
  }
  // we don't use the first line
  std::string ignore;
  getline(fin, ignore);

  // the columns of the csv associated with the data members
  std::string name, type, race, attribute;
  int level_rank, atk, def;

  std::string temp_string;
  int temp_int;
  int item_counter = 0;
  while (getline(fin, temp_string, ','))
  {
    name = temp_string;

    getline(fin, type, ',');

    getline(fin, temp_string, ',');
    std::istringstream(temp_string) >> temp_int;
    level_rank = temp_int;

    getline(fin, race, ',');

    getline(fin, attribute, ',');

    getline(fin, temp_string, ',');
    std::istringstream(temp_string) >> temp_int;
    atk = temp_int;

    getline(fin, temp_string);
    std::istringstream(temp_string) >> temp_int;
    def = temp_int;

    // create new card
    YGOCard *card_ptr = new YGOCard(name, type, level_rank, race, attribute, atk, def);

    // add to linked list and increment counter
    insert(item_counter++, card_ptr);
  }
}

//@post: removes all cards from the shop
// Deallocate and delete items
void CardShop::clear()
{
  for (int i = 0; i < item_count_; i++)
  {
    YGOCard *ptr = getItem(i);
    delete ptr;
    ptr = nullptr;
  }
  DoublyLinkedList::clear();
}

// destructor
CardShop::~CardShop()
{
  clear();
}

//@post: displays information of all cards in the shop, one per line
void CardShop::display()
{
  for (int i = 0; i < item_count_; i++)
  {
    getItem(i)->display();
  }
}

//@param: the index of the first card to be displayed
//@param: the index of the last card to be displayed
//@post: displays the names of all cards in the shop with startRange and endRange,
//       inclusive, one per line
void CardShop::displayName(int startRange, int endRange)
{
  for (int i = startRange; i <= endRange; i++)
  {
    getItem(i)->displayName();
    if (i != endRange)
    {
      std::cout << ", ";
    }
    else
    {
      std::cout << std::endl;
    }
  }
}

// @return:  true if all the cards in rhs are equal to the cards in the shop, false otherwise
bool CardShop::operator==(const CardShop &rhs) const
{
  if (getLength() != rhs.getLength())
  {
    return false;
  }
  for (int i = 0; i < getLength(); i++)
  {
    if (*(getPointerTo(i)->getItem()) == *(rhs.getPointerTo(i)->getItem()))
    {
    }
    else
    {
      return false;
    }
  }
  return true;
}

/**
  @param: comp can be std::less<int>{} (This is used for sorting in descending order.) 
  or std::greater<int>{} (This is used for sorting in ascending order.)
  @param: key can be "atk" (to sort by attack values) or "def" (to sort by defense values)
  @return: number of swaps used in Bubble Sort
*/
template <typename Comparator>
int CardShop::bubbleSort(Comparator comp, const std::string &key)
{
  int size = getLength();
  bool swapped = true;
  int pass = 1;
  int sort_count = 0;
  while (swapped && (pass < size))
  {
    swapped = false;
    for (int index = 0; index < size - pass; index++)
    {
      if (key == "atk")
      {
        if (comp(getItem(index + 1)->getAtk(), getItem(index)->getAtk()))
        {
          swap(index + 1, index);
          swapped = true;
          sort_count++;
        }
      }
      else if (key == "def")
      {
        if (comp(getItem(index + 1)->getDef(), getItem(index)->getDef()))
        {
          swap(index + 1, index);
          swapped = true;
          sort_count++;
        }
      }
    }
    pass++;
  }
  return sort_count;
}

/**
  @param: comp can be std::less<int>{} (This is used for sorting in descending order.) 
  or std::greater<int>{} (This is used for sorting in ascending order.)
  @param: key can be "atk" (to sort by attack values) or "def" (to sort by defense values)
  @return: number of swaps used in Insertion Sort
*/
template <typename Comparator>
int CardShop::insertionSort(Comparator comp, const std::string &key)
{
  int size = getLength();
  int sort_count = 0;
  for (int unsorted = 1; unsorted < size; unsorted++)
  {
    int current = unsorted;
    if (key == "atk")
    {
      while ((current > 0) && comp(getItem(current)->getAtk(), getItem(current - 1)->getAtk()))
      {
        swap(current, current - 1);
        current--;
        sort_count++;
      }
    }
    else if (key == "def")
    {
      while ((current > 0) && comp(getItem(current)->getDef(), getItem(current - 1)->getDef()))
      {
        swap(current, current - 1);
        current--;
        sort_count++;
      }
    }
  }
  return sort_count;
}

/**
  @param: comp can be std::less<int>{} (This is used for sorting in descending order.) 
  or std::greater<int>{} (This is used for sorting in ascending order.)
  @param: key can be "atk" (to sort by attack values) or "def" (to sort by defense values)
  @return: number of swaps used in Quick Sort
*/
template <typename Comparator>
int CardShop::quickSort(Comparator comp, const std::string &key)
{
  int size = getLength() - 1;
  int count = 0;
  quickSortRecursive(comp, key, 0, size, count);
  return count;
}

/**
  @param: comp can be std::less<int>{} (This is used for sorting in descending order.) 
  or std::greater<int>{} (This is used for sorting in ascending order.)
  @param: key can be "atk" (to sort by attack values) or "def" (to sort by defense values)
  @param: low index
  @param: high index
  @param: count
  @return: partition index
*/
template <typename Comparator>
int CardShop::partition(Comparator comp, const std::string &key, int low, int high, int &count)
{
  int i = low - 1;
  for (int j = low; j <= high; j++)
  {
    if (key == "atk")
    {
      if (comp(getItem(j)->getAtk(), getItem(high)->getAtk()))
      {
        i++;
        swap(i, j);
        count++;
      }
    }
    else if (key == "def")
    {
      if (comp(getItem(j)->getDef(), getItem(high)->getDef()))
      {
        i++;
        swap(i, j);
        count++;
      }
    }
  }
  swap(i + 1, high);
  count++;
  return i + 1;
}

/**
  @param: comp can be std::less<int>{} (This is used for sorting in descending order.) 
  or std::greater<int>{} (This is used for sorting in ascending order.)
  @param: key can be "atk" (to sort by attack values) or "def" (to sort by defense values)
  @param: low index
  @param: high index
  @param: count
  @post: implements the quicksort recursive alogorithm
*/
template <typename Comparator>
void CardShop::quickSortRecursive(Comparator comp, const std::string &key, int low, int high, int &count)
{
  if (low < high)
  {
    int pivot = partition(comp, key, low, high, count);
    quickSortRecursive(comp, key, low, pivot - 1, count);
    quickSortRecursive(comp, key, pivot + 1, high, count);
  }
}

// not implemented
template <typename Comparator>
int CardShop::mergeSort(Comparator comp, const std::string &key)
{
  return -1;
}