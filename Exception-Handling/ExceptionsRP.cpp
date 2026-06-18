// Exceptions.cpp Edited by Ryan Peguero.
//

#include <iostream>
#include <stdexcept>   // Added for standard exception types like std::runtime_error
#include <exception>   // For std::exception base class

// Custom exception class derived from std::exception
class CustomBankException : public std::exception {
public:
    // Store a message explaining what went wrong
    explicit CustomBankException(const char* message) noexcept
        : msg_(message) {}

    // Return the stored message
    const char* what() const noexcept override {
        return msg_;
    }

private:
    const char* msg_;
};

bool do_even_more_custom_application_logic()
{
    // TODO: Throw any standard exception
    // Here we deliberately throw a standard runtime_error to simulate a failure
    throw std::runtime_error("Standard exception in do_even_more_custom_application_logic()");

    // This line will not execute because of the throw above, but is left
    // to show original intent of the function.
    std::cout << "Running Even More Custom Application Logic." << std::endl;

    return true;
}

void do_custom_application_logic()
{
    std::cout << "Running Custom Application Logic." << std::endl;

    // TODO: Wrap the call to do_even_more_custom_application_logic()
    // with an exception handler that catches std::exception, displays
    // a message and the exception.what(), then continues processing.
    try {
        if (do_even_more_custom_application_logic())
        {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
    }
    catch (const std::exception& ex) {
        // This catch handles any standard exception thrown in do_even_more_custom_application_logic()
        // and reports the error message to the user.
        std::cout << "[do_custom_application_logic] Caught std::exception: "
                  << ex.what() << std::endl;
    }

    // TODO: Throw a custom exception derived from std::exception
    // and catch it explicitly in main
    std::cout << "Leaving Custom Application Logic." << std::endl;

    // Throw a custom exception to be handled by main()
    throw CustomBankException("CustomBankException thrown from do_custom_application_logic()");
}

float divide(float num, float den)
{
    // TODO: Throw an exception to deal with divide by zero errors using
    // a standard C++ defined exception
    if (den == 0.0f) {
        // Using a standard C++ exception type to signal divide-by-zero
        throw std::runtime_error("Division by zero error in divide()");
    }

    return (num / den);
}

void do_division() noexcept
{
    // TODO: create an exception handler to capture ONLY the exception thrown
    // by divide.
    float numerator = 10.0f;
    float denominator = 0.0f;

    try {
        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
    }
    catch (const std::exception& ex) {
        // This block catches the exception thrown by divide() and displays the message.
        // Because this function is marked noexcept, we must not let exceptions escape.
        std::cout << "[do_division] Caught std::exception: "
                  << ex.what() << std::endl;
    }
}

int main()
{
    std::cout << "Exceptions Tests!" << std::endl;

    // TODO: Create exception handlers that catch (in this order):
    //  your custom exception
    //  std::exception
    //  uncaught exception
    // that wraps the whole main function, and displays a message to the console.
    try {
        do_division();
        do_custom_application_logic();
    }
    catch (const CustomBankException& ex) {
        // First, explicitly catch our custom exception type
        std::cout << "[main] Caught CustomBankException: "
                  << ex.what() << std::endl;
    }
    catch (const std::exception& ex) {
        // Then, catch any other standard exceptions
        std::cout << "[main] Caught std::exception: "
                  << ex.what() << std::endl;
    }
    catch (...) {
        // Finally, catch any other unhandled exception types
        std::cout << "[main] Caught unknown exception." << std::endl;
    }

    std::cout << "Exiting program normally after handling exceptions." << std::endl;
    return 0;
}
