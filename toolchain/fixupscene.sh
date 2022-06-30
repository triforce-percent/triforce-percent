scenename=$(pwd | sed -r 's|.*assets/scenes/[^/]+/([^/]+)/?|\1|g')
echo "Scene ${scenename}"

cat ${scenename}_scene.c ${scenename}_room_*.c > temp1.c
sed -i 's|#include ".*\.h"||g' temp1.c
cpp -I ../../../../ -I ../../../../build/ temp1.c -o ${scenename}.i
sed -i 's|#.*||g' ${scenename}.i
rm temp1.c

parent=
while read -r line; do
    if [[ "$line" == *"Gfx "* ]]; then
        parent=$(echo $line | sed -r 's|.*Gfx (\w+DL_\w+)\[\].*|\1|g')
    fi
    if [ -z "$parent" ]; then continue; fi
    if [[ "$line" == *"gsDPPipeSync"* ]]; then
        echo "$parent"
        parent=
    fi
    if [[ "$line" == *"gsSPDisplayList"* || "$line" == *"gsSPBranchLessZraw"* ]]; then
        echo "                        Ignoring DL $parent with calls to other DLs"
        parent=
    fi
done < ${scenename}.i
exit 0

parent=
newparent=
printedparent=
while read -r line; do
    if [[ "$line" == *"Gfx "* ]]; then
        newparent=$(echo $line | sed -r 's|.*(room_\w+)DL.*|\1|g')
        printedparent=
    fi
    if [[ "$line" == *"gsDPPipeSync"* ]]; then
        newparent=
    fi
    if [[ "$line" == *"gsSPDisplayList"* && "$newparent" == *"room"* ]]; then
        child=$(echo $line | sed -r 's|.*\((\w+)\).*|\1|g')
        if [ -z "$printedparent" ]; then
            if [[ "$newparent" == "$parent" ]]; then
                layer="transparent"
            else
                layer="opaque"
            fi
            parent="$newparent"
            echo "$parent $layer:"
            printedparent=1
        fi
        echo "    $child"
    fi
done < ${scenename}.i
