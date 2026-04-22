*This project has been created as part of the 42 curriculum by jperez-m.*

# NetPractice

## Description
NetPractice is a general practical introduction to basic concepts of computer networking. The main goal of this project is to configure small networks to make them function correctly. By solving these network configuration puzzles, you will gain hands-on experience and a solid understanding of how IP addressing, subnetting, routing, and basic network devices work.

## Networking Basics (Theory for Beginners)
If you are starting from zero, here are the essential concepts you need to know to tackle this project:

### 1. IP Addresses (IPv4)
An IP address is an identifier assigned to each device connected to a network. IPv4 addresses consist of 4 numbers (octets) separated by dots, each ranging from 0 to 255 (e.g., `192.168.1.10`).

**Private vs. Public IP Ranges**
Not all IPs are routed on the Internet. Some blocks are meant exclusively for private networks (like your home router or school network). The main private IP blocks are:
- **Class A:** `10.0.0.0` to `10.255.255.255`
- **Class B:** `172.16.0.0` to `172.31.255.255`
- **Class C:** `192.168.0.0` to `192.168.255.255`

Any IP outside these ranges is usually a public IP, reachable directly over the internet.

### 2. Subnet Masks & CIDR Notation
A subnet mask dictates which part of the IP address represents the overarching "Network" and which part represents the specific "Host" (device). It looks like an IP address (e.g., `255.255.255.0`). 

**CIDR Calculation (Classless Inter-Domain Routing)**
An IPv4 address has exactly 32 bits. The CIDR simply counts the number of bits (starting from the left) that belong to the network. The remaining bits belong to the hosts.
- Total IPs in a CIDR: `2^(32 - CIDR)`
- Usable IPs for devices: `2^(32 - CIDR) - 2` (subtracting Network and Broadcast addresses).

Here are a few common CIDR masks and how to calculate them:
- **`/0`** (e.g., `0.0.0.0/0`): This means 0 network bits. The remaining 32 bits are hosts. It covers every IP on the internet (`2^32` addresses). It's typically used to represent a default route.
- **`/24`** (e.g., `192.168.1.0/24`): 24 bits for the network. The last 8 bits (`32 - 24 = 8`) are for hosts. Total addresses: `2^8 = 256`. Usable IPs: `254`. The mask is `255.255.255.0`.
- **`/28`**: 28 bits for network, 4 bits for hosts (`32 - 28 = 4`). Total addresses: `2^4 = 16`. Usable IPs: `14`. The subnet increments every 16 IPs. Mask: `255.255.255.240`.
- **`/30`**: 30 bits for network, 2 bits for hosts (`32 - 30 = 2`). Total addresses: `2^2 = 4`. Usable: `2`. A `/30` is extremely common for point-to-point connections directly joining two routers (Router A gets one IP, Router B gets the other). Mask: `255.255.255.252`.

Devices in the same subnet (network part) can communicate directly. If they are in different subnets, they need a router.

### 3. Network and Broadcast Addresses
In any subnet, two addresses are reserved and cannot be assigned to individual devices:
- **Network Address:** The very first address in the subnet. It identifies the network itself.
- **Broadcast Address:** The very last address in the subnet. It is used to broadcast messages to all devices in that subnet.

### 4. Devices: Switches vs. Routers
- **Switch:** Connects devices within the **same** network (subnet). It does not assign IPs or route outside the local network.
- **Router:** Connects **different** networks together. If a computer wants to talk to a different subnet or the internet, it sends the data to the router. A router usually has multiple interfaces, each acting as a gateway for a different subnet.

### 5. Default Gateway
The default gateway is the IP address of the router interface connected to your local network. When a device wants to send a message to an IP address outside its own subnet, it blindly forwards the packet to its default gateway.

## Instructions

### Running the Training Interface
To launch the NetPractice training interface locally on your machine, you can use the provided script. Open your terminal at the root of the project and execute:

```bash
./run.sh
```
*(Alternatively, you can open the `index.html` file directly in your web browser.)*

### Exporting Configurations
As you solve each of the 10 levels in the web interface, you will have the option to download your working configuration in a file.
1. Solve the level.
2. Click the specific button in the interface to export the level's configuration.
3. Save the downloaded file.

### Submission Requirements
To submit this project for evaluation, **10 exported configuration files** (one for each level) must be placed directly at the repository root. Ensure the files are correctly named as expected by the grading system (usually `level1`, `level2`, etc.).

## Resources

During the development and resolution of this project, the following core networking concepts were studied and applied:
- **TCP/IP addressing**
- **Subnet masks** and bitwise operations
- **Default gateways**
- **Routers and switches**
- **OSI layers** (specifically Layer 2 Data Link and Layer 3 Network)

### References & Tools
- [Cisco Networking Academy](https://www.netacad.com/) (Basic networking theory)
- [IPv4 Subnet Calculator](https://www.calculator.net/ip-subnet-calculator.html) (Good for visualizing subnets)
- [Wikipedia: Classless Inter-Domain Routing (CIDR)](https://en.wikipedia.org/wiki/Classless_Inter-Domain_Routing)

### AI Usage
*AI (specifically Gemini) was utilized during this project not only for structuring this README file and proofreading documentation, but also to provide clear explanations of the specific concepts required for each of the 10 levels of the project. While the AI helped generate beginner-friendly explanations of networking concepts (IP addressing, routers, switches, subnetting, etc.), the actual logic, calculations, and problem-solving required to complete the network configuration levels were done manually to ensure a deep personal understanding of the subject matter.*
