
class Base:
    b_iNo1 = 10
    b_iNo2 = 20
    def __init__(self):
        self.bm_No1 = "BASE"
        self.bm_No2 = True

class Derived(Base):
    d_iNo1 = -10
    def __init__(self):
        self.dm_No1 = "DERIVED"

def main():
    b_obj = Base()
    d_obj = Derived()
 
        
main()
