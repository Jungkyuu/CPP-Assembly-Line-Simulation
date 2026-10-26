// Name: JungKyu Mok

#include "Utilities.h"
#include <iostream>
#include <stdexcept>
#include <string>

namespace seneca {

char Utilities::m_delimiter = ' '; // initialize static member

void Utilities::setFieldWidth(size_t newWidth) { m_widthField = newWidth; }

size_t Utilities::getFieldWidth() const { return m_widthField; }

std::string Utilities::extractToken(const std::string &str, size_t &next_pos,
                                    bool &more) {
  if (next_pos >= str.length()) {
    more = false;
    return "";
  }

  size_t end_pos = str.find(m_delimiter, next_pos);
  if (end_pos == std::string::npos) {
    end_pos = str.length();
  }

  if (end_pos == next_pos) {
    more = false;
    throw std::invalid_argument("Delimiter found at next_pos");
  }

  std::string token = str.substr(next_pos, end_pos - next_pos);
  next_pos = end_pos + 1;

  // Remove leading and trailing spaces
  token.erase(0, token.find_first_not_of(" \t"));
  token.erase(token.find_last_not_of(" \t") + 1);

  more = (next_pos < str.length());

  if (m_widthField < token.length()) {
    m_widthField = token.length();
  }

  return token;
}

void Utilities::setDelimiter(char newDelimiter) { m_delimiter = newDelimiter; }

char Utilities::getDelimiter() { return m_delimiter; }

} // namespace seneca
