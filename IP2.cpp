#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;

// Function to convert decimal number to binary string
string decimalToBinary(int decimal)
{
    string binary = "";
    for (int i = 7; i >= 0; --i)
    {
        binary += to_string((decimal >> i) & 1);
    }
    return binary;
}

// Function to create a subnet mask with additional bits set to '1'
string createSubnetMask(int borrowBits)
{
    string subnetMask = "";
    int fullOctets = borrowBits / 8;
    int partialOctet = borrowBits % 8;

    // Set full octets to 255
    for (int i = 0; i < fullOctets; ++i)
    {
        subnetMask += "255.";
    }

    // Set partial octet
    int partialMask = 0;
    for (int i = 0; i < partialOctet; ++i)
    {
        partialMask += pow(2, 7 - i);
    }
    subnetMask += to_string(partialMask) + ".";

    // Append remaining octets
    for (int i = fullOctets + 1; i < 4; ++i)
    {
        subnetMask += "0.";
    }

    // Remove the trailing dot
    subnetMask.pop_back();

    return subnetMask;
}

// Function to adjust the subnet IP address based on the number of borrowed bits
string adjustSubnetIPAddress(string binaryIPAddress, int borrowBits)
{
    int firstZeroIndex = binaryIPAddress.find('0');
    if (firstZeroIndex != -1 && firstZeroIndex < borrowBits)
    {
        binaryIPAddress[firstZeroIndex] = '1';
    }
    return binaryIPAddress;
}

int main()
{
    string ipAddress;
    int subnet;
    cout << "Enter IP Address: ";
    cin >> ipAddress;

    cout << "\nEnter number of subnets: ";
    cin >> subnet;

    int borrowBits = 0;

    if (subnet > 0 && subnet <= 4)
        borrowBits = 2;
    if (subnet > 4 && subnet <= 8)
        borrowBits = 3;
    if (subnet > 8 && subnet <= 16)
        borrowBits = 4;

    char ipClass;
    if (ipAddress.substr(0, 3) == "192")
    {
        ipClass = 'C';
    }
    else if (ipAddress.substr(0, 3) == "172")
    {
        ipClass = 'B';
    }
    else
    {
        ipClass = 'A';
    }

    string defaultSubnetMask;
    switch (ipClass)
    {
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

    // Extract IP octets
    stringstream ss(defaultSubnetMask);
    string octet;
    string binarySubnet = "";
    while (getline(ss, octet, '.'))
    {
        int decimal = stoi(octet);
        binarySubnet += decimalToBinary(decimal) + ".";
    }
    // Remove the trailing dot
    binarySubnet.pop_back();

    cout << "\nClass of given IP address: " << ipClass << endl;
    cout << "\nDefault Subnet Mask: " << defaultSubnetMask << endl;
    cout << "\nSubnet Binary IP Address: " << binarySubnet << endl;
    int count = 0;
    int i = 0;
    while (count != borrowBits && i < binarySubnet.length())
    {
        if (binarySubnet[i] == '0')
        {
            binarySubnet[i] = '1';
            count++;
        }
        i++;
    }

    cout << "\nSubnet Binary IP Address(AB): " << binarySubnet << endl;

    int zeroCnt=0;
    while(i<=binarySubnet.length())
    {
        if (binarySubnet[i] == '0')
        {
            zeroCnt++;
        }
        i++;
    }
    cout<<"\nNumber of zero: "<<zeroCnt;
    cout<<"\nNumber of host: "<<pow(2,zeroCnt);

  

    return 0;
}
