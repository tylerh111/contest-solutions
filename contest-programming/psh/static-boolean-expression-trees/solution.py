### PSH Static Boolean Expression ###

def static_boolean_expression(n):
    stack = []
    strg = raw_input()
    strg_list = strg.split()
    for inp in strg_list:
        if inp == 't':
            stack.append(True)
        elif inp == 'f':
            stack.append(False)
        elif inp == '!':
            op1 = stack.pop()
            stack.append(not op1)
        elif inp == '&':
            op1 = stack.pop()
            op2 = stack.pop()
            stack.append(op1 & op2)
        elif inp == '|':
            op1 = stack.pop()
            op2 = stack.pop()
            stack.append(op1 | op2)
        elif inp == '^':
            op1 = stack.pop()
            op2 = stack.pop()
            stack.append(op1 ^ op2)
        else:
            print 'Oops'
    return stack.pop()

#start#
cases = input()
for i in range(0, cases, 1):
    operators = input()
    result = static_boolean_expression(operators)
    print str(result).lower()

