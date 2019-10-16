#include "peng/HelloWorld.h"

namespace peng {

    const char* LibTest::Hello(std::ostream& stream) {
        stream << "Hello from Puzzle Engine" << std::endl;

        return "Hello World";
    }

}
