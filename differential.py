def isOperand(x):
  return not (x == '+' or x == '-' or x == '*' or x == '/' or x == '^' or x == 'sin' or	x == 'cos')
def isOperator(x):
  return (x == '+' or x == '-' or x == '*' or x == '/' or x == '^' or x == 'sin' or	x == 'cos')
def isTrig(x):
  return (x == 'sin' or x == 'cos')

ops = []
#var = raw_input("Enter variable name here: ")
arg = raw_input("Enter expression here: ")
expr = arg.split()
tokens = reversed(expr)

for op in tokens:
  if isOperand(op):
    ops.append(op)
  elif op == 'sin' or op == 'cos':
    op1 = ops.pop()
    ops.append("(" + op + "(" + op1 + ")" + ")")
  else:
    op1 = ops.pop()
    op2 = ops.pop()
    ops.append("(" + op1 + op + op2 + ")")
print "Infix form of the function: " + ops.pop() + "\n"

class Node(object):
  def __init__(self, val, parent=None, left=None, right=None):
    self.val = val
    self.parent = parent
    self.left = left
    self.right = right
  def isFull(self):
    return ((curr.left != None and curr.right != None) or (isTrig(self.val) and curr.right != None)) 

root = Node(expr.pop(0))
print "root: " + root.val
curr = root

for op in expr:
  temp = Node(op, parent = curr)
  if curr.left == None and (not isTrig(curr.val)):
    curr.left = temp
  else:
    curr.right = temp
  if isOperator(op):
    curr = temp
  if isOperand(op):
    print "old up: " + curr.val
    curr = curr.parent
    print "new up: " + curr.val
    while curr.parent != None and curr != root and curr.isFull():
      curr = curr.parent

print "\n tree check"
temp = root
while (temp.left != None):
  print temp.val
  temp = temp.left

def derive(target):
  if (target.val == var):
    return 1
  elif (target.val.isDigit()): 
    return 0
  elif (target.val == '^'):
    return "(" + target.right.val + " * (" + target.left.val + ")^" + (target.right.val - 1) + ")"
  elif (target.val == '+' or target.val == '-'):
    return ("(" + derive(target.left) + ") " + target.val + " (" + defive(target.right) + ")")
  elif (target.val == 'sin'):
    tmp = target
