// Name: JungKyu Mok

#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H

#include "Station.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace seneca {

struct Item {
  std::string m_itemName;
  size_t m_serialNumber{0};
  bool m_isFilled{false};

  Item(const std::string &src) : m_itemName(src) {};
};

class CustomerOrder {
public:
  static size_t m_widthField;

  CustomerOrder();                          // Default constructor
  CustomerOrder(const std::string &record); // Custom constructor
  CustomerOrder(const CustomerOrder &other) {
    throw std::logic_error("Copy not allowed");
  }
  CustomerOrder &operator=(const CustomerOrder &other) {
    throw std::logic_error("Assignment not allowed");
  }
  CustomerOrder(CustomerOrder &&other) noexcept; // Move constructor
  CustomerOrder &
  operator=(CustomerOrder &&other) noexcept; // Move assignment operator
  ~CustomerOrder();                          // Destructor

  bool isOrderFilled() const;
  bool isItemFilled(const std::string &itemName) const;
  void fillItem(Station &station, std::ostream &os);
  void display(std::ostream &os) const;

private:
  std::string m_name;
  std::string m_product;
  std::vector<Item *> m_lstItem;
};
} // namespace seneca

#endif // SENECA_CUSTOMERORDER_H
