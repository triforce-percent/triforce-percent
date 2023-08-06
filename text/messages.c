// 0x900: Debugging

DECLARE_MESSAGE(0x0901, BOX_BLUE, POS_MIDDLE,
    UNSKIPPABLE ITEM_ICON("\x35") QUICKTEXT_ENABLE 
    "Frog"
)

DECLARE_MESSAGE(0x0910, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "Is mayonnaise an instrument?"
)

DECLARE_MESSAGE(0x0920, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "magfest is sus"
)

// 0xB00: Key of Courage

DECLARE_MESSAGE(0x0B10, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "Oh um. Are you looking for bugs," NEWLINE
    "too? I love bugs! But I can't" NEWLINE
    "find any. How's your luck?"
)

DECLARE_MESSAGE(0x0B11, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "What is that? I asked you for a" NEWLINE
    "bug!"
)

DECLARE_MESSAGE(0x0B12, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "No, no! These are crawlies!" NEWLINE
    "Crawlies are dumb. I want a flying" NEWLINE
    "bug. You know, colorful, with wings." BOX_BREAK UNSKIPPABLE
    "They like flowers, so you might" NEWLINE
    "find one somewhere people grow lots" NEWLINE
    "of different kinds of flowers."
)

DECLARE_MESSAGE(0x0B13, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "Wow, you actually brought it!" NEWLINE
    QUICKTEXT_ENABLE "Thanks!" QUICKTEXT_DISABLE BOX_BREAK UNSKIPPABLE
    "You're a nice guy, unlike that Mido..." NEWLINE
    "He never talks to me. Except one" NEWLINE
    "time he gave me this, and ordered" NEWLINE
    "me to keep it safe." BOX_BREAK UNSKIPPABLE
    "But I don't really want it... You can" NEWLINE
    "have it!"
)

DECLARE_MESSAGE(0x0004, BOX_BLUE, POS_MIDDLE,
    UNSKIPPABLE ITEM_ICON("\x31") QUICKTEXT_ENABLE "You got the " COLOR(RED) "Magic Powder" COLOR(WHITE) "!" QUICKTEXT_DISABLE NEWLINE
    "It smells like mushrooms."
)

DECLARE_MESSAGE(0x0B15, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "I don't think you can use it by" NEWLINE
    "yourself, though..."
)

DECLARE_MESSAGE(0x0B16, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "Thanks for bringing me that bug!"
)

DECLARE_MESSAGE(0x009C, BOX_BLACK, POS_VARIABLE,
    UNSKIPPABLE
    "What's that? You're lookin' for a" NEWLINE
    "flyin' bug?" BOX_BREAK UNSKIPPABLE
    "I usually don' carry anything like" NEWLINE
    "that, but my kid has been catchin'" NEWLINE
    "a lot of 'em lately." BOX_BREAK UNSKIPPABLE
    "He always leaves some around, and" NEWLINE
    "I bet he'll be happy to know he" NEWLINE
    "helped his old man make a sale!" NEWLINE
    TEXT_SPEED("\x02") 
    QUICKTEXT_ENABLE "Har" QUICKTEXT_DISABLE " " 
    QUICKTEXT_ENABLE "har" QUICKTEXT_DISABLE " " 
    QUICKTEXT_ENABLE "har" QUICKTEXT_DISABLE "!" 
    TEXT_SPEED("\x00") BOX_BREAK UNSKIPPABLE
    "Lemme put one out for ya." EVENT
)

DECLARE_MESSAGE(0x0B28, BOX_BLACK, POS_MIDDLE,
    QUICKTEXT_ENABLE  COLOR(RED) "Butterfly   35 Rupees" NEWLINE
    COLOR(WHITE) "This is a beautiful red and" NEWLINE
    "yellow butterfly. You can keep it" NEWLINE
    "in one of your bottles." QUICKTEXT_DISABLE PERSISTENT
)

DECLARE_MESSAGE(0x0B29, BOX_BLACK, POS_MIDDLE,
    QUICKTEXT_ENABLE "Butterfly   35 Rupees" QUICKTEXT_DISABLE NEWLINE
    NEWLINE TWO_CHOICE COLOR(GREEN) "Buy" NEWLINE
    "Don't buy" COLOR(WHITE)
)

DECLARE_MESSAGE(0x00F9, BOX_BLUE, POS_MIDDLE,
    UNSKIPPABLE ITEM_ICON("\x1E") QUICKTEXT_ENABLE "You got a " COLOR(RED) "Butterfly" COLOR(WHITE) "!" QUICKTEXT_DISABLE NEWLINE
    "Bug enthusiasts love these!"
)

DECLARE_MESSAGE(0x0B30, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "Hey, Kokiri! I smell something" NEWLINE
    "on you..." BOX_BREAK UNSKIPPABLE
    "That smells like my " COLOR(RED) "Magic Powder" COLOR(WHITE) "." NEWLINE
    QUICKTEXT_ENABLE "Give it back!" QUICKTEXT_DISABLE NEWLINE
    TWO_CHOICE COLOR(GREEN) "Yes" NEWLINE
    "No"
)

DECLARE_MESSAGE(0x0B31, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "You're as bad as that other" NEWLINE
    "Kokiri kid!"
)

DECLARE_MESSAGE(0x0B32, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "I knew it, it's my " COLOR(RED) "Magic Powder" COLOR(WHITE) "!" BOX_BREAK UNSKIPPABLE
    "That other nasty Kokiri kid stole" NEWLINE
    "it from me. He said that because" NEWLINE
    "it's made of forest mushrooms," NEWLINE
    "it's his property." BOX_BREAK UNSKIPPABLE
    "The nerve he had! Who made him" NEWLINE
    "the owner of the forest?!" BOX_BREAK UNSKIPPABLE
    "I plucked those mushrooms, dried" NEWLINE
    "them, and mashed them myself!" BOX_BREAK UNSKIPPABLE
    SHIFT("\x40") "grumble..." BOX_BREAK UNSKIPPABLE
    "Anyway, it's not your fault." NEWLINE
    "Thank you for bringing it back." BOX_BREAK UNSKIPPABLE
    "As a reward, I'll use this powder" NEWLINE
    "on your masks to make them more" NEWLINE
    "powerful!"
)

