s = input("Enter a string:")
sub = input("Enter a substring to search for all occurences:")

search_index = 0
L = []

while sub in s[search_index : ]:
    k = s.index(sub, search_index)
    L.append(k)
    search_index = k+1

print(L)


    
