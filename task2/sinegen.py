import math
from pathlib import Path

path = "task1/sinerom.mem"
file = Path(path)

DATA_WIDTH = 8
ADDRESS_SIZE = 8
ROM_DEPTH = 1 << ADDRESS_SIZE
ROM_MAX = 1 << DATA_WIDTH 

def scale(v):
    AMPLITUDE = (ROM_MAX / 2) - 1
    v *= AMPLITUDE
    v += AMPLITUDE

    return v

def get_hex_string(v, i):
    return f"{v:2X}\n" if ((i + 1) % 16 == 0) else f"{v:2X} "

with file.open("w") as f:

    for i in range(ROM_DEPTH):
        
        v = math.cos(2*math.pi* i / ROM_DEPTH)

        v = int(scale(v))
        f.write(get_hex_string(v, i))