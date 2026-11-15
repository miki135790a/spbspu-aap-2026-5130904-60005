#include <iostream>
#include <cstring>
#include <cctype>
#include <new>

size_t latRmv(const char* src, char* dest)
{
  size_t j = 0;
  for (size_t i = 0; src[i] != '\0'; ++i) {
    if (!std::isalpha(static_cast< unsigned char >(src[i]))) {
      dest[j++] = src[i];
    }
  }
  dest[j] = '\0';
  return j;
}

size_t rmvVow(const char* src, char* dest)
{
  size_t j = 0;
  for (size_t i = 0; src[i] != '\0'; ++i) {
    const char lower = static_cast< char >(std::tolower(static_cast< unsigned char >(src[i])));
    if (lower != 'a' && lower != 'e' && lower != 'i' && lower != 'o' && lower != 'u') {
      dest[j++] = src[i];
    }
  }
  dest[j] = '\0';
  return j;
}

char* readLine(size_t* out_len)
{
  const size_t INITIAL_CAPACITY = 16;
  size_t capacity = INITIAL_CAPACITY;
  size_t length = 0;

  char* buffer = new (std::nothrow) char[capacity];
  if (!buffer) {
    return nullptr;
  }

  char c = 0;
  while (std::cin.get(c) && c != '\n') {
    if (length + 1 >= capacity) {
      capacity *= 2;
      char* const temp = new (std::nothrow) char[capacity];
      if (!temp) {
        delete[] buffer;
        return nullptr;
      }

      for (size_t i = 0; i < length; ++i) {
        temp[i] = buffer[i];
      }
      delete[] buffer;
      buffer = temp;
    }
    buffer[length++] = c;
  }
  buffer[length] = '\0';
  *out_len = length;
  return buffer;
}

int runLabWork()
{
  size_t length = 0;
  char* const input = readLine(&length);

  if (!input) {
    std::cerr << "Error: Failed to allocate memory." << std::endl;
    return 1;
  }

  if (length == 0) {
    delete[] input;
    std::cerr << "Error: Empty input." << std::endl;
    return 1;
  }

  char* const res1 = new (std::nothrow) char[length + 1];
  char* const res2 = new (std::nothrow) char[length + 1];

  if (!res1 || !res2) {
    delete[] input;
    delete[] res1;
    delete[] res2;
    std::cerr << "Error: Failed to allocate memory for results." << std::endl;
    return 1;
  }

  latRmv(input, res1);
  rmvVow(input, res2);

  std::cout << res1 << "\n";
  std::cout << res2 << "\n";

  delete[] input;
  delete[] res1;
  delete[] res2;

  return 0;
}

int main()
{
  return runLabWork();
}
