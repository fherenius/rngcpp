//
// Created by root on 5/2/22.
//
#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>
#include <random>
#include <vector>
#include <fmt/core.h>
#include <fmt/os.h>

template<typename Type>
class Generator
{
    std::random_device                  d_device;
    std::mt19937_64                     d_generator;
    std::uniform_int_distribution<Type> d_distribution;

  public:
    Generator(Type min, Type max);

    auto gen();
};

template<typename Type>
inline Generator<Type>::Generator(Type min, Type max)
  :
  d_generator(d_device()),
  d_distribution(min, max)
{};

template<typename Type>
inline auto Generator<Type>::gen()
{
  return d_distribution(d_generator);
};

template<typename Type>
class TestSetGenerator
  :
    public Generator<Type>
{
    std::vector<Type> d_set;

  public:
    explicit TestSetGenerator(Type size, Type min, Type max);

    void generate();

    void save();

    Type at(Type idx);

    Type size() const;
};

template<typename Type>
TestSetGenerator<Type>::TestSetGenerator(Type size, Type min, Type max)
  :
  Generator<Type>(min, max),
  d_set(size)
{
}

template<typename Type>
Type TestSetGenerator<Type>::at(Type idx)
{
  return d_set[idx];
}

template<typename Type>
Type TestSetGenerator<Type>::size() const
{
  return d_set.size();
}

template<typename Type>
void TestSetGenerator<Type>::generate()
{
  auto first = begin(d_set);
  auto last  = end(d_set);
  while (first != last)
    *first++ = this->gen();
}

int main(int argc, char *argv[])
{
  if (argc != 5)
  {
    fmt::print("Please supply different command line options.");
    return 1;
  }

  std::string outName = argv[1];
  auto min = static_cast<size_t>(std::strtold(argv[2], nullptr));
  auto max = static_cast<size_t>(std::strtold(argv[3], nullptr));
  auto amount = static_cast<size_t>(std::strtold(argv[4], nullptr));

  /*
  size_t intMin = 1;
  size_t intMax = 2147483647;
  */

  TestSetGenerator<size_t> testset(amount, min, max);
  testset.generate();

  TestSetGenerator<size_t> testsetTwo(amount, min, max);
  testsetTwo.generate();

  auto out = fmt::output_file(outName.c_str());

  for (size_t idx = 0; idx != testset.size(); ++idx)
    out.print("{} {}\n", testset.at(idx), testsetTwo.at(idx));
}
