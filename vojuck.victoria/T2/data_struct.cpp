#include <iostream>
#include <iomanip>

#include "data_struct.hpp"
#include "delimiter.hpp"
#include "inguard.hpp"

std::istream &vojuck::operator>>(std::istream &in, DataStruct &dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  DataStruct input;
  using sep = DelimiterIO;
  using label = LabelIO;
  using hex = HexULL;
  using str = StringIO;
  using chr = CharIO;
  size_t counter = 0;
  in >> sep{ '(' };
  for (size_t i = 0; i < 3; i++)
  {
    std::string key = "";
    in >> sep{ ':' };
    in >> key;

    if (key == "key2")
    {
      in >> chr{ input.key2 };
    }

    else if (key == "key1")
    {
      in >> hex{ input.key1 };
    }

    else if (key == "key3")
    {
      in >> str{ input.key3 };
    }
  }

  in >> sep{ ':' };
  in >> sep{ ')' };

  if (in)
  {
    dest = input;
  }
  return in;
}

std::ostream &vojuck::operator<<(std::ostream &out, const DataStruct &src)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  InGuard InGuard(out);
  out << "(";
  out << ":key1 '" << std::fixed << std::setprecision(1) << src.key1 << "'";
  out << ":key2 " << std::fixed << std::setprecision(1) << src.key2;
  out << ":key3 \"" << std::fixed << std::setprecision(1) << src.key3 << "\"";
  out << ":)";
  return out;
}



bool vojuck::operator<(const DataStruct &leftkey, const DataStruct &rightkey)
{
  if (leftkey.key1 == rightkey.key1)
  {
    if (leftkey.key2 == rightkey.key2)
    {
      return leftkey.key3.length() < rightkey.key3.length();
    }
    else
    {
      return leftkey.key2 < rightkey.key2;
    }
  }
  else
  {
    return leftkey.key1 < rightkey.key1;
  }
}
