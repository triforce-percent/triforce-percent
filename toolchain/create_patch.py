import sys

def patchfull(i, o):
    ind = i.read()
    inptr = 0
    outd = b''
    while inptr < len(ind):
        bthistime = min(255, len(ind)-inptr)
        outd += bytes([0, bthistime]) + ind[inptr:inptr+bthistime]
        inptr += bthistime
    outd += bytes([0, 0])
    o.write(outd)

def patchdiff(orig, mod, o):
    origd = orig.read()
    modd = mod.read()
    if len(origd) != len(modd):
        raise RuntimeError('Patching can\'t change file length!')
    inptr = 0
    outd = b''
    while True:
        if origd[inptr:] == modd[inptr:]:
            break # No more differences, quit early
        skipcount = 0
        while skipcount < 0x7FFF and inptr < len(origd):
            if origd[inptr] != modd[inptr]:
                break
            skipcount += 1
            inptr += 1
        newdata = b''
        while len(newdata) < 0xFF and inptr < len(origd):
            if origd[inptr] == modd[inptr]:
                if inptr < len(origd) - 1 and origd[inptr+1] != modd[inptr+1] and len(newdata) < 200:
                    pass # Don't stop replacement mode for just 1 byte same
                    # (i.e. next byte is different), unless we're going to have to switch
                    # out of replacement mode soon anyway
                else:
                    break
            newdata += bytes([modd[inptr]])
            inptr += 1
        if skipcount <= 0x7F:
            outd += bytes([skipcount])
        else:
            outd += bytes([0x80 | (skipcount >> 8), skipcount & 0xFF])
        outd += bytes([len(newdata)])
        outd += newdata
        if inptr == len(origd):
            break
    outd += bytes([0, 0])
    o.write(outd)

if __name__ == '__main__':
    assert len(sys.argv) == 4
    assert sys.argv[3].endswith('.pat')
    if sys.argv[1].endswith('full'):
        with open(sys.argv[2], 'rb') as i, open(sys.argv[3], 'wb') as o:
            patchfull(i, o)
    else:
        with open(sys.argv[1], 'rb') as orig, open(sys.argv[2], 'rb') as mod, open(sys.argv[3], 'wb') as o:
            patchdiff(orig, mod, o)
        
