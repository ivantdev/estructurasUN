class Stack():
  def __init__(self, size=5):
    self.max = size
    self.arr = [None]*self.max
    self.idx = 0

  def full(self):
    return self.max == self.idx

  def empty(self):
    return self.idx == 0

  def push(self, x):
    if (not self.full()):
      self.arr[self.idx] = x
      self.idx += 1
      return
    else:
      print('full')

  def pop(self):
    if(not self.empty()):
      self.idx -= 1
      x = self.arr[self.idx]
      return x

  def is_palindrome(self):
    palindrome = True
    for i in range(self.idx//2):
      if(self.arr[i] != self.arr[self.idx - 1 - i]):
        palindrome = False
      if(not palindrome): break
    return palindrome

  def getArr(self):
    return self.arr

string = "oso"
stack = Stack(len(string))
for i in string:
  stack.push(i)

print('array: ', stack.getArr(),'\nes palindromo?', stack.is_palindrome())