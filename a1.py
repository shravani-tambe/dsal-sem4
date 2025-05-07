def teledatabase(): 
    phone = [] 
    n = int(input("Enter number of clients: "))
    for i in range(n): 
        x = int(input(f"Enter phone number {i+1}: "))
        phone.append(x)
    return phone 
    
def hash1(key, table_size): 
    return key % table_size
    
def hash2(key): 
    return 7 - (key % 7)
    
def display_table(hashtable): 
    print(f"\nHash Index\tPhone Number")
    for i in range(len(hashtable)): 
        if hashtable[i] != -1: 
            print(f"{i}\t\t{hashtable[i]}")
        else: 
            print(f"{i}\t\tEMPTY")
                
while True: 
    phone = teledatabase() 
    m = int(input("Enter Hash Table Size: "))
    hashtable = [-1] * m
    
    opt = int(input(
        "\nChoose collision resolution technique:\n"
        "1. Linear Probing\n"
        "2. Double Hashing\n"
        "3. Exit\n"
        "Choice: "
    ))
    
    if opt == 3:
        print("TERMINATED SUCCESSFULLY")
        break
    
    for num in phone: 
        h1 = hash1(num, m)
        
        if hashtable[h1] == -1: 
            hashtable[h1] = num
        else: 
            if opt == 1:  # Linear Probing
                orig_h1 = h1
                while hashtable[h1] != -1:
                    h1 = (h1 + 1) % m
                    if h1 == orig_h1:
                        print("Hash Table is full!")
                        break
                else:
                    hashtable[h1] = num

            elif opt == 2:  # Double Hashing
                h2 = hash2(num)
                i = 1
                orig_h1 = h1
                while hashtable[h1] != -1:
                    h1 = (orig_h1 + i * h2) % m
                    i += 1
                    if i > m:
                        print("Hash Table is full!")
                        break
                else:
                    hashtable[h1] = num

    display_table(hashtable)
