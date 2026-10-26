// Name: JungKyu Mok

#include "LineManager.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace seneca {
// Constructor
LineManager::LineManager(const std::string &file,
                         const std::vector<Workstation *> &stations) {
  std::ifstream inputFile(file);
  if (!inputFile) {
    throw std::runtime_error("Unable to open file");
  }

  std::string line;
  while (std::getline(inputFile, line)) {
    std::istringstream record(line);
    std::string workstation, nextWorkstation;
    std::getline(record, workstation, '|');
    std::getline(record, nextWorkstation, '|');

    auto currentStation = std::find_if(
        stations.begin(), stations.end(), [&workstation](Workstation *ws) {
          return ws->getItemName() == workstation;
        });

    auto nextStation = std::find_if(
        stations.begin(), stations.end(), [&nextWorkstation](Workstation *ws) {
          return ws->getItemName() == nextWorkstation;
        });

    if (currentStation != stations.end()) {
      if (nextStation != stations.end()) {
        (*currentStation)->setNextStation(*nextStation);
      }
      m_activeLine.push_back(*currentStation);
    }
  }

  inputFile.close();

  // Determine the first station
  m_firstStation = *std::find_if(
      m_activeLine.begin(), m_activeLine.end(), [&stations](Workstation *ws) {
        return std::none_of(
            stations.begin(), stations.end(),
            [&ws](Workstation *ws2) { return ws2->getNextStation() == ws; });
      });

  m_cntCustomerOrder = g_pending.size();
}

// Reorder stations
void LineManager::reorderStations() {
  std::vector<Workstation *> orderedLine;
  Workstation *current = m_firstStation;
  while (current) {
    orderedLine.push_back(current);
    current = current->getNextStation();
  }
  m_activeLine = std::move(orderedLine);
}

// Run one iteration of the line manager
bool LineManager::run(std::ostream &os) {
  static size_t count = 0;

  bool result = false;

  os << "Line Manager Iteration: " << ++count << '\n';

  if (!g_pending.empty()) {
    *m_firstStation += std::move(g_pending.front());
    g_pending.pop_front();
  }

  for (auto &station : m_activeLine) {
    station->fill(os);
  }

  for (auto &station : m_activeLine) {
    station->attemptToMoveOrder();
  }

  for (auto &station : m_activeLine) {
    result = station->allOrdersFilled();
    if (result == false) {
      break;
    }
  }

  return result;
}

// Display all active stations
void LineManager::display(std::ostream &os) const {
  for (const auto &station : m_activeLine) {
    station->display(os);
  }
}
} // namespace seneca
