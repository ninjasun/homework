def isOperand(x):
  return not (x == '+' or x == '-' or x == '*' or x == '/' or x == '^' or x == 'sin' or	x == 'cos')
def isOperator(x):
  return (x == '+' or x == '-' or x == '*' or x == '/' or x == '^' or x == 'sin' or	x == 'cos')
def isTrig(x):
  return (x == 'sin' or x == 'cos')

ops = []
var = raw_input("Enter variable name here: ")
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
  def __init__(self, val, parent, left=None, right=None):
    self.val = val
    self.parent = parent
    self.left = left
    self.right = right
  def isFull(self):
    return ((self.left != None and self.right != None) or (isTrig(self.val) and self.right != None)) 

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

def derive(target):
  if (isOperand(target.val)):
    print "hitting operand"
    if (target.val == var):
      return "1"
    else:
      return "0"
  else:
    if (target.val == '^'):
      return "(" + target.right.val + " * (" + target.left.val + ")^" + (str(int(target.right.val) - 1)) + ")"
    elif (target.val == '+' or target.val == '-'):
      return ("(" + derive(target.left) + ") " + target.val + " (" + derive(target.right) + ")")
    elif (target.val == '*'):
      du = derive(target.left)
      dv = derive(target.right)
      u = inorder(target.left)
      v = inorder(target.right)
      return "(("+v+") * ("+du+") + ("+u+") * ("+dv+"))" 
    elif (target.val == '/'):
      du = derive(target.left)
      dv = derive(target.right)
      u = inorder(target.left)
      v = inorder(target.right)
      return "( (("+v+") * ("+du+") + ("+u+") * ("+dv+")) / ("+v+")^2)" 
    elif (target.val == 'sin'):
      u = inorder(target.right)
      du = derive(target.right)
      return "(cos("+u+") * ("+du+"))"
    elif (target.val == 'cos'):
      u = inorder(target.right)
      du = derive(target.right)
      return "(- (sin("+u+") ) * ("+du+"))"

def inorder(target):
  if target == None:
    return ""
  else:
    return "("+str(inorder(target.left)) + str(target.val) + str(inorder(target.right))+")"

answer = derive(root)
print answer