DECLARE_MESSAGE(0x0B33, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "If you have any masks, show them" NEWLINE
    "to me!"
)

DECLARE_MESSAGE(0x0B34, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "Let me sprinkle some of this" NEWLINE
    COLOR(RED) "Magic Powder" COLOR(WHITE) " on that mask!"
)

DECLARE_MESSAGE(0x0013, BOX_BLUE, POS_MIDDLE,
    UNSKIPPABLE ITEM_ICON("\x27") QUICKTEXT_ENABLE "You upgraded the " COLOR(RED) "Bunny Hood" COLOR(WHITE) "!" QUICKTEXT_DISABLE NEWLINE
    "The magic in its long ears" NEWLINE
    "allows the wearer to run" NEWLINE
    "with great speed."
)

DECLARE_MESSAGE(0x0016, BOX_BLUE, POS_MIDDLE,
    UNSKIPPABLE ITEM_ICON("\x2A") QUICKTEXT_ENABLE "You upgraded the " COLOR(RED) "Gerudo Mask" COLOR(WHITE) "!" QUICKTEXT_DISABLE NEWLINE
    "Now you can charm people with" NEWLINE
    "the perfect lady's disguise..." NEWLINE
    "even Gerudo themselves!"
)

DECLARE_MESSAGE(0x0B40, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "A Gerudo child far from the desert?" NEWLINE
    "My! Your father must be Hylian." BOX_BREAK UNSKIPPABLE
    "Is this your first time visiting?" NEWLINE
    "Come in and greet your Gerudo" NEWLINE
    "sisters!"
)

DECLARE_MESSAGE(0x0B50, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "So you come from outside? I bet" NEWLINE
    "you had bountiful crops out there." BOX_BREAK UNSKIPPABLE
    "Heh, here not even cacti bloom in" NEWLINE
    "this desert."
)

DECLARE_MESSAGE(0x0B51, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "Our fortress seems to be smaller" NEWLINE
    "every day." BOX_BREAK UNSKIPPABLE
    "Someday, I suppose there'll be" NEWLINE
    "nothing left but desert."
)

DECLARE_MESSAGE(0x0B52, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "The Royal Family of Hyrule has" NEWLINE
    "forsaken our people. They are" NEWLINE
    "leaving us with no other option" NEWLINE
    "than to fight!"
)

DECLARE_MESSAGE(0x0B53, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "Oh, child. I pity you. Soon, you" NEWLINE
    "will have to pick a side."
)

DECLARE_MESSAGE(0x0B60, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "Hm? A kid?" NEWLINE
    "What are you doing here?" BOX_BREAK UNSKIPPABLE
    "Did your mother send you here to" NEWLINE
    "meet the great Nabooru?" BOX_BREAK UNSKIPPABLE
    "How nice of her. I'm pleased she" NEWLINE
    "wishes her child to know of her" NEWLINE
    "Gerudo origins." BOX_BREAK UNSKIPPABLE
    QUICKTEXT_ENABLE "Very well!" QUICKTEXT_DISABLE EVENT
)
    
DECLARE_MESSAGE(0x0B61, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "Guards, you may leave the girl" NEWLINE
    "and I alone." EVENT
)

DECLARE_MESSAGE(0x0B62, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "Well, enough acting, " TEXT_SPEED("\x03") "boy" TEXT_SPEED("\x00") ". Yes, I" NEWLINE
    "can see through your disguise." EVENT
)

DECLARE_MESSAGE(0x0B63, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "A Hylian child pretending to be a" NEWLINE
    "Gerudo. I admire your courage, but" NEWLINE
    "how will this help you in stopping" NEWLINE
    "the great Ganondorf?" BOX_BREAK UNSKIPPABLE
    "That is what you want, isn't it?" EVENT
)

DECLARE_MESSAGE(0x0B64, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "You may think I'm your enemy," NEWLINE
    "being a Gerudo like him." BOX_BREAK UNSKIPPABLE
    "The truth is, that man is as much" NEWLINE
    "against our kind as he is against" NEWLINE
    "yours." BOX_BREAK UNSKIPPABLE
    "The power of the Goddesses is all" NEWLINE
    "he desires, even if that means" NEWLINE
    "betraying us all." EVENT
)

DECLARE_MESSAGE(0x0B65, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "But while your goal is admirable," NEWLINE
    "you're still a child. No kid will" NEWLINE
    "stop Ganondorf." BOX_BREAK UNSKIPPABLE
    "An adult with your courage," NEWLINE
    "however..." EVENT
)

DECLARE_MESSAGE(0x0B66, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "Ages ago, the Gerudo created a" NEWLINE
    "melody known as the " COLOR(BLUE) "Song of Time" COLOR(WHITE) "." NEWLINE
    "It is such powerful magic that it" NEWLINE
    "was divided into two halves." BOX_BREAK UNSKIPPABLE
    "The first half was granted to the" NEWLINE
    "Royal Family, while the second" NEWLINE
    "half remained in this land."
)

//  "text text text text text text te"
DECLARE_MESSAGE(0x0B67, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "Do you know what lies beyond the" NEWLINE
    "desert?" BOX_BREAK_DELAYED("\x38") UNSKIPPABLE
    "There's a place there known as the" NEWLINE
    COLOR(YELLOW) "Desert Colossus" COLOR(WHITE) "." BOX_BREAK_DELAYED("\x38") UNSKIPPABLE
    "We Gerudo have used it as a temple" NEWLINE
    "for generations, but it was built" NEWLINE
    "by the ancient Sages." BOX_BREAK_DELAYED("\x38") UNSKIPPABLE
    "It is a two-sided dungeon made for" NEWLINE
    "a time-traveling Hero who can go" NEWLINE
    "from child to adult and back." FADE("\x38")
)

