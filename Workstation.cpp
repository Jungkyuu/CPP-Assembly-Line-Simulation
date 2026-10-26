// Name: JungKyu Mok

#include "Workstation.h"
#include <iostream>

namespace seneca {
// Global queues definition
std::deque<CustomerOrder> g_pending;
std::deque<CustomerOrder> g_completed;
std::deque<CustomerOrder> g_incomplete;

// Constructor
Workstation::Workstation(const std::string &item) : Station(item) {}

// Fill the order at the front of the queue
void Workstation::fill(std::ostream &os) {
  if (!m_orders.empty()) {
    m_orders.front().fillItem(*this, os);
  }
}

// Attempt to move the order to the next station
bool Workstation::attemptToMoveOrder() {
  if (!m_orders.empty()) {
    if (m_orders.front().isItemFilled(getItemName()) ||
        this->getQuantity() == 0) {
      if (m_pNextStation != nullptr) {
        *m_pNextStation += std::move(m_orders.front());
      } else {
        if (m_orders.front().isOrderFilled()) {
          g_completed.push_back(std::move(m_orders.front()));
        } else {
          g_incomplete.push_back(std::move(m_orders.front()));
        }
      }
      m_orders.pop_front();
      return true;
    }
  }
  return false;
}

// Set the next station
void Workstation::setNextStation(Workstation *station) {
  m_pNextStation = station;
}

// Get the next station
Workstation *Workstation::getNextStation() const { return m_pNextStation; }

// Display the station and the next station
void Workstation::display(std::ostream &os) const {
  os << getItemName() << " --> ";
  if (m_pNextStation) {
    os << m_pNextStation->getItemName();
  } else {
    os << "End of Line";
  }
  os << '\n';
}

bool Workstation::allOrdersFilled() { return m_orders.empty(); }

// Move a new order to the back of the queue
Workstation &Workstation::operator+=(CustomerOrder &&newOrder) {
  m_orders.push_back(std::move(newOrder));
  return *this;
}
} // namespace seneca
