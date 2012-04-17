import sys

def isOperand(x):
  """Checks if argument x is an operand"""
  return x not in ['+','-','*','/','^','sin','cos']

def isTrig(x):
  """Checks if argument x is a trig function"""
  return (x == 'sin' or x == 'cos')

def inorder(target):
  """Traverses tree in order and returns string in infix form"""
  if target == None:
    return ""
  return inorder(target.left) + str(target.val) + inorder(target.right)

def derive(target):
  """Recursively calculates derivative of argument target"""
  if (isOperand(target.val)):
    if (target.val == var):
      return "1" #when target is the variable
    return "0" #when target is some other operand
  else: #when target is an operator
    if (target.val == '^'): #exponentiation
      if (isTrig(target.left.val)):
        return "(("+target.right.val+"*"+inorder(target.left)+")*"+derive(target.left)+")"
      if (target.right.val == '2'):
        return "("+target.right.val+"*("+target.left.val+"))"
      return "("+target.right.val+"*("+target.left.val+")^"+(str(int(target.right.val)-1))+")"
    elif (target.val == '+' or target.val == '-'):
      return ("("+derive(target.left)+")"+target.val+"("+derive(target.right)+")")
    elif (target.val == '*'): #product rule
      du = derive(target.left)
      dv = derive(target.right)
      u = inorder(target.left)
      v = inorder(target.right)
      return "("+v+")*("+du+")+("+u+")*("+dv+")" 
    elif (target.val == '/'): #quotient rule
      du = derive(target.left)
      dv = derive(target.right)
      u = inorder(target.left)
      v = inorder(target.right)
      return " (("+v+")*("+du+")+("+u+")*("+dv+"))/("+v+")^2" 
    elif (target.val == 'sin'): #sin rule
      u = inorder(target.right)
      du = derive(target.right)
      return "cos("+u+")*("+du+")"
    elif (target.val == 'cos'): #cos rule
      u = inorder(target.right)
      du = derive(target.right)
      return "(-sin("+u+")*("+du+"))"

class Node(object):
  def __init__(self, val, parent, left=None, right=None):
    self.val = val
    self.parent = parent
    self.left = left
    self.right = right
  def isFull(self):
    """Checks if node has room for more children"""
    return ((self.left != None and self.right != None) or (isTrig(self.val) and self.right != None)) 

ops, var, arg = [], sys.argv[1], sys.argv[2]
expr = arg.split()
tokens = reversed(expr)

#Prints tree through iteration
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
print "Infix form of the function: " + ops.pop()

#Builds tree through iteration
root = Node(expr.pop(0), None)
curr = root
for op in expr:
  temp = Node(op, curr)
  if curr.left == None and (not isTrig(curr.val)):
    curr.left = temp
  else:
    curr.right = temp
  curr = temp
  if isOperand(op):
    curr = curr.parent
    while curr.isFull() and  curr != root:
      curr = curr.parent

print "Derivative of the function: " + derive(root)