//  "text text text text text text te"
DECLARE_MESSAGE(0x0B68, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "As I said, you're just a kid now." NEWLINE
    "But I sense that you can control" NEWLINE
    "even greater magic than just that" NEWLINE
    "mask."
)

DECLARE_MESSAGE(0x0B69, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "If you're truly who I think you" NEWLINE
    "are, I can teach you both halves" NEWLINE
    "of the " COLOR(BLUE) "Song of Time" COLOR(WHITE) "." BOX_BREAK UNSKIPPABLE
    "By playing it, you'll be able to" NEWLINE
    "overcome the trials of the " COLOR(YELLOW) "Desert" NEWLINE
    "Colossus" COLOR(WHITE) "..." BOX_BREAK UNSKIPPABLE
    "...and you'll become a man who" NEWLINE
    "can stand against Ganondorf."
)

DECLARE_MESSAGE(0x0B6A, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "Is this really what you want?" NEWLINE
    NEWLINE
    TWO_CHOICE COLOR(GREEN) "Yes" NEWLINE
    "No"
)

DECLARE_MESSAGE(0x0B6B, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "Come now, I know you want to" NEWLINE
    "stop Ganondorf." EVENT
)

DECLARE_MESSAGE(0x0B6C, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "All right, listen well!"
)

DECLARE_MESSAGE(0x087A, BOX_OCARINA, POS_VARIABLE,
    QUICKTEXT_ENABLE SHIFT("\x0E") "This is the " COLOR(BLUE) "full Song of Time" COLOR(WHITE) "..." NEWLINE
    NEWLINE
    NEWLINE
    QUICKTEXT_DISABLE OCARINA
)

DECLARE_MESSAGE(0x089D, BOX_OCARINA, POS_VARIABLE,
    QUICKTEXT_ENABLE  SHIFT("\x08") "You played the " COLOR(BLUE) "full Song of Time" COLOR(WHITE) "." NEWLINE
    NEWLINE
    NEWLINE
    QUICKTEXT_DISABLE
)

DECLARE_MESSAGE(0x00D5, BOX_BLUE, POS_MIDDLE,
    UNSKIPPABLE
    SHIFT("\x28") "You've learned the" NEWLINE 
    SHIFT("\x29") COLOR(BLUE) "full Song of Time" COLOR(WHITE) "!" BOX_BREAK UNSKIPPABLE
    "This song is proof of a true Hero's" NEWLINE
    "courage." BOX_BREAK UNSKIPPABLE
    "Play it as a child to become an" NEWLINE
    "adult, and as an adult to become" NEWLINE
    "a child."
)

DECLARE_MESSAGE(0x0B6D, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "I'll see you again in a few years!"
)


// 0xC00: Key of Power

DECLARE_MESSAGE(0x0C10, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "Whaaaat?! Impossible!" BOX_BREAK UNSKIPPABLE
    "I'm the fastest man in Hyrule!" NEWLINE
    "How did you get here before I did?!" EVENT
)

DECLARE_MESSAGE(0x0C11, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "Ahem, sorry about that!" NEWLINE
    "What I mean is that you're" NEWLINE
    "extraordinary!" BOX_BREAK UNSKIPPABLE
    "Meet me in the middle of Hyrule" NEWLINE
    "Field to get a " COLOR(RED) "special reward" COLOR(WHITE) "!"
)

DECLARE_MESSAGE(0x0C20, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    COLOR(RED) "You " QUICKTEXT_ENABLE "FOOL!" 
    QUICKTEXT_DISABLE COLOR(WHITE) FADE("\x20")
)

DECLARE_MESSAGE(0x0C21, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    COLOR(RED) "This is the only reward" NEWLINE
    "cheaters like you get!" FADE("\x20")
)

DECLARE_MESSAGE(0x0C30, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "huff... huff..." BOX_BREAK UNSKIPPABLE
    "I guess you're a better cheater" NEWLINE
    "than I am..." BOX_BREAK UNSKIPPABLE
    "I never thought anyone would" NEWLINE
    "find a power like the one I did," NEWLINE
    "seven years ago..." EVENT
)

DECLARE_MESSAGE(0x0C31, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "That day, after Hyrule Castle" NEWLINE
    "was attacked, I went on my usual" NEWLINE
    "running route to clear my mind." BOX_BREAK UNSKIPPABLE
    "Somewhere out in the field here," NEWLINE
    "I stepped on this object, lying" NEWLINE
    "on the ground." BOX_BREAK UNSKIPPABLE
    "It must have been dropped by" NEWLINE
    "someone fleeing town." EVENT
)

DECLARE_MESSAGE(0x0C32, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "It was a golden locket. I tried it" NEWLINE
    "on and felt this rush all over my" NEWLINE
    "body!" BOX_BREAK UNSKIPPABLE
    "I could run faster than I could" NEWLINE
    "ever imagine. In fact, I could run" NEWLINE
    "faster than light!" BOX_BREAK UNSKIPPABLE
    "That's how I was able to finish" NEWLINE
    "the race before I started, and" NEWLINE
    "how I was just fighting you." EVENT
)

DECLARE_MESSAGE(0x0C33, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "But I now realize this has made" NEWLINE
    "me a terrible man." BOX_BREAK UNSKIPPABLE
    "I wanted to be the fastest so" NEWLINE
    "badly I tried to kill you!" BOX_BREAK UNSKIPPABLE
    SHIFT("\x48") "sniffle..." EVENT
)

DECLARE_MESSAGE(0x0C34, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "I just want to be my own self" NEWLINE
    "again, to run free in the wild." NEWLINE
    "I don't care about the magic" NEWLINE
    "anymore." BOX_BREAK UNSKIPPABLE
    "Here, you can have this."
)

