// Name: JungKyu Mok

#ifndef SENECA_STATION_H
#define SENECA_STATION_H

#include <iostream>
#include <string>

namespace seneca {

class Station {
  int m_id;
  std::string m_itemName;
  std::string m_description;
  size_t m_serialNumber;
  size_t m_quantity;
  static size_t m_widthField; // maximum number of characters required to print
                              // the item name
  static int id_generator;    // variable used to generate IDs for new instances

public:
  Station(const std::string &record);

  const std::string &getItemName() const;
  size_t getNextSerialNumber();
  size_t getQuantity() const;
  void updateQuantity();
  void display(std::ostream &os, bool full) const;
};

} // namespace seneca

#endif // SENECA_STATION_H
