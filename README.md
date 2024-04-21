# IPK-network-sniffer

> **Note:** The production of this file was accelerated by [chatGPT4](https://chat.openai.com/)

## Table of Contents
- [IPK-network-sniffer](#ipk-network-sniffer)
  - [Table of Contents](#table-of-contents)
  - [Theory](#theory)
    - [OSI Model](#osi-model)
      - [Encapsulation](#encapsulation)
      - [Protocol Locations in the OSI Model](#protocol-locations-in-the-osi-model)
    - [IP Extensions and Options](#ip-extensions-and-options)
    - [Link Types](#link-types)
  - [Design Overview](#design-overview)
    - [Structure Overview](#structure-overview)
      - [Protocol Class Hierarchy](#protocol-class-hierarchy)
      - [IPCAPWrapper and its Implementations](#ipcapwrapper-and-its-implementations)
      - [Comprehensive Class Diagram](#comprehensive-class-diagram)
    - [System Operation Workflow](#system-operation-workflow)
    - [Use of Threading](#use-of-threading)
  - [Implementation](#implementation)
      - [`ArgumentParser`](#argumentparser)
      - [`PacketData`](#packetdata)
      - [`PacketHandler`](#packethandler)
      - [`PacketSniffer`](#packetsniffer)
      - [`ParsingContext`](#parsingcontext)
      - [`PortType`](#porttype)
      - [`ProtoType`](#prototype)
      - [`IPAddress`](#ipaddress)
      - [`Protocol`](#protocol)
      - [`ProtocolFactory`](#protocolfactory)
      - [`SignalHandler`](#signalhandler)
      - [`ThreadSafeQueue`](#threadsafequeue)
      - [`ARPProtocol`](#arpprotocol)
      - [`ICMP4Protocol`](#icmp4protocol)
      - [`ICMP6Protocol`](#icmp6protocol)
      - [`IGMPProtocol`](#igmpprotocol)
      - [`IMGPProtocol`](#imgpprotocol)
      - [`IPv4Protocol`](#ipv4protocol)
      - [`IPv6Protocol`](#ipv6protocol)
      - [`MLDProtocol`](#mldprotocol)
      - [`NDPProtocol`](#ndpprotocol)
      - [`TCPProtocol`](#tcpprotocol)
      - [`UDPProtocol`](#udpprotocol)
      - [`IPCAPWrapper`](#ipcapwrapper)
      - [`MockIPCAPWrapper`](#mockipcapwrapper)
      - [`RealIPCAPWrapper`](#realipcapwrapper)
  - [Testing](#testing)
    - [Tests Implemented by Me](#tests-implemented-by-me)
      - [Test Case 1: Interface Listing](#test-case-1-interface-listing)
      - [Test Case 2: Default Single Packet Capture](#test-case-2-default-single-packet-capture)
      - [Test Case 3: TCP Filtering](#test-case-3-tcp-filtering)
      - [Test Case 4: UDP Filtering by Port](#test-case-4-udp-filtering-by-port)
      - [Test Case 5: Combined TCP and UDP Port Filtering](#test-case-5-combined-tcp-and-udp-port-filtering)
      - [Test Case 6: ICMPv4 and ICMPv6 Filtering](#test-case-6-icmpv4-and-icmpv6-filtering)
      - [Test Case 7: ARP and NDP Display](#test-case-7-arp-and-ndp-display)
      - [Test Case 8: Multiple Packet Capture](#test-case-8-multiple-packet-capture)
      - [Test Case 9: Protocol Exclusivity Test](#test-case-9-protocol-exclusivity-test)
    - [Hardware specifications](#hardware-specifications)
      - [Processor](#processor)
      - [General Info](#general-info)
      - [Features](#features)
      - [Vulnerabilities](#vulnerabilities)
      - [Performance](#performance)
      - [Architecture](#architecture)
    - [Software specifications](#software-specifications)
  - [Bibliography](#bibliography)
    - [Books](#books)
    - [Standards and Specifications](#standards-and-specifications)
    - [Online Resources](#online-resources)

## Theory

### OSI Model
The Open Systems Interconnection (OSI) model is a conceptual framework used to understand network interactions in seven layers. Each layer serves a specific function and communicates with the layers directly above and below it:

1. Physical Layer: Deals with the physical aspects of data transmission, including cable or radio signal types.
2. Data Link Layer: Responsible for node-to-node data transfer and error correction from the physical layer.
3. Network Layer: Handles routing of data packets across networks.
4. Transport Layer: Provides end-to-end communication services for applications.
5. Session Layer: Manages sessions between applications.
6. Presentation Layer: Translates data between the application layer and the network.
7. Application Layer: Provides networking services to applications.

#### Encapsulation
Encapsulation is a process in the Data Link, Network, and Transport layers where data from a higher layer is wrapped with necessary protocol information before passing it down to a lower layer. This involves adding headers (and sometimes trailers) to the data. For example, in an Ethernet-based network, an IP packet (from the Network layer) is encapsulated within an Ethernet frame at the Data Link layer.

#### Protocol Locations in the OSI Model
```
+-----------------+---------------------------------------------------+
| OSI Layer       | Protocols                                         |
+-----------------+---------------------------------------------------+
| 7. Application  | -                                                 |
| 6. Presentation | -                                                 |
| 5. Session      | -                                                 |
| 4. Transport    | TCP, UDP                                          |
| 3. Network      | IP (IPv4, IPv6), ICMP                             |
| 2. Data Link    | Ethernet, ARP                                     |
| 1. Physical     | - (Ethernet standards also define physical layer  |
|                 | characteristics, but specific physical layer      |
|                 | protocols like DSL, Fiber, etc., are not listed)  |
+-----------------+---------------------------------------------------+
```
- TCP/UDP (Transport Layer): These protocols are responsible for end-to-end communication. TCP provides reliable transmission with flow control and error handling, while UDP offers a connectionless service for applications that require speed over reliability.
- ICMP4/ICMP6 (Network Layer): Internet Control Message Protocol is used for sending error messages and operational information indicating, for example, that a requested service is not available or that a host or router could not be reached.
- ARP/NDP (Data Link Layer): Address Resolution Protocol (ARP) and Neighbor Discovery Protocol (NDP) are used for mapping IP addresses to physical machine (MAC) addresses. ARP is used with IPv4 and NDP is part of the IPv6 specification.
- IGMP/MLD (Network Layer): Internet Group Management Protocol (IGMP) and Multicast Listener Discovery (MLD) are used to manage group membership for multicast traffic. IGMP is used with IPv4, while MLD is used with IPv6.
- IPv4/IPv6 (Network Layer): Internet Protocol versions 4 and 6 are the primary protocols for routing traffic across the Internet.

### IP Extensions and Options
IP headers can be extended with options to provide additional capabilities. Common options for IPv4 include security options (like the IPsec suite), record route (which stores the route of a packet), and timestamp options (which can be used for round-trip time measurements). IPv6 has a more streamlined approach with extension headers, which facilitate features like routing (alternate routing), fragmentation, and authentication.

### Link Types
In network packet capturing, the link type specifies the link protocol's type. Since this project uses only LINKTYPE_ETHERNET, the following applies:

- Ethernet: The most common link type for local area networks (LANs). Ethernet frames encapsulate various network layer protocols such as IP packets and have a well-defined format including source and destination MAC addresses, a type field (to indicate the network layer protocol), and a frame check sequence for error detection.

## Design Overview

This project is designed to capture and analyze network packets efficiently using the `libpcap` library. The system architecture utilizes object-oriented programming principles to modularize the process into clear, manageable components such as packet capturing, packet handling, and protocol processing.

### Structure Overview

#### Protocol Class Hierarchy

The diagram in Figure 1 illustrates the Protocol class and its derived classes, demonstrating a clear example of generalization and specialization in object-oriented design. The Protocol class serves as an abstract base, defining a common interface for all specialized protocol handlers such as `TCPProtocol`, `UDPProtocol`, and `ICMP4Protocol`. This modular and scalable design allows for easy extension as new protocols need to be supported, enhancing the maintainability and adaptability of the packet processing framework.

![Protocols](imgs/protocol.png)
*Figure 1: Part of the Class Diagram showing Protocol and its derived classes.*

#### IPCAPWrapper and its Implementations

Figure 2 shows the `IPCAPWrapper` class and its concrete implementations: `MockIPCAPWrapper` and `RealIPCAPWrapper`. The `IPCAPWrapper` abstracts library-specific functions of `libpcap`, a standard packet capture library in Unix environments, to promote code maintainability and testing. `RealIPCAPWrapper` uses real `libpcap` calls for live environments, while `MockIPCAPWrapper` is used within Google Test frameworks for simulating pcap functionalities without accessing real network hardware. This setup underscores the importance of a maintainable codebase that can be robustly tested.

![Wrappers](imgs/wrappers.png)
*Figure 2: Part of the Class Diagram showing the IPCAPWrapper and its derived classes.*

#### Comprehensive Class Diagram

The diagram in Figure 3 provides a complete overview of the system's architecture. The `ProtocolFactory` is central for creating appropriate protocol handlers dynamically based on detected packet types. `PacketSniffer` is responsible for opening a network session, setting up filters, and sniffing packets. `PacketHandler`, in conjunction with ThreadSafeQueue, manages packet processing; `PacketSniffer` places packets into the queue, and `PacketHandler` processes them as they arrive. This architecture effectively decouples packet capture from packet processing, facilitating efficient data handling and processing through multithreading.

![Class Diagram](imgs/class.png)
*Figure 3: Class Diagram showing the relationships and structure of the classes within the system.*
> **Note:** `ArgumentParser` was omitted from the diagram for brevity, as it is a standalone class.

### System Operation Workflow

The flow diagram in Figure 4 illustrates the process flow from the start of the application to the processing of packets. It highlights the dynamic interactions between components such as the `ArgumentParser`, `PacketSniffer`, `ThreadSafeQueue`, and `PacketHandler`.

![Flow Diagram](imgs/flow.png)

*Figure 4: Flow Diagram depicting the operational flow from packet capture to packet processing.*

### Use of Threading

To combat potential buffer overflow issues with the network card and to manage the high throughput of network data, the application employs a multithreading approach with a thread-safe queue. This design choice is crucial for the following reasons:

- **Asynchronous Processing**: The `PacketSniffer` captures packets and enqueues them into a `ThreadSafeQueue`. This decouples the packet capture from the packet processing, allowing both to occur simultaneously without waiting for one to complete before the other starts.

- **Buffer Overflow Prevention**: By immediately moving captured packets into a queue, we mitigate the risk of losing packets that could occur due to buffer overflow in the network card's buffer, especially under high traffic conditions.

- **Enhanced Performance**: Utilizing separate threads for capturing and processing packets takes advantage of multi-core processors, improving the application's overall performance and responsiveness.

This threaded approach ensures that the system can handle large volumes of network data efficiently and reliably, making it suitable for both development and production environments for network analysis and troubleshooting.

## Implementation

#### `ArgumentParser`

-   **Purpose**: Parses command-line arguments to configure the packet sniffer's settings.
-   **Key Functionalities**:
    -   Parses user inputs to extract interface names, port numbers, and protocol filters.
    -   Provides a method to display configuration settings and usage instructions.

#### `PacketData`

-   **Purpose**: Represents the data structure for storing packet information after capture.
-   **Key Functionalities**:
    -   Stores both raw packet data and metadata such as timestamps and captured lengths.
    -   Provides accessors for retrieving packet specifics like length and timestamps.

#### `PacketHandler`

-   **Purpose**: Manages the processing of packets from a capture queue using protocol handlers.
-   **Key Functionalities**:
    -   Runs a processing loop that dequeues packets and applies protocol-specific parsing.
    -   Can be stopped gracefully to manage packet processing shutdown.

#### `PacketSniffer`

-   **Purpose**: Handles the setup and execution of packet captures using `pcap`.
-   **Key Functionalities**:
    -   Configures and initiates packet capture on specified interfaces with necessary filters.
    -   Interacts with `IPCAPWrapper` to abstract pcap functionalities like opening a device and setting filters.

#### `ParsingContext`

-   **Purpose**: Stores contextual information for a packet being processed to assist protocol handlers.
-   **Key Functionalities**:
    -   Manages and validates the setting of various packet attributes like source/destination IPs, ports, and MAC addresses.
    -   Provides formatted outputs for debugging and logging packet information.

#### `PortType`

-   **Purpose**: Enumerates types of port settings (source, destination, any) for filtering purposes.
-   **Key Functionalities**:
    -   Defines port filtering options used in constructing capture filters.

#### `ProtoType`

-   **Purpose**: Enumerates the protocol types to standardize protocol identification across handlers.
-   **Key Functionalities**:
    -   Provides a consistent set of identifiers for network protocols like TCP, UDP, and ICMP.

#### `IPAddress`

-   **Purpose**: Encapsulates IPv4 and IPv6 address handling within the network packets.
-   **Key Functionalities**:
    -   Provides methods to convert IP addresses from binary to human-readable form.
    -   Supports both IPv4 and IPv6 address transformations.

#### `Protocol`

-   **Purpose**: Abstract base class for protocol-specific handlers that process packets.
-   **Key Functionalities**:
    -   Defines a common interface for all protocol handlers to implement packet processing methods.

#### `ProtocolFactory`

-   **Purpose**: Implements the Factory Design Pattern to instantiate protocol handlers based on packet data.
-   **Key Functionalities**:
    -   Dynamically creates instances of derived `Protocol` classes based on the protocol type detected in the packet.

#### `SignalHandler`

-   **Purpose**: Manages system signals for graceful shutdown and logging.
-   **Key Functionalities**:
    -   Intercepts and processes system signals to handle events like application termination.

#### `ThreadSafeQueue`

-   **Purpose**: Provides a thread-safe queue implementation for storing and accessing packets across multiple threads.
-   **Key Functionalities**:
    -   Enforces exclusive access to the queue's front and back to prevent race conditions.

#### `ARPProtocol`

-   **Purpose**: Handles parsing and processing of ARP packets.
-   **Key Functionalities**:
Extracts ARP-specific information such as sender and target IP addresses.

#### `ICMP4Protocol`

-   **Purpose**: Manages the parsing of ICMPv4 packets.
-   **Key Functionalities**:
    -   Sets protocol type in the `ParsingContext`.

#### `ICMP6Protocol`

-   **Purpose**: Manages the parsing of ICMPv6 packets.
-   **Key Functionalities**:
    -   Sets protocol type in the `ParsingContext`.

#### `IGMPProtocol`

-   **Purpose**: Parses Internet Group Management Protocol packets for managing IPv4 multicast groups.
-   **Key Functionalities**:
    -   Sets protocol type in the `ParsingContext`.

#### `IMGPProtocol`

-   **Purpose**: Manages parsing of IMGP messages, a hypothetical or specialized protocol.
-   **Key Functionalities**:
    -   Sets protocol type in the `ParsingContext`.

#### `IPv4Protocol`

-   **Purpose**: Specializes in parsing IPv4 packets including header information and encapsulated payloads.
-   **Key Functionalities**:
    -   Extracts source and destination IP addresses and protocol types from IPv4 headers.
    -   Calls the `ProtocolFactory` to create protocol handlers for encapsulated packets.
    -   Calls processing methods on the created protocol handlers.

#### `IPv6Protocol`

-   **Purpose**: Handles the parsing of IPv6 packets, addressing the complexities of IPv6 including extension headers.
-   **Key Functionalities**:
    -   Manages extended addressing.
    -   Calls the `ProtocolFactory` to create protocol handlers for encapsulated packets.
    -   Calls processing methods on the created protocol handlers.

#### `MLDProtocol`

-   **Purpose**: Manages parsing for Multicast Listener Discovery messages used in IPv6.
-   **Key Functionalities**:
    -   Sets protocol type in the `ParsingContext`.

#### `NDPProtocol`

-   **Purpose**: Parses Neighbor Discovery Protocol packets for IPv6 address resolution and management.
-   **Key Functionalities**:
    -   Sets protocol type in the `ParsingContext`.

#### `TCPProtocol`

-   **Purpose**: Provides parsing and processing of TCP packets.
-   **Key Functionalities**:
    -   Extracts TCP headers including port numbers.

#### `UDPProtocol`

-   **Purpose**: Specializes in parsing UDP packets, which are used for connectionless communication.
-   **Key Functionalities**:
    -   Extracts source and destination ports.

#### `IPCAPWrapper`

-   **Purpose**: Defines an abstract interface to the `pcap` library functions to enable mock implementations and real interactions.
-   **Key Functionalities**:
    -   Abstracts `pcap` operations such as opening a capture device and compiling and setting filters.

#### `MockIPCAPWrapper`

-   **Purpose**: Provides a mock implementation of IPCAPWrapper for testing without actual network packet captures.
-   **Key Functionalities**:
    -   Simulates `pcap` functions allowing for comprehensive testing of network analysis logic in isolation.

#### `RealIPCAPWrapper`

-   **Purpose**: Implements the `IPCAPWrapper` interface with actual `libpcap` function calls for live network packet capturing.
-   **Key Functionalities**:
    -   Enables real packet captures with filter application, useful in deployed environments for traffic analysis.


## Testing

Testing was conducted using a robust suite from [IPK Sniffer Tests](https://git.fit.vutbr.cz/xjerab28/IPK-Sniffer-Tests), complemented by additional tests I designed to thoroughly evaluate specified functionalities and ensure reliable operation under various scenarios. Below I mention some of the tests I conducted:

### Tests Implemented by Me

#### Test Case 1: Interface Listing
-   **Objective**: Validate that the program lists all active interfaces correctly when no interface is specified.
-   **Steps**: Run ./ipk-sniffer without any arguments.
-   **Expected Result**: The program prints a list of all active network interfaces.
```
Running Test: testInterfaceListing

Sniffer started with arguments: []
Asserting that 'lo' is in sniffed packet
👍
Asserting that 'eth0' is in sniffed packet
👍
```

#### Test Case 2: Default Single Packet Capture
-   **Objective**: Verify that the program captures and displays exactly one packet if the -n parameter is not specified.
-   **Steps**: Run ./ipk-sniffer -i lo.
-   **Expected Result**: The program captures and displays exactly one packet from the lo interface.
```
Running Test: testSinglePacketCapture

Sniffer started with arguments: ['-i', 'lo']
Asserting that 1 == 1
👍
.Sniffer started with arguments: ['-i', 'lo', '--tcp', '-p', '4567']
Asserting that 'src IP: 127.0.0.1' is in sniffed packet
👍
Asserting that 'dst port: 4567' is in sniffed packet
👍
```

#### Test Case 3: TCP Filtering
-   **Objective**: Test TCP packet filtering functionality.
-   **Steps**: Run ./ipk-sniffer --interface lo --tcp.
-   **Expected Result**: Only TCP packets are captured and displayed from the lo interface.

```
Running Test: testTcp2

Sniffer started with arguments: ['-i', 'lo', '--tcp']
Asserting that 'protocol: TCP' is in sniffed packet
👍
```

#### Test Case 4: UDP Filtering by Port
-   **Objective**: Ensure that UDP packet filtering by source or destination port works correctly.
-   **Steps**: Run ./ipk-sniffer -i lo -u --port-source 53.
-   **Expected Result**: Only UDP packets with source port 53 are captured and displayed.
```
Running Test: testUdp2

Sniffer started with arguments: ['-i', 'lo', '--udp']
Asserting that 'protocol: UDP' is in sniffed packet
👍
```

#### Test Case 5: Combined TCP and UDP Port Filtering
-   **Objective**: Test combined TCP and UDP packet capture with specific port filtering.
-   **Steps**: Run ./ipk-sniffer -i lo --tcp --udp --port-destination 80.
-   **Expected Result**: Both TCP and UDP packets with destination port 80 are captured and displayed.

#### Test Case 6: ICMPv4 and ICMPv6 Filtering
-   **Objective**: Validate filtering for ICMPv4 and ICMPv6 packets.
-   **Steps**: Run ./ipk-sniffer -i lo --icmp4 --icmp6.
-   **Expected Result**: Only ICMPv4 and ICMPv6 packets are captured and displayed from the lo interface.
```
Running Test: testIcmp

Sniffer started with arguments: ['-i', 'lo', '--icmp4', '--icmp6', '-n', '2']
Asserting that 'src IP: ::1' is in sniffed packet
👍
Asserting that 2 == 2
👍
Asserting that 'protocol: ICMP4' is in sniffed packet
👍
Asserting that 'protocol: ICMP6' is in sniffed packet
👍
.Sniffer started with arguments: ['-i', 'lo', '--icmp4']
Asserting that 'src IP: 127.0.0.1' is in sniffed packet
👍
Asserting that 'frame length: 42' is in sniffed packet
👍
.Sniffer started with arguments: ['-i', 'lo', '--icmp6']
Asserting that 'src IP: ::1' is in sniffed packet
👍
Asserting that 'frame length: 62' is in sniffed packet
👍
.Sniffer started with arguments: ['-i', 'lo', '--icmp6']
Asserting that 'src IP: ::1' is in sniffed packet
👍
Asserting that 'frame length: 73' is in sniffed packet
👍
```

#### Test Case 7: ARP and NDP Display
-   **Objective**: Check that ARP and NDP frames are captured and displayed when specified.
-   **Steps**: Run ./ipk-sniffer -i lo --arp --ndp.
-   **Expected Result**: Only ARP and NDP packets are captured and displayed.
```
Running Test: testArpNdp

Sniffer started with arguments: ['-i', 'lo', '--arp', '--ndp', '-n', '2']
Asserting that 'src MAC: 00:00:00:00:00:00' is in sniffed packet
👍
Asserting that 2 == 2
👍
Asserting that 'protocol: ARP' is in sniffed packet
👍
Asserting that 'protocol: ICMP6' is in sniffed packet
👍
```

#### Test Case 8: Multiple Packet Capture
-   **Objective**: Confirm that the program can capture a specified number of packets.
-   **Steps**: Run ./ipk-sniffer -i lo -n 10.
-   **Expected Result**: Exactly 10 packets are captured and displayed from the lo interface.
```
Running Test: testMultiplePacketCapture

Sniffer started with arguments: ['-i', 'lo', '-n', '10']
Asserting that 10 == 10
👍
.Sniffer started with arguments: ['-i', 'lo', '--ndp']
Asserting that 'src IP: ::1' is in sniffed packet
👍
Asserting that 'frame length: 78' is in sniffed packet
👍
.Sniffer started with arguments: ['-i', 'lo', '--ndp']
Asserting that 'src IP: ::1' is in sniffed packet
👍
Asserting that 'frame length: 62' is in sniffed packet
👍
```

#### Test Case 9: Protocol Exclusivity Test
-   **Objective**: Ensure that specifying multiple protocols does not capture unspecified protocols.
-   **Steps**: Run ./ipk-sniffer -i lo --tcp --udp --icmp4.
-   **Expected Result**: No ARP, NDP, IGMP, or MLD packets are displayed, only TCP, UDP, and ICMPv4 packets.
```
Running Test: testProtocolExclusivity

Sniffer started with arguments: ['-i', 'lo', '--tcp', '--udp', '--icmp4', '-n', '7']
Asserting that 'protocol: ARP' is NOT in sniffed packet
👍
Asserting that 'protocol: NDP' is NOT in sniffed packet
👍
Asserting that 'protocol: IGMP' is NOT in sniffed packet
👍
Asserting that 'protocol: ICMPv6' is NOT in sniffed packet
👍
Asserting that 'protocol: MLD' is NOT in sniffed packet
👍
Asserting that 3 == 3
👍
```

### Hardware specifications

#### Processor

-   **Model**: Intel(R) Core(TM) i5-6300HQ CPU @ 2.30GHz
-   **CPU MHz**: 2304.000
-   **Cache Size**: 6144 KB
-   **Cores**: 4

#### General Info

-   **Vendor ID**: GenuineIntel
-   **CPU Family**: 6
-   **Model Number**: 94
-   **Stepping**: 3
-   **Microcode Version**: 0xffffffff

#### Features

-   **Virtualization (Hypervisor)**: Yes
-   **Security Features**: NX, IBRS, IBPB, STIBP
-   **Performance Boosting**: HT (Hyper-Threading), Turbo Boost
-   **Additional Flags**: SSE4_1, SSE4_2, AVX2

#### Vulnerabilities

#### Performance

-   **BogoMIPS**: 4608.00

#### Architecture

-   **Physical Address Sizes**: 39 bits
-   **Virtual Address Sizes**: 48 bits

_Note: This configuration represents one of the CPU cores as seen by the system. All cores have similar configurations._

### Software specifications

-   **Operating System**: Ubuntu 22.04.4 LTS
-   **Kernel Version**: 5.15.146.1-microsoft-standard-WSL2
-   **Compiler**: gcc (GCC) 12.3.0
-   **Google Test Version**: 1.14.0

## Bibliography

### Books

1. **"Computer Networking: A Top-Down Approach"** by James F. Kurose and Keith W. Ross
   - Provides comprehensive insights into the OSI model, encapsulation processes, and detailed protocol explanations.

2. **"Computer Networks"** by Andrew S. Tanenbaum and David J. Wetherall
   - A classic text that explores network architectures and the behavior of protocols at various OSI layers.

### Standards and Specifications

3. **[RFC 791 - Internet Protocol](https://tools.ietf.org/html/rfc791)**
   - Foundational document for IPv4 detailing its protocol structure, including header formats and options.

4. **[RFC 8200 - Internet Protocol, Version 6 (IPv6) Specification](https://tools.ietf.org/html/rfc8200)**
   - Specifies the structure and usage of IPv6, including the approach to extension headers.

5. **[RFC 792 - Internet Control Message Protocol](https://tools.ietf.org/html/rfc792)**
   - Details the structure and usage of ICMP, integral to network management and behavior analysis.

6. **[RFC 826 - An Ethernet Address Resolution Protocol](https://tools.ietf.org/html/rfc826)**
   - Specifies the ARP protocol for IP address resolution in Ethernet networks.

7. **[IEEE 802.3 Standard](https://www.ieee802.org/3/)**
   - Defines Ethernet, detailing the technical specifications of physical and data link layer interactions.

### Online Resources

8. **[IETF (Internet Engineering Task Force)](https://www.ietf.org/)**
   - Access to all RFCs (Request for Comments) that define the protocols and extensions mentioned, such as IGMP and MLD.

9. **[Cisco Networking Academy](https://www.netacad.com/)**
   - Offers detailed educational materials and visual resources on networking layers, encapsulation, and protocol specifications.