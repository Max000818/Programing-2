#include "test_runner.h"
#include <sstream>
#include <string>

using namespace std;

class Logger {
public:
    explicit Logger(ostream& output_stream) : os(output_stream) {}

    void SetLogLine(bool value) { log_line = value; }
    void SetLogFile(bool value) { log_file = value; }

    void Log(const string& message) {
        if (log_file && log_line) {
            os << current_file << ":" << current_line << " " << message << endl;
        } else if (log_file) {
            os << current_file << " " << message << endl;
        } else if (log_line) {
            os << "Line " << current_line << " " << message << endl;
        } else {
            os << message << endl;
        }
    }

    void SetFile(const string& file) { current_file = file; }
    void SetLine(int line) { current_line = line; }

private:
    ostream& os;
    bool log_line = false;
    bool log_file = false;
    string current_file;
    int current_line = 0;
};

#define LOG(logger, message) \
    logger.SetFile(__FILE__); \
    logger.SetLine(__LINE__); \
    logger.Log(message);

void TestLog() {
#line 1 "Logger.cpp"

    ostringstream logs;
    Logger l(logs);
    LOG(l, "hello");

    l.SetLogFile(true);
    LOG(l, "hello");

    l.SetLogLine(true);
    LOG(l, "hello");

    l.SetLogFile(false);
    LOG(l, "hello");

    string expected = "hello\n";
    expected += "Logger.cpp hello\n";
    expected += "Logger.cpp:10 hello\n";
    expected += "Line 13 hello\n";
    ASSERT_EQUAL(logs.str(), expected);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestLog);
}