DECLARE_MESSAGE(0x0068, BOX_BLUE, POS_MIDDLE,
    UNSKIPPABLE  ITEM_ICON("\x6F")  QUICKTEXT_ENABLE 
    "You obtained the " COLOR(LIGHTBLUE) "Sages' Charm" COLOR(WHITE) "!" QUICKTEXT_DISABLE NEWLINE
    "This locket amplifies and" NEWLINE
    "enhances the magic power" NEWLINE
    "of its wearer." BOX_BREAK UNSKIPPABLE ITEM_ICON("\x6F")
    "Equip the Sages' offerings" NEWLINE
    "to channel their power" NEWLINE
    "yourself!"
)


// 0xD00: Key of Wisdom

DECLARE_MESSAGE(0x0D20, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "Welcome Link!" NEWLINE
    "I am the " COLOR(LIGHTBLUE) "Great Fairy of Wisdom" COLOR(WHITE) "." BOX_BREAK UNSKIPPABLE
    "For ages, I've offered guidance to" NEWLINE
    "those who seek enlightenment." NEWLINE
    "This, too, is why you're here."
)

DECLARE_MESSAGE(0x0D21, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "You have almost reached the end of" NEWLINE
    "your journey, but to prove your" NEWLINE
    "spirit's growth, you must allow the" NEWLINE
    COLOR(LIGHTBLUE) "wisdom of the Sages" COLOR(WHITE) " to guide you." BOX_BREAK UNSKIPPABLE
    COLOR(LIGHTBLUE) "This song" COLOR(WHITE) " is proof of that virtue," NEWLINE
    "and the final key to the Sacred" NEWLINE
    "Realm."
)

DECLARE_MESSAGE(0x086D, BOX_OCARINA, POS_VARIABLE,
    QUICKTEXT_ENABLE SHIFT("\x11") "Play using " COLOR(BLUE) "\x9F" COLOR(WHITE) " and " COLOR(YELLOW) "\xA1" COLOR(WHITE) "." NEWLINE
    NEWLINE
    NEWLINE
    QUICKTEXT_DISABLE OCARINA
)

DECLARE_MESSAGE(0x0871, BOX_OCARINA, POS_VARIABLE,
    QUICKTEXT_ENABLE SHIFT("\x11") "Play the " COLOR(LIGHTBLUE) "Overture of Sages" COLOR(WHITE) "!" NEWLINE
    NEWLINE
    NEWLINE
    QUICKTEXT_DISABLE OCARINA
)

DECLARE_MESSAGE(0x0074, BOX_BLUE, POS_MIDDLE,
    UNSKIPPABLE  
    SHIFT("\x28") "You have learned the" NEWLINE
    SHIFT("\x29") COLOR(LIGHTBLUE) "Overture of Sages" COLOR(WHITE) "!!"
)

DECLARE_MESSAGE(0x0894, BOX_OCARINA, POS_VARIABLE,
    QUICKTEXT_ENABLE SHIFT("\x01") "You played the " COLOR(LIGHTBLUE) "Overture of Sages" COLOR(WHITE) "." NEWLINE
    NEWLINE
    NEWLINE
    QUICKTEXT_DISABLE
)

DECLARE_MESSAGE(0x088E, BOX_BLACK, POS_MIDDLE,
    COLOR(LIGHTBLUE) TEXT_SPEED("\x01") 
    "Warp to the Sacred Realm?"
    TEXT_SPEED("\x00") COLOR(WHITE) NEWLINE NEWLINE
    TWO_CHOICE COLOR(GREEN) "OK" NEWLINE
    "No" COLOR(WHITE)
)

DECLARE_MESSAGE(0x0D23, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "Play this song before the blade of" NEWLINE
    "destiny, and the path of the Sages" NEWLINE
    "shall be revealed."
)

DECLARE_MESSAGE(0x0D30, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE QUICKTEXT_ENABLE COLOR(RED)
    SHIFT("\x1D") "You can't warp here!" FADE("\x46")
)

// 0xA00: Chamber of Sages / Triforce

DECLARE_MESSAGE(0x0A10, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "Welcome, Link. I'm Rauru, the" NEWLINE
    "ancient Sage of Light." BOX_BREAK UNSKIPPABLE
    "Now that you hold the keys to the" NEWLINE
    "three sacred virtues, your heart" NEWLINE
    "is in perfect balance."
)

DECLARE_MESSAGE(0x0A11, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "The song you just played has" NEWLINE
    "awakened the other Sages, and they" NEWLINE
    "are on their way to joining us here." BOX_BREAK UNSKIPPABLE
    "You must receive a blessing from" NEWLINE
    "each of us." BOX_BREAK UNSKIPPABLE
    "Together, we will open the way to" NEWLINE
    "your goal!"
)

DECLARE_MESSAGE(0x0A20, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "Link, the promise I made to you" NEWLINE
    "stays true. I will always be your" NEWLINE
    "friend."
)

DECLARE_MESSAGE(0x0A30, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "The bond between the Goron race" NEWLINE
    "and the Royal Family is rock solid!" NEWLINE
    "Let's go, brother!"
)

DECLARE_MESSAGE(0x0A40, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "I knew the hero would turn out" NEWLINE
    "to be a handsome man!" BOX_BREAK UNSKIPPABLE
    "Once this is all over, you must" NEWLINE
    "come visit me, all right?"
)

DECLARE_MESSAGE(0x0A50, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "Nice work! It looks like our" NEWLINE
    "song worked for you." BOX_BREAK UNSKIPPABLE
    "From all the Gerudos," NEWLINE
    "you have our support!"
)

DECLARE_MESSAGE(0x0A60, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "Undoubtedly, you are the boy" NEWLINE
    "from the forest who appeared" NEWLINE
    "in Princess Zelda's dreams." BOX_BREAK UNSKIPPABLE
    "I am glad my charm found its" NEWLINE
    "way into your hands." BOX_BREAK UNSKIPPABLE
    "I wish you well in fulfilling the" NEWLINE
    "great destiny that is before you."
)

