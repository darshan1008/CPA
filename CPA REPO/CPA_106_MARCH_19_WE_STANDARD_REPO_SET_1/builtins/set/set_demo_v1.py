#! /usr/bin/python3

times = 80

print ("[1]:Set creation") 
S = {1, 2, 3}
print ("S:", S) 
print ("Set can contain objects of any immutable type") 
S = {1, 3.14, "Hello", (1,2,3)} 
print ("S:", S) 
print ("-" * times) 

print ("[2]:Converting set into list and tuples")
S = {1, 2, 3, 4, 5} 
L = list (S) 
T = tuple (S) 
print ("S:", S, "L:", L, "T:", T) 
print ("-" * times) 

print ("[3]:Converting list and tuples into set") 
L = [1, 2, 3, 4, 5] 
T = (1.1, 2.2, 3.3, 4.4, 5.5) 
S1 = set (L) 
S2 = set (T) 
print ("L:", L, "S1:", S1)
print ("T:", T, "S2:", S2) 
print ("-" * times) 

print ("[4]:Adding member to a set") 
S = {1, 2, 3}
print ("Initial S:", S)
S.add (4)
print ("After S.add (4), S:", S) 
L = [5, 6, 7, 8]
for x in L:
    S.add (x)
print ("S:",S)
print ("-" * times) 

print ("[5]:Emptying the set") 
S = {1, 2, 3, 4, 5} 
print ("Initial S:", S) 
S.clear () 
print ("After S.clear (), S:", S); 
print ("-" * times) 

print ("[6]:Poping an element") 
S = {1, 2, 3, 4, 5} 
print ("Initial S:", S) 
S.pop ()
print ("After first S.pop (), S:", S)
S.pop ()
print ("After second S.pop (), S:", S) 
S.pop ()
print ("After third S.pop (), S:", S) 
print ("-" * times) 

print ("[7]:Removing a particular element") 
S = {1, 2, 3, 4, 5} 
print ("Initial S:", S) 
S.remove (3) 
print ("After S.remove (3), S:", S) 
S.remove (5)
print ("After S.remove (5), S:", S) 
print ("-" * times) 

print ("[8]:Duplicating a set") 
S = {1, 2, 3, 4, 5} 
S1 = S.copy () 
print ("Initial S:", S)
print ("After S1=S.copy (), S1:", S1) 
print ("-" * times) 

print ("[9]:Union of sets") 
S1 = {1, 2, 3, 4} 
S2 = {3, 4, 5, 6} 
S  = S1.union (S2)
print ("S1:", S1, "S2:", S2, "S=S1.union (S2):", S)
print ("-" * times)

print ("[10]:Union of sets and update") 
S1 = {1, 2, 3, 4}
print ("Initial S1:", S1)
S2 = {3, 4, 5, 6}
print ("Initial S2:", S2) 
S1.update (S2) 
print ("After S1.update (S2), S1:", S1) 
print ("-" * times) 

print ("[11]:Intersection of sets") 
S1 = {1, 2, 3, 4}
S2 = {3, 4, 5, 6}
S  = S1.intersection (S2)
print ("S1:", S1, "S2:", S2, "S=S1.intersection(S2):", S)
print ("-" * times) 

print ("[12]:Intersection of sets and update") 
print ("S1:", S1)
S1 = {1, 2, 3, 4}
print ("S2:", S2) 
S2 = {3, 4, 5, 6} 
S1.intersection_update (S2)
print ("After S1.update_intersection (S2), S1:", S1) 
print ("-" * times) 

print ("[13]:Difference of sets") 
S1 = {1, 2, 3, 4, 5}
S2 = {4, 5, 6, 7, 8} 
S  = S1.difference (S2) 
print ("S1:", S1) 
print ("S2:", S2) 
print ("S = S1.update (S2):", S) 
print ("-" * times) 

print ("[14]:Difference and update") 
S1 = {1, 2, 3, 4, 5} 
print ("S1:", S1)
S2 = {3, 4, 5, 6, 7}
print ("S2:", S2) 
S1.difference_update (S2) 
print ("S1.update(S2), S1:", S1) 
print ("-" * times) 

print ("[15]:Symmetric difference of sets") 
S1 = {1, 2, 3, 4, 5}
S2 = {3, 4, 5, 6, 7}
S  = S1.symmetric_difference (S2)
print ("S1:", S1)
print ("S2:", S2) 
print ("S=S1.symmetric_difference (S2):", S) 
print ("-" * times) 

print ("[16]:Symmetric difference and update") 
S1 = {1, 2, 3, 4, 5}
print ("S1:", S1) 
S2 = {3, 4, 5, 6, 7}
print ("S2:", S2) 
S1.symmetric_difference_update (S2) 
print ("After S1.symmetric_difference_update(S2):", S1)
print ("-" * times) 

print ("[17]:Checking for disjoint property") 
S1 = {1, 2, 3, 4, 5} 
S2 = {6, 7, 8, 9, 10}
S3 = {4, 5, 6, 7, 8}
print ("S1:", S1) 
print ("S2:", S2) 
print ("S3:", S3) 
ans = S1.isdisjoint (S2) 
print ("After ans = S1.isdisjoint (S2), ans:", ans) 
ans = S1.isdisjoint (S3)
print ("After ans = S1.isdisjoint (S3), ans:", ans) 
print ("-" * times)

print ("[18]:Checking for subset property") 
S1 = {1, 2, 3, 4, 5} 
S2 = {1, 2, 3}
S3 = {3, 4, 5, 6}
print ("S1:", S1)
print ("S2:", S2)
print ("S3:", S3) 
ans = S2.issubset (S1) 
print ("After ans = S2.issubset (S1), ans:", ans)
ans = S3.issubset (S1) 
print ("After ans = S3.issubset (S1), ans:", ans) 
print ("-" * times) 

print ("[19]:Checking for superset property") 
S1 = {1, 2, 3, 4, 5}
S2 = {1, 2, 3} 
S3 = {3, 4, 5, 6}
print ("S1:", S1) 
print ("S2:", S2) 
print ("S3:", S3)
ans = S1.issuperset (S2)
print ("After ans = S1.issuperset (S2), ans:", ans)
ans = S1.issuperset (S3) 
print ("After ans = S1.issuperset (S3), ans:", ans)
print ("-" * times) 
