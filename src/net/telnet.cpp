#include "net/telnet.h"

#include <arpa/telnet.h>

void rethinkmud::net::connections::telnet::input(std::vector<char> data)
{
    // TODO: Parse the input for telnet command sequence
    // TODO: Extract (remove) the command sequences as we process the input
    // TODO: For now we assume that all sequences are complete

    // TODO: After parsing and removing the telnet sequences,
    // TODO: the rest of the data is passed as a string to the
    // TODO: command interpreter
}
