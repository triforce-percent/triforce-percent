import struct
import sys
import random

import createm64 as m64

def mk64_drive(nplayers, nframes, ctrlrmask=(True, True, True, True)):
    #Hold A, move control stick left/right, press Z occasionally
    playerstick = [random.randrange(-40, 40)] * nplayers
    playerstickdir = [bool(random.randrange(2))] * nplayers
    ret = bytearray()
    for f in range(nframes):
        for p in range(nplayers):
            if not ctrlrmask[p]:
                ret.extend(b'\x00\x00\x00\x00')
                continue
            b1 = 0x80 #A
            if random.randrange(60) == 0:
                b1 |= 0x20 #Z
            if random.randrange(20) == 0 and abs(playerstick[p]) > 30:
                b1 |= 0x40 #B
            b2 = 0
            b3 = playerstick[p]
            b4 = 0
            ret.extend(bytes([b1, b2, b3 if b3 >= 0 else b3 + 256, b4]))
            if playerstick[p] >= random.randrange(30, 50):
                playerstickdir[p] = True
            elif playerstick[p] <= random.randrange(-60, -40):
                playerstickdir[p] = False
            if playerstickdir[p]:
                playerstick[p] -= 1
            else:
                playerstick[p] += 1
    return ret

def mk64_run(nplayers):
    c1only = (True, False, False, False)
    run = m64.wait(nplayers, 30)
    run += m64.mash_button(nplayers, 60, bytes([0x10, 0, 0, 0]))
    run += m64.wait(nplayers, 100)
    run += m64.mash_button(nplayers, 2*(nplayers-1), b'\x00\x00\x40\x00', c1only) #Over to N player mode
    run += m64.mash_button(nplayers, 4, b'\x80\x00\x00\x00', c1only) #A-A
    run += m64.mash_button(nplayers, 4, b'\x00\x00\x00\xC0', c1only) #Down to 150 CC
    run += m64.mash_button(nplayers, 4, b'\x80\x00\x00\x00', c1only) #A-A
    run += m64.wait(nplayers, 30)
    run += m64.mash_button(nplayers, 2, b'\x80\x00\x00\x00', (True, False, False, False)) #A
    run += m64.wait(nplayers, 30)
    run += m64.mash_button(nplayers, 2, b'\x80\x00\x00\x00', (False, True, False, False)) #A
    run += m64.wait(nplayers, 30)
    run += m64.mash_button(nplayers, 2, b'\x80\x00\x00\x00', (False, False, True, False)) #A
    run += m64.wait(nplayers, 30)
    run += m64.mash_button(nplayers, 2, b'\x80\x00\x00\x00', (False, False, False, True)) #A
    run += m64.wait(nplayers, 30)
    run += m64.mash_button(nplayers, 90, b'\x80\x00\x00\x00') #All mash A until race starts
    run += mk64_drive(nplayers, 5000)
    totalframes = len(run) // (4*nplayers)
    return m64.create_header(nplayers, totalframes) + run
    
def main():
    if len(sys.argv) != 3:
        print('Usage: createdummym64.py path/to/output.m64 n_players')
        sys.exit(1)
    nplayers = int(sys.argv[2])
    f = open(sys.argv[1], 'wb')
    f.write(mk64_run(nplayers))
    f.close()

if __name__ == '__main__':
    main()
