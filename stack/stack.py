from abc import ABC, abstractmethod
from curses.ascii import isdigit

class GenericStack(ABC):
    @abstractmethod
    def push(self, x):
        pass

    @abstractmethod
    def pop(self):
        pass
    
    @abstractmethod
    def full(self):
        pass
    
    @abstractmethod
    def empty(self):
        pass

class GenericArrayStack(GenericStack):
    def __init__(self, size = 5):
        self.__arr = [None]*size
        self.__top = 0
        self.__size = size
    
    @property
    def arr(self):
        return self.__arr
    
    @property
    def top(self):
        return self.__top
        
    def full(self):
        return self.__top == self.__size
    
    def empty(self):
        return self.__top <= 0
    
    def push(self, x):
        if(not self.full()):
            self.__arr[self.__top] = x
            self.__top += 1
        else: print('full')
    
    def pop(self):
        if(not self.empty()):
            self.__top -= 1
            return self.__arr[self.__top]
        else: print("empty")

class PalindromeStack(GenericArrayStack):
    def __init__(self, size=5):
        super().__init__(size)

    def is_palindrome(self):
        palindrome = True
        for i in range(self.top//2):
            if(self.arr[i] != self.arr[self.top - 1 - i]):
                palindrome = False
            if(not palindrome): break
        return palindrome

    def getArr(self):
        return self.arr
    
class PostfixStack(GenericArrayStack):
    def __init__(self, size=5):
        super().__init__(size)
    
    def push(self, x):
        if isdigit(x):
            x = int(x)
            super().push(x)
        elif(x == "+"):
            a = self.pop()
            b = self.pop()
            c = a + b
            super().push(c)
        elif(x == "-"):
            a = self.pop()
            b = self.pop()
            c = a - b
            super().push(c)
        elif(x == "*"):
            a = self.pop()
            b = self.pop()
            c = a * b
            super().push(c)
        elif(x == "/"):
            a = self.pop()
            b = self.pop()
            c = a / b
            super().push(c)
    
    def getArr(self):
        return super().__arr
            

def usePalindromeStack():
    string = "oso"
    stack = PalindromeStack(len(string))
    for i in string:
        stack.push(i)
    print('array: ', stack.getArr(),'\nes palindromo?', stack.is_palindrome())

def usePostFixStack(s):
    s = s.split()
    stack = PostfixStack(len(s))
    for i in s:
        stack.push(i)
    print('resultado: ', stack.pop())
    print(stack.getArr())
        
def main():
    # usePalindromeStack()
    usePostFixStack("2 3 5 * +")
    
    usePostFixStack("2 3 + 5 *")
    
if __name__ == "__main__":
    main()