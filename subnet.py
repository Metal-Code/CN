def ip_Class(ip):
    ipsplit = ip.split('.')
    if int(ipsplit[0]) <= 127:
        return 'A', "255.0.0.0",8
    elif 128 <= int(ipsplit[0]) <= 191:
        return 'B', "255.255.0.0",16
    elif 192 <= int(ipsplit[0]) <= 223:
        return 'C', "255.255.255.0",24


def decimal_to_binary_conversion_for_8bit(decimal_str):
    decimal_num = int(decimal_str)
    if 0 <= decimal_num <= 255:
        binary_str = format(decimal_num, '08b')
        return binary_str
    else:
        print("Input must be in the range 0 to 255.")

def bit_generation(bits, n=0):
    permutations = []
    if n.bit_length() <= bits:
        permutations.append('{:0{}b}'.format(n, bits))
        permutations += bit_generation(bits, n + 1)
    return tuple(permutations)




ipaddress = input("Enter the IP address: ")
no_of_subnets = int(input("Enter the number of subnets to be created: "))

classIp, Dsubnet,networkbits = ip_Class(ipaddress)
print(f'\nClass of the IP address is : {classIp} \nDefault Subnet : {Dsubnet}')


subnetsplit = Dsubnet.split('.')
binarysubnet = ""

print(subnetsplit)

for i in range(4):
    binarysubnet=binarysubnet + decimal_to_binary_conversion_for_8bit(subnetsplit[i])

print(binarysubnet)

newbs = []
newbs[:] = binarysubnet

sindex = -1

no_of_extra_bits = 0

for k in range(1,10):
    if no_of_subnets>pow(2,k-1)and no_of_subnets<=pow(2,k):
        no_of_extra_bits = k
        break

for j in range(0, 32):
    if int(newbs[j]) == 0:
        sindex = j
        s = no_of_extra_bits
        while s != 0:
            newbs[sindex] = '1'
            sindex = sindex + 1
            s = s - 1
        break

print(newbs)

mystring = ""
count = 0
newsubnet = ""
for i in range(0, 32):
    mystring = mystring + str(newbs[i])
    count = count + 1
    if count == 8:
        count = 0
        newsubnet = newsubnet + str(int(mystring, 2))+'.'
        mystring = ""

newsubnet=newsubnet[:-1]
print("New Subnet:", newsubnet)

count_1 = newbs.count('1')

print(f"No. of adresses in one subnet = {pow(2,32-count_1)}")

ipsplit = ipaddress.split('.')

permutations = bit_generation(no_of_extra_bits)


ipbinary = ""
for i in range(4):
    ipbinary=ipbinary + decimal_to_binary_conversion_for_8bit(ipsplit[i])

newipb = []
newipb[:] = ipbinary



for i in range(no_of_subnets):
    start = count_1
    setsubnetbits = networkbits
    for j in range(no_of_extra_bits):
        newipb[setsubnetbits]=str(permutations[i][j])
        setsubnetbits = setsubnetbits + 1
    
    l = start
    for k in range(l,32):
        newipb[start] = '0'
        start+=1
    
    mystring = ""
    count = 0
    newsubnet = ""
    for m in range(0, 32):
        mystring = mystring + str(newipb[m])
        count = count + 1
        if count == 8:
            count = 0
            newsubnet = newsubnet + str(int(mystring, 2))+'.'
            mystring = ""

    newsubnet=newsubnet[:-1]
    print(f"\nSubnet {i+1} starts from {newsubnet}")

    start = l
    for k in range(l,32):
        newipb[start] = '1'
        start+=1
    
    mystring = ""
    count = 0
    newsubnet = ""
    for m in range(0, 32):
        mystring = mystring + str(newipb[m])
        count = count + 1
        if count == 8:
            count = 0
            newsubnet = newsubnet + str(int(mystring, 2))+'.'
            mystring = ""

    newsubnet=newsubnet[:-1]
    print(f"Subnet {i+1} ends from {newsubnet}")
