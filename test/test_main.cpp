#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"
extern "C" {
#include "main.h"
}

TEST_GROUP(HostnameTest){};

TEST(HostnameTest, GetHostnameWorks) {
    char buffer[256];
    int result = get_hostname(buffer, sizeof(buffer));
    CHECK_EQUAL(0, result);
}

int main(int argc, char** argv) {
    return CommandLineTestRunner::RunAllTests(argc, argv);
}
