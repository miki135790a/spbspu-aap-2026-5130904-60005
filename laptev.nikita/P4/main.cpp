#include <iostream>
#include <cstring>
#include <cctype>
#include <new>

size_t lat_rmv(const char* src, char* dest)
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

size_t rmv_vow(const char* src, char* dest)
{
  size_t j = 0;
  for (size_t i = 0; src[i] != '\0'; ++i) {
    char lower = std::tolower(static_cast< unsigned char >(src[i]));

    if (lower != 'a' && lower != 'e' && lower != 'i' && lower != 'o' && lower != 'u') {
      dest[j++] = src[i];
    }
  }
  dest[j] = '\0';
  return j;
}

int main()
{
  size_t capacity = 16;
  size_t length = 0;

  char* input = new (std::nothrow) char[capacity];
  if (!input) {
    std::cerr << "Error: Memory allocation failed." << std::endl;
    return 1;
  }

  char c;

  while (std::cin.get(c) && c != '\n') {
    if (length + 1 >= capacity) {
      capacity *= 2;
      char* temp = new (std::nothrow) char[capacity];
      if (!temp) {
        delete[] input;
        std::cerr << "Error: Memory allocation failed." << std::endl;
        return 1;
      }
      std::strcpy(temp, input);
      delete[] input;
      input = temp;
    }
    input[length++] = c;
  }
  input[length] = '\0';

  char* res1 = new (std::nothrow) char[length + 1];
  char* res2 = new (std::nothrow) char[length + 1];
  if (!res1 || !res2) {
    delete[] input;
    delete[] res1;
    delete[] res2;
    std::cerr << "Error: Memory allocation failed." << std::endl;
    return 1;
  }

  lat_rmv(input, res1);
  rmv_vow(input, res2);

  std::cout << res1 << "\n";
  std::cout << res2 << "\n";

  delete[] input;
  delete[] res1;
  delete[] res2;

  return 0;
}
