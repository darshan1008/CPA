
class Base1:
    B1 = "BASE1"
    def __init__(self):
        self.b1_No = -10

class Base2:
    B2 = "BASE2"
    def __init__(self):
        self.b2_No = -20

class Derived(Base1,Base2):
    def __init__(self):
        Base1.__init__(self)
        Base2.__init__(self)
        self.d_No = 30

dObj = Derived()
