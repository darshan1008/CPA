L = []
for i in range(10):
    n = int(input("Enter an integer:"))
    L.append(n)
    
print("BREAK")

for x in L:
    if x % 7 == 0:
        break
    print("x:", x)

print("CONTINUE")
for x in L:
    if x % 7 == 0:
        continue
    print("x:", x)



