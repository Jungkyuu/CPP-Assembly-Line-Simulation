// Name: JungKyu Mok

#include "Station.h"
#include "Utilities.h"
#include <iomanip>
#include <iostream>

namespace seneca {

size_t Station::m_widthField = 0;
int Station::id_generator = 0;

Station::Station(const std::string &record) : m_id(++id_generator) {
  Utilities util;
  size_t next_pos = 0;
  bool more = true;

  m_itemName = util.extractToken(record, next_pos, more);
  m_serialNumber = std::stoul(util.extractToken(record, next_pos, more));
  m_quantity = std::stoul(util.extractToken(record, next_pos, more));
  m_description = util.extractToken(record, next_pos, more);

  // Update m_widthField based on the length of the item name
  if (m_widthField < m_itemName.length()) {
    m_widthField = m_itemName.length();
  }
}

const std::string &Station::getItemName() const { return m_itemName; }

size_t Station::getNextSerialNumber() { return m_serialNumber++; }

size_t Station::getQuantity() const { return m_quantity; }

void Station::updateQuantity() {
  if (m_quantity > 0) {
    --m_quantity;
  }
}

void Station::display(std::ostream &os, bool full) const {
  os << std::right << std::setw(3) << std::setfill('0') << m_id << " | "
     << std::left << std::setw(m_widthField) << std::setfill(' ') << m_itemName
     << " | " << std::right << std::setw(6) << std::setfill('0')
     << m_serialNumber << " | ";

  if (full) {
    os << std::setw(4) << std::setfill(' ') << m_quantity << " | "
       << m_description;
  }
  os << std::endl;
}

} // namespace seneca
