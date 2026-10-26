// Name: JungKyu Mok

#include "CustomerOrder.h"
#include "Utilities.h"
#include <iomanip>
#include <iostream>
#include <unordered_set>

namespace seneca {

size_t CustomerOrder::m_widthField = 0;

// Default constructor
CustomerOrder::CustomerOrder() : m_name(""), m_product("") {}

// Custom constructor that parses the record
CustomerOrder::CustomerOrder(const std::string &record) {
  Utilities util;
  size_t next_pos = 0;
  bool more = true;
  m_name = util.extractToken(record, next_pos, more);
  m_product = util.extractToken(record, next_pos, more);

  while (more) {
    m_lstItem.push_back(new Item(util.extractToken(record, next_pos, more)));
  }

  // Update width field for display purposes
  if (util.getFieldWidth() > m_widthField) {
    m_widthField = util.getFieldWidth();
  }
}

// Move constructor
CustomerOrder::CustomerOrder(CustomerOrder &&other) noexcept {
  *this = std::move(other);
}

// Move assignment operator
CustomerOrder &CustomerOrder::operator=(CustomerOrder &&other) noexcept {
  if (this != &other) {
    // Clean up current resources
    for (auto &item : m_lstItem) {
      delete item;
    }
    m_lstItem.clear();

    // Transfer resources from 'other' to 'this'
    m_name = std::move(other.m_name);
    m_product = std::move(other.m_product);
    m_lstItem = std::move(other.m_lstItem);

    // Leave 'other' in a destructible state
    other.m_lstItem.clear();
  }
  return *this;
}

// Destructor
CustomerOrder::~CustomerOrder() {
  for (auto item : m_lstItem) {
    delete item;
  }
  m_lstItem.clear();
}

bool CustomerOrder::isOrderFilled() const {
  for (const Item *item : m_lstItem) {
    if (!item->m_isFilled)
      return false;
  }
  return true;
}

bool CustomerOrder::isItemFilled(const std::string &itemName) const {
  for (const Item *item : m_lstItem) {
    if (item->m_itemName == itemName && !item->m_isFilled)
      return false;
  }
  return true;
}

void CustomerOrder::fillItem(Station &station, std::ostream &os) {
  for (Item *item : m_lstItem) {
    if (item->m_itemName == station.getItemName() && !item->m_isFilled) {
      if (station.getQuantity() > 0) {
        item->m_serialNumber = station.getNextSerialNumber();
        item->m_isFilled = true;
        station.updateQuantity();
        os << "    Filled " << m_name << ", " << m_product << " ["
           << item->m_itemName << "]" << std::endl;
        break;
      } else {
        os << "    Unable to fill " << m_name << ", " << m_product << " ["
           << item->m_itemName << "]" << std::endl;
      }
    }
  }
}

void CustomerOrder::display(std::ostream &os) const {
  os << m_name << " - " << m_product << std::endl;
  for (const Item *item : m_lstItem) {
    os << "[" << std::setw(6) << std::right << std::setfill('0')
       << item->m_serialNumber << "] " << std::setfill(' ') << std::left
       << std::setw(m_widthField) << item->m_itemName << " - "
       << (item->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
  }
}

} // namespace seneca