DECLARE_MESSAGE(0x0A70, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "Link, the great Hero of Time..." BOX_BREAK UNSKIPPABLE
    "The one with the three virtues of" NEWLINE
    "Courage, Power, and Wisdom in" NEWLINE
    "balance in your heart..." BOX_BREAK UNSKIPPABLE
    "The one with the ability to bend" NEWLINE
    "and shift time itself..."
)

DECLARE_MESSAGE(0x0A71, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "In this reality, we have only" NEWLINE
    "just met." BOX_BREAK UNSKIPPABLE
    "Yet we have known each other in" NEWLINE
    "ages past, and surely in other" NEWLINE
    "timelines of the present." BOX_BREAK UNSKIPPABLE
    "I sense that our destiny is about" NEWLINE
    "to change forever." BOX_BREAK UNSKIPPABLE
    "But I trust that you'll always use" NEWLINE
    "your strengths to protect Hyrule."
)

DECLARE_MESSAGE(0x0A72, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "Are you ready, Link?" NEWLINE
    NEWLINE
    TWO_CHOICE COLOR(GREEN) "Are you Zelda?" NEWLINE
    "Are you a boy or a girl?"
)

DECLARE_MESSAGE(0x0A73, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "I guess that hasn't been much of" NEWLINE
    "a secret since " COLOR(LIGHTBLUE) "Melee" COLOR(WHITE) ", huh?" EVENT
)

DECLARE_MESSAGE(0x0A74, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "Would be nice if I could get my" NEWLINE
    "own game someday..."
)

DECLARE_MESSAGE(0x0A75, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "Link, this isn't the time for" NEWLINE
    "nonsense!" EVENT
)

DECLARE_MESSAGE(0x0A76, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "O-of course I-I'm a boy..."
)

DECLARE_MESSAGE(0x0A77, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE
    "Let's not keep everyone waiting!"
)

DECLARE_MESSAGE(0x0ACE, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE ITEM_ICON("\x73") QUICKTEXT_ENABLE
    "You got the " COLOR(YELLOW) "Triforce" COLOR(WHITE) "!!!" QUICKTEXT_DISABLE NEWLINE
    "After 23 years, the dreams of" NEWLINE
    "millions of players around the" NEWLINE
    "world have finally come true!"
)

// 0xE00: Finale

DECLARE_MESSAGE(0x0E00, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE COLOR(YELLOW) TEXT_SPEED("\x02")
    SHIFT("\x4F") "Link..." FADE("\x18")
)

DECLARE_MESSAGE(0x0E01, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE COLOR(YELLOW) TEXT_SPEED("\x01")
    SHIFT("\x52") "Link." FADE("\x28")
)

DECLARE_MESSAGE(0x0E02, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE COLOR(YELLOW) TEXT_SPEED("\x01")
    "It is we, the Golden Goddesses"  NEWLINE
    "of the Triforce:" NEWLINE
    "Din, Nayru, and Farore..." FADE("\x38")
)

DECLARE_MESSAGE(0x0E03, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE COLOR(YELLOW) TEXT_SPEED("\x01")
    "You have done well to arrive" NEWLINE
    "here, and your heart is in" NEWLINE
    "balance..." FADE("\x38")
)

DECLARE_MESSAGE(0x0E04, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE COLOR(YELLOW) TEXT_SPEED("\x01")
    "You are now the master of the" NEWLINE
    "complete Triforce..." FADE("\x38")
)

DECLARE_MESSAGE(0x0E05, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE COLOR(YELLOW) TEXT_SPEED("\x01")
    "The True Force stirs within you..." FADE("\x38")
)

DECLARE_MESSAGE(0x0E06, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE COLOR(YELLOW) TEXT_SPEED("\x01")
    "Now, Link... What do you wish for?" NEWLINE TEXT_SPEED("\x00")
    THREE_CHOICE COLOR(GREEN) "Be King of Hyrule" NEWLINE
    "Rupees" NEWLINE
    "See the future"
)

DECLARE_MESSAGE(0x0E07, BOX_BLACK, POS_MIDDLE,
    UNSKIPPABLE COLOR(YELLOW) TEXT_SPEED("\x01")
    SHIFT("\x13") "Your wish has been granted." FADE("\x46")
)

DECLARE_MESSAGE(0x0E10, BOX_NONE_BOTTOM, POS_VARIABLE,
    UNSKIPPABLE QUICKTEXT_ENABLE
    SHIFT("\x50") "Link..." FADE("\x1C")
)

DECLARE_MESSAGE(0x0E11, BOX_NONE_BOTTOM, POS_VARIABLE,
    UNSKIPPABLE QUICKTEXT_ENABLE
    SHIFT("\x04") "It seems you've managed to bring" NEWLINE
    SHIFT("\x01") "together a great number of people." FADE("\x53")
)

DECLARE_MESSAGE(0x0E12, BOX_NONE_BOTTOM, POS_VARIABLE,
    UNSKIPPABLE QUICKTEXT_ENABLE
    SHIFT("\x1A") "I'm so happy to see this." FADE("\x2C")
)

DECLARE_MESSAGE(0x0E13, BOX_NONE_BOTTOM, POS_VARIABLE,
    UNSKIPPABLE QUICKTEXT_ENABLE
    SHIFT("\x0C") "I know they're out there, but it" NEWLINE
                  "would be nice if we could see them," NEWLINE
    SHIFT("\x38") "don't you think?" FADE("\x75")
)

DECLARE_MESSAGE(0x0E14, BOX_BLUE, POS_TOP,
    UNSKIPPABLE COLOR(LIGHTBLUE)
    SHIFT("\x49") "Everyone!" NEWLINE
    SHIFT("\x08") "Type " COLOR(YELLOW) "Here together" COLOR(LIGHTBLUE) " in the chat!" NEWLINE
    SHIFT("\x55") "Now!"
)

