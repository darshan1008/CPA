#! /usr/bin/python3 

# Creation method 1

times=67
print ("-" * times)
print ("[1]:Demo of singly quoted string") 
s1 = 'Hello' 
s2 = 'That is "so called" stuff' 
print (s1) 
print (s2) 
print ("-" * times)

# Creation method 2
print ("[2]:Demo of doubly quoted string")
s1 = "Hello" 
s2 = "There's a general perception ... " 
print (s1) 
print (s2) 
print ("-" * times) 
print ("Demo of escape sequences in quoted strings")
print ("Demo of newline\nescape sequence") 
print ('Demo of tab\tescape sequence') 
print ("-" * times) 

# Creation method 3
print ("[3]:Demo of triply quoted string") 
s1 = """This is a 
triple quoted string"""
print (s1) 
print ("-" * times); 

# Creation method 4
print ("[4]:Demo of raw string") 
s1 = r"This is a raw string. Escape sequences like \n have no effect"
print (s1)
print ("-" * times)

# String manipulations via operators
print ("[5]:Concatenation demo") 
s1 = "Hello" 
s2 = "World" 
print ("s1=" + s1); 
print ("s2=" + s2); 
print ("s1+s2=" + s1+s2)
print ("s1+','+s2+'!'=" + s1 + "," + s2 + "!")
print ("-" * times) 

# Printing length of a string 
print ("[6]:Demo of length of a string")  
s1 = "This is an arbitrary string" 
print ("len(s1)=" + str (len (s1)))
print ("-" * times) 

# Testing a character for membership 
print ("[7]:Demo of testing membership of a character in a string") 
s1 = "Hello" 
ans= 'H' in s1 
print ("Output of 'H' in s1 = " + str (ans))
ans = 'z' in s1
print ("Output of 'z' in s1 = " + str (ans))
print ("-" * times)

# Indexing of a string 
print ("[8]:Demo of indexing of a string") 
print ("Printing first two characters")
s1 = "Hello,World!" 
print ("s1[0]\t:\t" + s1[0] + "\ns1[1]\t:\t" + s1[1])
print ("Printing whole string character by character") 
for i in range (len(s1)):
	print ("s[" + str (i) + "]\t:\t" + s1[i])
print ("Negative indexing:Printing last two characters") 
print ("s1[-1]\t:\t" + s1[-1] + "\ns1[-2]\t:\t" + s1[-2]) 
print ("-" * times)

# Slicing a string 
print ("[9]:Demo of slicing a string") 
s1 = "Hello,slicing string" 
print ("s1[0:len(s1)]\t\t:\t " + s1[0:len(s1)])
print ("s1[0:5]\t\t\t:\t " + s1[0:5]) 
print ("s1[:5]\t\t\t:\t " + s1[:5])
print ("s1[14:len(s1)]\t\t:\t " + s1[14:len(s1)])
print ("s1[14:]\t\t\t:\t " + s1[14:])
print ("s1[::]\t\t\t:\t " + s1[::])
print ("s1[-len(s1):]\t\t:\t", s1[-len(s1):])
print ("s1[-len(s1):len(s1)]\t:\t", s1[-len(s1):len(s1)])
print ("s1[0:len(s1):2]\t\t:\t", s1[0:len(s1):2])
print ("s1[len(s1)-1:0:-2]\t:\t", s1[len(s1)-1:0:-2])
print ("-" * times)


