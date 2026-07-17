#include <iostream>
#include <stdexcept>
#include <string>

#include "sqlite3.h"

namespace {

void executeStatement(sqlite3* database, const char* sql) {
    char* errorMessage = nullptr;
    const int result = sqlite3_exec(database, sql, nullptr, nullptr, &errorMessage);

    if (result != SQLITE_OK) {
        const std::string message = errorMessage == nullptr
            ? "SQLite statement failed."
            : errorMessage;
        sqlite3_free(errorMessage);
        throw std::runtime_error(message);
    }
}

std::string findUserByName(sqlite3* database, const std::string& userInput) {
    const char* sql = "SELECT NAME FROM USERS WHERE NAME = ?1;";
    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(database, sql, -1, &statement, nullptr) != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(database));
    }

    if (sqlite3_bind_text(
            statement,
            1,
            userInput.c_str(),
            static_cast<int>(userInput.size()),
            SQLITE_TRANSIENT) != SQLITE_OK) {
        sqlite3_finalize(statement);
        throw std::runtime_error(sqlite3_errmsg(database));
    }

    std::string result = "No matching user";
    const int stepResult = sqlite3_step(statement);

    if (stepResult == SQLITE_ROW) {
        const unsigned char* value = sqlite3_column_text(statement, 0);
        result = value == nullptr
            ? "No matching user"
            : reinterpret_cast<const char*>(value);
    } else if (stepResult != SQLITE_DONE) {
        const std::string message = sqlite3_errmsg(database);
        sqlite3_finalize(statement);
        throw std::runtime_error(message);
    }

    sqlite3_finalize(statement);
    return result;
}

} // namespace

int main() {
    sqlite3* database = nullptr;

    if (sqlite3_open(":memory:", &database) != SQLITE_OK) {
        std::cerr << "Unable to open the SQLite database." << std::endl;
        return 1;
    }

    try {
        executeStatement(
            database,
            "CREATE TABLE USERS ("
            "ID INTEGER PRIMARY KEY,"
            "NAME TEXT NOT NULL UNIQUE"
            ");");

        executeStatement(
            database,
            "INSERT INTO USERS (NAME) VALUES "
            "('Fred'), ('Barney'), ('Wilma'), ('Betty');");

        const std::string normalInput = "Fred";
        const std::string injectionAttempt = "Fred' OR '1'='1";

        std::cout << "Normal input result: "
                  << findUserByName(database, normalInput)
                  << std::endl;

        std::cout << "Injection attempt result: "
                  << findUserByName(database, injectionAttempt)
                  << std::endl;

        std::cout << "The injection text is treated as data because it is bound "
                     "to a prepared statement rather than concatenated into SQL."
                  << std::endl;
    } catch (const std::exception& exception) {
        std::cerr << "Database error: " << exception.what() << std::endl;
        sqlite3_close(database);
        return 1;
    }

    sqlite3_close(database);
    return 0;
}
