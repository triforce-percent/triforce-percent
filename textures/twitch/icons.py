import json
from PIL import Image # pip install pillow
import struct
import ci4tool

with open('icons.json', 'r') as f:
    icons_d = json.loads(f.read())

all_icons = []
for g in icons_d['global']:
    all_icons.append(g)
for s in icons_d['sub']:
    all_icons.append(s)
for e in icons_d['emote']:
    all_icons.append(e)

palette_files = set()

for icon in all_icons:
    palette_files.add(icon['plt'])

palette_files = sorted(list(palette_files))

for icon in all_icons:
    icon['plt'] = palette_files.index(icon['plt'])

palettes = []
for p in palette_files:
    print('Palette ' + p)
    palettes.append(ci4tool.load_palette_from_png(p, True))

outsz = 32

def pad_image(im, newsize):
    w, h = im.size
    px, py = (newsize - w) // 2, (newsize - h) // 2
    res = Image.new('RGBA', (newsize, newsize), (0, 0, 0, 0))
    res.paste(im, (px, py))
    return res

for icon in all_icons:
    print('Icon ' + icon['path'])
    with Image.open(icon['path']) as im:
        assert (im.size[0] in [71, 72] and im.size[1] in [72, 73]) or im.size == (outsz, outsz) or im.size == (112, 112)
        if len(im.getbands()) == 1:
            im = im.convert()
        if im.size == (112, 112):
            im = pad_image(im, 128)
        if im.size[0] != outsz or im.size[1] != outsz:
            im = im.resize((outsz, outsz), resample=Image.NEAREST)
        icon['data'] = ci4tool.apply_palette_to_im(im, palettes[icon['plt']], icon['dither'])

with open('icons.inc', 'w') as f:
    f.write('#define ICON_SIZE ' + str(outsz) + '\n')
    f.write('#define ICONS_PER_GROUP (2048 / ((ICON_SIZE * ICON_SIZE) / 2))\n')
    f.write('#define NUM_ICONS ' + str(len(all_icons)) + '\n')
    f.write('#define IDX_SUB_START ' + str(len(icons_d['global'])) + '\n')
    f.write('#define IDX_EMOTE_START ' + str(len(icons_d['global']) + len(icons_d['sub'])) + '\n')
    f.write('#define NUM_PALETTES ' + str(len(palettes)) + '\n\n')
    f.write('__attribute__((aligned(16))) static const u64 icon_textures[] = {\n')
    for icon in all_icons:
        f.write(ci4tool.indexes_to_c(icon['data'], None, icon['path']))
    f.write('};\n\n__attribute__((aligned(16))) static const u16 icon_palettes[] = {\n')
    for p in palettes:
        f.write(ci4tool.palette_to_c(p))
    f.write('};\n\nstatic const Gfx icon_tile_setup_dls[] = {\n')
    bi = 0
    while bi < len(all_icons):
        f.write('    gsDPLoadSync(),\n')
        f.write('    gsDPLoadBlock(7, 0, 0, ((ICON_SIZE*ICON_SIZE*ICONS_PER_GROUP+3)>>2)-1,\n')
        f.write('        G_DXT(G_IM_SIZ_4b, ICON_SIZE)),\n')
        f.write('    gsDPPipeSync(),\n')
        for t in range(4):
            if bi >= len(all_icons): break
            p = all_icons[bi]['plt']
            f.write('    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, ((((ICON_SIZE)>>1)+7)>>3),\n')
            f.write('        ' + str(t) + '*(ICON_SIZE*ICON_SIZE)/16, ' + str(t) + ', ' + str(p) + ', 0, 0, 0, 0, 5, 0),\n')
            #f.write('    gsDPSetTileSize(' + str(t) + ', 0, 0, (ICON_SIZE-1)<<G_TEXTURE_IMAGE_FRAC,\n')
            #f.write('        (ICON_SIZE-1)<<G_TEXTURE_IMAGE_FRAC),\n')
            bi += 1
        f.write('    gsSPEndDisplayList(),\n')
    f.write('};\n\n')
