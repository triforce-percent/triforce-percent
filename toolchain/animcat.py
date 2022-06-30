'''
Concatenate animations from bin files according to anim.txt.
Output:
- a bin file containing all the animations
- a .c file containing an animation header table of z64_animation_entry_link_t,
  with addresses relative to 0 = beginning of file
'''
import sys, os, glob

class AnimInfo():
    def __init__(self, filepath, frames, addr):
        self.filepath, self.frames, self.addr = filepath, frames, addr
        print(hex(addr) + ': ' + str(self.frames) + ' frames: ' + self.filepath)

animinfo = []
curaddr = 0
binfiles = glob.glob('*.bin')
with open('anim.txt', 'r') as txtfile:
    for l in txtfile:
        l = l.strip()
        if not l: continue
        if l[0] == '#': continue
        matchfiles = list(filter(lambda x: 'linkcustomanim_' + l + '_' in x, binfiles))
        if len(matchfiles) == 0:
            raise RuntimeError('Could not find animation matching ' + l)
        if len(matchfiles) > 1:
            raise RuntimeError('Multiple animations match ' + l 
                + ', maybe you did not delete the old one when changing animation length')
        binfile = matchfiles[0]
        frames = binfile[binfile.rindex('_')+1:-4]
        if not frames.isnumeric():
            raise RuntimeError('Error with anim frame count ' + frames)
        frames = int(frames)
        size = os.path.getsize(binfile)
        assert frames * 0x86 == size
        animinfo.append(AnimInfo(binfile, frames, curaddr))
        curaddr += size

if len(animinfo) == 0:
    raise RuntimeError('No animations found')

with open('anim.bin', 'wb') as binout:
    for a in animinfo:
        with open(a.filepath, 'rb') as f:
            binout.write(f.read())
    if (curaddr & 0xF) != 0:
        oldcuraddr = curaddr
        curaddr = (curaddr + 15) & 0xFFFFFFF0
        binout.write(bytes([0] * (curaddr - oldcuraddr)))
    
with open('anim.c', 'w') as cout:
    cout.write('LinkAnimationHeader linkAnimPatchTable[' 
        + str(len(animinfo)) + '] = {\n')
    for a in animinfo:
        cout.write('    {{' + str(a.frames) + '}, ' + hex(a.addr) + '},\n')
    cout.write('};\n')

print('animcat done')
