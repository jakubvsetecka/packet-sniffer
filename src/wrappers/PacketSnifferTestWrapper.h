#include "PacketSniffer.h"

class PacketSnifferTestWrapper : public PacketSniffer {
  public:
    // Use constructor of the base class
    using PacketSniffer::PacketSniffer;

    // Publicly expose createFilter for testing
    std::string testCreateFilter() {
        return createFilter();
    }
};
