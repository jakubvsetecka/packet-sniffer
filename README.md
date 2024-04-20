# IPK-network-sniffer

- content structuring;
- executive summary of the theory necessary to understand the functionality of the implemented application;
- UML diagrams or at least a narrative about interesting source code sections;
- most importantly, the testing part, which should prove that you have done some validation and verification of implemented functionality;
- description of extra functionality or features beyond the standard outlined by the assignment;
- bibliography with a list of all the sources used.

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
    - [Class Diagram](#class-diagram)
    - [Flow Diagram](#flow-diagram)
    - [Use of Threading](#use-of-threading)
  - [Implementation](#implementation)
  - [Testing](#testing)
  - [Bibliography](#bibliography)

## Theory
- explain osi model
- encapsulation
- where are selected protocols located
- ip extensions and options (will be used when describing syntax for filters)
- link types

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
- TCP/UDP (Transport Layer): These protocols are responsible for end-to-end communication. TCP provides reliable transmission with flow control and error handling, while UDP offers a connectionless service for applications that require speed over reliability.
- ICMP4/ICMP6 (Network Layer): Internet Control Message Protocol is used for sending error messages and operational information indicating, for example, that a requested service is not available or that a host or router could not be reached.
- ARP/NDP (Data Link Layer): Address Resolution Protocol (ARP) and Neighbor Discovery Protocol (NDP) are used for mapping IP addresses to physical machine (MAC) addresses. ARP is used with IPv4 and NDP is part of the IPv6 specification.
- IGMP/MLD (Network Layer): Internet Group Management Protocol (IGMP) and Multicast Listener Discovery (MLD) are used to manage group membership for multicast traffic. IGMP is used with IPv4, while MLD is used with IPv6.
- IPv4/IPv6 (Network Layer): Internet Protocol versions 4 and 6 are the primary protocols for routing traffic across the Internet.
### IP Extensions and Options
IP headers can be extended with options to provide additional capabilities. Common options for IPv4 include security options (like the IPsec suite), record route (which stores the route of a packet), and timestamp options (which can be used for round-trip time measurements). IPv6 has a more streamlined approach with extension headers, which facilitate features like routing (alternate routing), fragmentation, and authentication.

### Link Types
In network packet capturing, the link type specifies the link protocol's type. Since this project uses only LINKTYPE_ETHERNET, the following applies:

- Ethernet: The most common link type for local area networks (LANs). Ethernet frames encapsulate various network layer protocols such as IP packets, and have a well-defined format including source and destination MAC addresses, type field (to indicate the network layer protocol), and a frame check sequence for error detection.

## Design Overview

This project is designed to capture and analyze network packets efficiently using the libpcap library. The system architecture utilizes object-oriented programming principles to modularize the process into clear, manageable components such as packet capturing, packet handling, and protocol processing.

### Class Diagram

The class diagram (Figure 1) provides a visual representation of the system's class structure and relationships. Key classes include `PacketSniffer`, `PacketHandler`, `ProtocolFactory`, and various protocol-specific handlers. This diagram helps in understanding the object-oriented approach used for the scalable and modular design of the packet analyzer.

![Protocols](imgs/protocol.png)

![Wrappers](imgs/wrappers.png)

![Class Diagram](imgs/class.png)
*Figure 1: Class Diagram showing the relationships and structure of the classes within the system.*

### Flow Diagram

The flow diagram (Figure 2) illustrates the process flow from the start of the application to the processing of packets. It highlights the dynamic interactions between components such as the `ArgumentParser`, `PacketSniffer`, `ThreadSafeQueue`, and `PacketHandler`.

![Flow Diagram](imgs/flow.png)
*Figure 2: Flow Diagram depicting the operational flow from packet capture to packet processing.*

### Use of Threading

To combat potential buffer overflow issues with the network card and to manage the high throughput of network data, the application employs a multithreading approach with a thread-safe queue. This design choice is crucial for the following reasons:

- **Asynchronous Processing**: The `PacketSniffer` captures packets and enqueues them into a `ThreadSafeQueue`. This decouples the packet capture from the packet processing, allowing both to occur simultaneously without waiting for one to complete before the other starts.

- **Buffer Overflow Prevention**: By immediately moving captured packets into a queue, we mitigate the risk of losing packets that could occur due to buffer overflow in the network card's buffer, especially under high traffic conditions.

- **Enhanced Performance**: Utilizing separate threads for capturing and processing packets takes advantage of multi-core processors, improving the application's overall performance and responsiveness.

This threaded approach ensures that the system can handle large volumes of network data efficiently and reliably, making it suitable for both development and production environments for network analysis and troubleshooting.



## Implementation

- shortly describe every class with its methods

## Testing

TODO


## Bibliography

> **Note:** Production of this README was accelerated by [chatGPT4](https://chat.openai.com/)