DECLARE_MESSAGE(0x0E15, BOX_NONE_BOTTOM, POS_VARIABLE,
    UNSKIPPABLE QUICKTEXT_ENABLE
    SHIFT("\x50") "Look!" FADE("\x12")
)

DECLARE_MESSAGE(0x0E16, BOX_NONE_BOTTOM, POS_VARIABLE,
    UNSKIPPABLE QUICKTEXT_ENABLE
    SHIFT("\x08") "You asked to see our future?" FADE("\x25")
)

DECLARE_MESSAGE(0x0E17, BOX_NONE_BOTTOM, POS_VARIABLE,
    UNSKIPPABLE QUICKTEXT_ENABLE
    SHIFT("\x40") "Here it is." FADE("\x1A")
)

DECLARE_MESSAGE(0x0E18, BOX_NONE_BOTTOM, POS_VARIABLE,
    UNSKIPPABLE QUICKTEXT_ENABLE
    SHIFT("\x38") "Thank you, Link," NEWLINE
    SHIFT("\x18") "for all you have done for us." FADE("\x51")
)

DECLARE_MESSAGE(0x0E20, BOX_NONE_BOTTOM, POS_VARIABLE,
    UNSKIPPABLE QUICKTEXT_ENABLE
    SHIFT("\x2C") "Thank you, Zelda." FADE("\x23")
)

DECLARE_MESSAGE(0x0E21, BOX_NONE_BOTTOM, POS_VARIABLE,
    UNSKIPPABLE QUICKTEXT_ENABLE
    SHIFT("\x1C") "Let us create the future," NEWLINE
    SHIFT("\x4C") "together." FADE("\x3B")
)

// 0xF00: Staff Roll

DECLARE_MESSAGE(0x0F00, BOX_CREDITS, POS_VARIABLE,
    QUICKTEXT_ENABLE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x43") "TRIFORCE%" NEWLINE NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x2B") "OoT ACE Showcase" 
    QUICKTEXT_DISABLE FADE2("\x00\x3A")
)

DECLARE_MESSAGE(0x0F01, BOX_CREDITS, POS_VARIABLE,
    QUICKTEXT_ENABLE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x28") "Director" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x46") "SAURAEN" NEWLINE NEWLINE NEWLINE
    NEWLINE
    SHIFT("\x24") SHIFT("\x28") "RTA Speedrunner" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x46") "SAVESTATE"
    QUICKTEXT_DISABLE FADE2("\x00\x3A")
)

DECLARE_MESSAGE(0x0F02, BOX_CREDITS, POS_VARIABLE,
    QUICKTEXT_ENABLE NEWLINE NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x18") "Scenario" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "SAURAEN" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "REBECCAETRIPP" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "TERUSTHEBIRD" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "DWANGOAC"
    QUICKTEXT_DISABLE FADE2("\x00\x3A")
)

DECLARE_MESSAGE(0x0F10, BOX_CREDITS, POS_VARIABLE,
    QUICKTEXT_ENABLE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x3E") "ASSET UNIT" NEWLINE NEWLINE NEWLINE NEWLINE
    NEWLINE
    SHIFT("\x24") SHIFT("\x18") "Scene Design" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "CDI-FAILS" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "ZEL" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "SAURAEN"
    QUICKTEXT_DISABLE FADE2("\x00\x3A")
)

DECLARE_MESSAGE(0x0F11, BOX_CREDITS, POS_VARIABLE,
    QUICKTEXT_ENABLE NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x18") "Music" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "SAURAEN" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "REBECCAETRIPP" NEWLINE NEWLINE NEWLINE
    NEWLINE
    SHIFT("\x24") SHIFT("\x18") "Screen Text" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "KIM-SUKLEY" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "SAURAEN"
    QUICKTEXT_DISABLE FADE2("\x00\x3A")
)

DECLARE_MESSAGE(0x0F20, BOX_CREDITS, POS_VARIABLE,
    QUICKTEXT_ENABLE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x18") "Cinema Scenes" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "SAURAEN" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "DWANGOAC" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "DEFENESAM" NEWLINE NEWLINE NEWLINE
    NEWLINE
    SHIFT("\x24") SHIFT("\x18") "BotW Model Conversion" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "ALI1234" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "SAURAEN"
    QUICKTEXT_DISABLE FADE2("\x00\x3A")
)

DECLARE_MESSAGE(0x0F21, BOX_CREDITS, POS_VARIABLE,
    QUICKTEXT_ENABLE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x18") "Animation" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "UNESAG" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "SAURAEN" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "RANKAISIJA" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "AEROARTWORK"
    QUICKTEXT_DISABLE FADE2("\x00\x3A")
)

DECLARE_MESSAGE(0x0F30, BOX_CREDITS, POS_VARIABLE,
    QUICKTEXT_ENABLE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x18") "Zelda (English Voice)" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "SAOIRSE" NEWLINE NEWLINE NEWLINE
    NEWLINE
    SHIFT("\x24") SHIFT("\x18") "Link (Japanese Voice)" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "ZERO" NEWLINE NEWLINE NEWLINE
    NEWLINE
    SHIFT("\x24") SHIFT("\x18") "Translator" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "YUKLOJ"
    QUICKTEXT_DISABLE FADE2("\x00\x3A")
)

DECLARE_MESSAGE(0x0F31, BOX_CREDITS, POS_VARIABLE,
    QUICKTEXT_ENABLE NEWLINE NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x18") "Textures" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "CDI-FAILS" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "KIM-SUKLEY" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "ZEL" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "SAURAEN"
    QUICKTEXT_DISABLE FADE2("\x00\x3A")
)

