from enum import Enum
import re

class Basic(Enum):
    String = 1
    Number = 2
    Varible = 3
    Function = 4

class Opcode(Enum):
    LOG = 1   # 0x01

def normalize_whitespace(s):
    return re.sub(r"\s+", " ", s).strip()


def GetData(Line, arg):
    parts = Line.split()
    curget = ""
    curarg = 0
    instring = False
    for char in normalize_whitespace(Line):
        if char == "\"":
            instring = not instring
        if char == " ":
            if not instring:
                if curarg == arg+1:
                    break
                curarg +=1
                curget = ""
        
        curget += char
    if curget.isdigit():
        return [Basic.Number, curget]
    elif curget.startswith("_"):
        return [Basic.Varible, curget]
    else:
        return [Basic.String, curget[2:-1]]


def tokenize(code):
    tokens = []
    for line in code.splitlines():
        line = normalize_whitespace(line)
        if not line or line.startswith("/"):
            continue
        
        if line.startswith("."):  # definicja funkcji
            funcname = line[1:]
            tokens.append([Basic.Function, funcname])
        
        elif line.startswith("#log"):
            arg = GetData(line, 0)  
            tokens.append([Opcode.LOG, arg[0], arg[1]])
    
    return tokens

def build_string_table(tokens):
    tabele = []


    return tabele

def binerize(tokens):
    out = []

    return out

# ---- MAIN ----

with open("fscript/codes/code.sml") as f:
    code = f.read()

tokens = tokenize(code)
string_table, string_index = build_string_table(tokens)
binary = binerize(tokens, string_index)

print("TOKENS:", tokens)
print("STRINGS:", string_table)
print("BINARY:", binary)