// BufferOverflow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Edited by Ryan A Peguero for CS-405 M2 Buffer Overflow assignment 

#include <iomanip>
#include <iostream>
#include <string>
#include <cstring>

int main()
{
  std::cout << "Buffer Overflow Example" << std::endl;5


  const std::string account_number = "CharlieBrown42";
  char user_input[20];

  // Read user input into a safe std::string first so we can check its length.
  // This preserves the required declaration order: account_number directly before user_input.
  std::cout << "Enter a value: ";
  std::string input;
  if (!std::getline(std::cin, input)) {
    // If getline fails, EOF or error, clear input to empty string.
    input.clear();
  }

  // Maximum number of characters that fit into user_input excluding the null terminator.
  const std::size_t max_len = sizeof(user_input) - 1;

  if (input.size() > max_len) {
    // Notify the user their input was too long and truncate to prevent overflow.
    std::cerr << "Error: Input too long (" << input.size()
              << " chars). Maximum allowed is " << max_len << " characters. Truncating input." << std::endl;
    // Copy only up to max_len characters and ensure null termination.
    std::memcpy(user_input, input.data(), max_len);
    user_input[max_len] = '\0';
  } else {
    // Safe to copy entire string including null terminator.
    std::memcpy(user_input, input.c_str(), input.size() + 1);
  }

  std::cout << "You entered: " << user_input << std::endl;
  std::cout << "Account Number = " << account_number << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