DECLARE_MESSAGE(0x0F40, BOX_CREDITS, POS_VARIABLE,
    QUICKTEXT_ENABLE NEWLINE
    SHIFT("\x24") SHIFT("\x32") "PROGRAM UNIT" NEWLINE NEWLINE NEWLINE NEWLINE
    NEWLINE
    SHIFT("\x24") SHIFT("\x18") "Actor Program" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "SAURAEN" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "RANKAISIJA" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "Z64ME" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "MNGOLDENEAGLE" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "ZEL"
    QUICKTEXT_DISABLE FADE2("\x00\x3A")
)

DECLARE_MESSAGE(0x0F41, BOX_CREDITS, POS_VARIABLE,
    QUICKTEXT_ENABLE NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x18") "Game / Actor Patches" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "SAURAEN" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "MNGOLDENEAGLE" NEWLINE NEWLINE NEWLINE
    NEWLINE
    SHIFT("\x24") SHIFT("\x18") "System Patches" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "SAURAEN" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "ZEL"
    QUICKTEXT_DISABLE FADE2("\x00\x3A")
)

DECLARE_MESSAGE(0x0F50, BOX_CREDITS, POS_VARIABLE,
    QUICKTEXT_ENABLE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x28") "Cel Shading" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x46") "SAURAEN" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x46") "GLANK"
    QUICKTEXT_DISABLE FADE2("\x00\x3A")
)

DECLARE_MESSAGE(0x0F51, BOX_CREDITS, POS_VARIABLE,
    QUICKTEXT_ENABLE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x28") "Bootstrapper Chain" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x46") "SAURAEN" NEWLINE NEWLINE NEWLINE
    NEWLINE
    SHIFT("\x24") SHIFT("\x28") "Hyperspeed Loader" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x46") "TERUSTHEBIRD" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x46") "SAURAEN"
    QUICKTEXT_DISABLE FADE2("\x00\x3A")
)

DECLARE_MESSAGE(0x0F60, BOX_CREDITS, POS_VARIABLE,
    QUICKTEXT_ENABLE NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x18") "Host Frontend" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "SAURAEN" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "THEMAS3212" NEWLINE NEWLINE NEWLINE
    NEWLINE
    SHIFT("\x24") SHIFT("\x18") "TAStm32 Firmware" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "OWNASAURUS" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "SAURAEN"
    QUICKTEXT_DISABLE FADE2("\x00\x3A")
)

DECLARE_MESSAGE(0x0F61, BOX_CREDITS, POS_VARIABLE,
    QUICKTEXT_ENABLE NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x18") "SRM / ACE Setup" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "MRCHEEZE" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "SAVESTATE" NEWLINE NEWLINE NEWLINE
    NEWLINE
    SHIFT("\x24") SHIFT("\x18") "Build Toolchain" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "SAURAEN" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "Z64ME"
    QUICKTEXT_DISABLE FADE2("\x00\x3A")
)

DECLARE_MESSAGE(0x0F70, BOX_CREDITS, POS_VARIABLE,
    QUICKTEXT_ENABLE NEWLINE
    SHIFT("\x24") SHIFT("\x2E") "COMMUNITY UNIT" NEWLINE NEWLINE
    NEWLINE NEWLINE NEWLINE
    SHIFT("\x14") SHIFT("\x08") "Partner Creators" NEWLINE NEWLINE NEWLINE
    SHIFT("\x14") SHIFT("\x26") "SWANKYBOX" NEWLINE NEWLINE NEWLINE
    SHIFT("\x14") SHIFT("\x26") "RETRO GAME" NEWLINE NEWLINE
    SHIFT("\x14") SHIFT("\x40")     "MECHANICS EXPLAINED" NEWLINE NEWLINE NEWLINE
    SHIFT("\x14") SHIFT("\x26") "HARD4GAMES" NEWLINE NEWLINE NEWLINE
    QUICKTEXT_DISABLE FADE2("\x00\x4E")
)

DECLARE_MESSAGE(0x0F71, BOX_CREDITS, POS_VARIABLE,
    QUICKTEXT_ENABLE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x18") "Partner Reactors" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "HMK" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "TETRABITGAMING"
    QUICKTEXT_DISABLE FADE2("\x00\x49")
)

DECLARE_MESSAGE(0x0F72, BOX_CREDITS, POS_VARIABLE,
    QUICKTEXT_ENABLE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x24") "OST Published By" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x42") "SIIVAGUNNER"
    QUICKTEXT_DISABLE FADE2("\x00\x30")
)

DECLARE_MESSAGE(0x0F80, BOX_CREDITS, POS_VARIABLE,
    QUICKTEXT_ENABLE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x18") "Video Editing" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "MUSKET012" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "GRAVATOS" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "SAVESTATE" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "SAURAEN"
    QUICKTEXT_DISABLE FADE2("\x00\x3A")
)

DECLARE_MESSAGE(0x0F81, BOX_CREDITS, POS_VARIABLE,
    QUICKTEXT_ENABLE NEWLINE
    SHIFT("\x24") SHIFT("\x18") "Technical Support" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "ZEL" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "Z64ME" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "MZXRULES" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "THARO" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "WISEGUY" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "JACK WALKER"
    QUICKTEXT_DISABLE FADE2("\x00\x3A")
)

DECLARE_MESSAGE(0x0F90, BOX_CREDITS, POS_VARIABLE,
    QUICKTEXT_ENABLE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x18") "Special Thanks" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "KAZE EMANUAR" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "XDANIEL" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x36") "ARIANA ALMANDOZ"
    QUICKTEXT_DISABLE FADE2("\x00\x3A")
)

DECLARE_MESSAGE(0x0F91, BOX_CREDITS, POS_VARIABLE,
    QUICKTEXT_ENABLE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x32") "Executive Producer" NEWLINE NEWLINE NEWLINE
    SHIFT("\x24") SHIFT("\x42") "DWANGOAC"
    QUICKTEXT_DISABLE FADE2("\x00\x3A")
)

