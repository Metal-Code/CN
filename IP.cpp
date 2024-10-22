#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Function to calculate subnet mask based on the number of bits for the subnet
string calculateSubnetMask(int subnetBits) {
    string subnetMask = "";
    int fullOctets = subnetBits / 8;
    int partialOctet = subnetBits % 8;
    
    for (int i = 0; i < fullOctets; ++i) {
        subnetMask += "255.";
    }
    
    if (partialOctet > 0) {
        int partialMask = 0;
        for (int i = 0; i < partialOctet; ++i) {
            partialMask += pow(2, 7 - i);
        }
        subnetMask += to_string(partialMask) + ".";
    }
    
    // Append remaining octets
    for (int i = fullOctets + 1; i <= 4; ++i) {
        subnetMask += "0.";
    }
    
    // Remove the trailing dot
    subnetMask.pop_back();
    
    return subnetMask;
}

int main() {
    string ipAddress;
    int numSubnets;
    
    cout << "Enter IP Address: ";
    cin >> ipAddress;
    cout << "Enter the number of subnets: ";
    cin >> numSubnets;
    
    // Extracting the class of the IP address
    char ipClass;
    if (ipAddress.substr(0, 3) == "192" || ipAddress.substr(0, 3) == "172" || ipAddress.substr(0, 2) == "10") {
        ipClass = 'C';
    } else if (ipAddress.substr(0, 2) == "19" || (ipAddress[0] == '1' && ipAddress[1] <= '6')) {
        ipClass = 'B';
    } else {
        ipClass = 'A';
    }
    
    // Default subnet mask based on IP class
    string defaultSubnetMask;
    switch(ipClass) {
        case 'A':
            defaultSubnetMask = "255.0.0.0";
            break;
        case 'B':
            defaultSubnetMask = "255.255.0.0";
            break;
        case 'C':
            defaultSubnetMask = "255.255.255.0";
            break;
    }
    
    cout << "IP Class: " << ipClass << endl;
    cout << "Default Subnet Mask: " << defaultSubnetMask << endl;
    
    // Calculate subnet range and subnet mask for each subnet
    int subnetBits = ceil(log2(numSubnets)); // Number of bits required to represent the subnets
    cout << "Subnets Information: " << endl;
    cout << "Subnet\t\tStarting IP\t\tEnding IP\t\tSubnet Mask" << endl;
    for (int i = 0; i < numSubnets; ++i) {
        // Calculate subnet range
        int subnetSize = pow(2, 32 - subnetBits); // Number of IP addresses in each subnet
        int start = i * subnetSize;
        
        int ip1, ip2, ip3, ip4;
        sscanf(ipAddress.c_str(), "%d.%d.%d.%d", &ip1, &ip2, &ip3, &ip4);
        int newStart = (ip1 << 24) | (ip2 << 16) | (ip3 << 8) | ip4;
        newStart += start;

        ip1 = (newStart >> 24) & 0xFF;
        ip2 = (newStart >> 16) & 0xFF;
        ip3 = (newStart >> 8) & 0xFF;
        ip4 = newStart & 0xFF;
        string startingIP = to_string(ip1) + "." + to_string(ip2) + "." + to_string(ip3) + "." + to_string(ip4);
        
        int end = newStart + subnetSize - 1;
        
        ip1 = (end >> 24) & 0xFF;
        ip2 = (end >> 16) & 0xFF;
        ip3 = (end >> 8) & 0xFF;
        ip4 = end & 0xFF;
        string endingIP = to_string(ip1) + "." + to_string(ip2) + "." + to_string(ip3) + "." + to_string(ip4);
        
        cout << "Subnet " << i + 1 << ":\t" << startingIP << "\t\t" << endingIP << "\t\t" << calculateSubnetMask(32 - subnetBits) << endl;
    }
    
    return 0;
}