DECLARE_MESSAGE(0x0F92, BOX_CREDITS, POS_VARIABLE,
    QUICKTEXT_ENABLE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE
    SHIFT("\x62") "Presented At" NEWLINE NEWLINE NEWLINE
    SHIFT("\x1A") "SUMMER GAMES DONE QUICK 2022" 
    QUICKTEXT_DISABLE FADE2("\x00\x3A")
)

DECLARE_MESSAGE(0x0FA0, BOX_CREDITS, POS_VARIABLE,
    QUICKTEXT_ENABLE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE
    NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE
    SHIFT("\x23") "Assets, Toolchain, and Performance" NEWLINE NEWLINE
    SHIFT("\x42") "Copyright (C) 2019-2022" NEWLINE NEWLINE
    SHIFT("\x50") "The Triforce% Team"
    QUICKTEXT_DISABLE FADE2("\x00\x3A")
)

DECLARE_MESSAGE(0x0FA1, BOX_CREDITS, POS_VARIABLE,
    QUICKTEXT_ENABLE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE
    NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE
    SHIFT("\x18") "The Legend of ZELDA: Ocarina of Time" NEWLINE NEWLINE
    SHIFT("\x52") "Copyright (C) 1998" NEWLINE NEWLINE
    SHIFT("\x72") "Nintendo"
    QUICKTEXT_DISABLE FADE2("\x00\x3A")
)

DECLARE_MESSAGE(0x0FA2, BOX_CREDITS, POS_VARIABLE,
    QUICKTEXT_ENABLE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE
    NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE
    SHIFT("\x75") "The End"
    QUICKTEXT_DISABLE PERSISTENT
)



// Trailer

/*
DECLARE_MESSAGE(0x109D, BOX_NONE_BOTTOM, POS_VARIABLE,
    SHIFT("\x1B") "If you were really good" NEWLINE
    SHIFT("\x24") "at pressing buttons," NEWLINE
    SHIFT("\x23") "what would you do?" BOX_BREAK_DELAYED("\x28")
    SHIFT("\x10") "Would you play a game really" NEWLINE
    SHIFT("\x0B") "skillfully, but within the bounds" NEWLINE
    SHIFT("\x14") "intended by the developers?" BOX_BREAK_DELAYED("\x28")
    SHIFT("\x12") "Would you perform difficult," NEWLINE
    SHIFT("\x08") "elaborate glitches to skip large" NEWLINE
    SHIFT("\x20") "portions of the game?" BOX_BREAK_DELAYED("\x28")
    SHIFT("\x13") "Or would you get a robot," BOX_BREAK_DELAYED("\x28")
    SHIFT("\x1B") "build on two decades of" NEWLINE
    SHIFT("\x18") "reverse engineering work," BOX_BREAK_DELAYED("\x28")
    SHIFT("\x1B") "and glitch your way into" NEWLINE
    SHIFT("\x17") "changing the game's code?" BOX_BREAK_DELAYED("\x28")
    
    SHIFT("\x21") "If you had the ability" NEWLINE
    SHIFT("\x0A") "to rewrite the laws of reality," NEWLINE
    SHIFT("\x24") "what would you do?" BOX_BREAK_DELAYED("\x28")
                  "Would you just achieve your goals" NEWLINE
    SHIFT("\x1F") "as quickly as possible?" BOX_BREAK_DELAYED("\x28")
    SHIFT("\x15") "Would you erase everything" NEWLINE
    SHIFT("\x09") "and make something brand new?" BOX_BREAK_DELAYED("\x28")
    SHIFT("\x09") "Or would you make the dreams" BOX_BREAK_DELAYED("\x28")
    SHIFT("\x20") "of millions of players" BOX_BREAK_DELAYED("\x28")
    SHIFT("\x27") "finally come true?" BOX_BREAK_DELAYED("\x28")
    
    SHIFT("\x0D") "If you had the power to make" NEWLINE
    SHIFT("\x07") "Hyrule however you dreamed it..." BOX_BREAK_DELAYED("\x28")
                  "the attention of thousands of viewers..." BOX_BREAK_DELAYED("\x28")
    SHIFT("\x08") "and one wish to the Goddesses..." BOX_BREAK_DELAYED("\x28")
    SHIFT("\x02") "would you create something great?" FADE("\x50")
)

DECLARE_MESSAGE(0x109D, BOX_CREDITS, POS_VARIABLE,
    QUICKTEXT_ENABLE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE
    SHIFT("\x42") "Triforce%" NEWLINE NEWLINE
    SHIFT("\x28") "OoT ACE Showcase" 
    QUICKTEXT_DISABLE BOX_BREAK_DELAYED("\x28")
    QUICKTEXT_ENABLE NEWLINE NEWLINE NEWLINE
    SHIFT("\x18")   "Sauraen"    SHIFT("\x36") "Savestate"     NEWLINE
    SHIFT("\x20")     "zel"      SHIFT("\x40") "CDi-Fails"     NEWLINE
    SHIFT("\x14")  "rankaisija"  SHIFT("\x3A") "z64me"         NEWLINE
    SHIFT("\x0D") "TerusTheBird" SHIFT("\x25") "Kim-SukLey"    NEWLINE
    SHIFT("\x15")   "MrCheeze"   SHIFT("\x26") "RebeccaETripp" NEWLINE
    SHIFT("\x1E")    "Yukloj"    SHIFT("\x48") "Zero"          NEWLINE
    SHIFT("\x0B")  "AeroArtwork" SHIFT("\x26") "musket012"
    QUICKTEXT_DISABLE BOX_BREAK_DELAYED("\x28")
    QUICKTEXT_ENABLE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE NEWLINE
    SHIFT("\x3E") "SGDQ 2022"
    QUICKTEXT_DISABLE BOX_BREAK_DELAYED("\x28")
    "dummy"
)
*/

//This one needs to come at the end
DECLARE_MESSAGE(0xFFFF, BOX_BLUE, POS_MIDDLE,
    "Dummy"
)
