
# Description of the .tbt TabIt file format

## Overview

This document describes the format for .tbt files that are opened and saved by TabIt, a Windows application that is described on its [website](http://www.tabit.net) as

> a full-featured program for creating, playing, and printing guitar, bass, or banjo tablature.

TabIt is sold by GTAB Software.

The latest version of TabIt, version 2.03, was released in 2006.

TabIt is effectively abandonware.

Version 2.03 was used as a reference for this work.

Only files produced by this version are discussed.

For earlier versions, [tbt-parser](https://github.com/bostick/tbt-parser/) does handle all known versions of TabIt, but no effort is made to document these versions.

The format description was reverse-engineered and this document is not an official specification.

Any deviations in this document from how TabIt actually works are errors in this document and should be brought to the attention of the author.


I am not affiliated with TabIt and I do not own any trademark associated with TabIt.

I am simply a fan who wants to see TabIt live.

Thank you JR.




## Example: Twinkle Twinkle Little Star

Here is a dissection of an example file of Twinkle Twinkle Little Star.

![twinkle](twinkle.png)

You can download the .tbt file [here](twinkle.tbt).

The whole file is 143 bytes and looks like this:
```
T B T o x . . 1 . 6 . . . . . .     54 42 54 6f 78 01 03 31 2e 36 00 0b 00 00 00 00
. . . . . . . . . . . . . . . .     00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
. . . . . . . . . . . . . . x .     00 00 00 00 00 00 00 00 00 00 c0 00 b8 00 78 00
. . . . . z y . . . . . . p . .     15 00 00 00 e0 7a 79 15 8f 00 00 00 a2 70 b6 18
x . c . . I ` . . . . . . . . .     78 da 63 93 96 49 60 00 02 07 09 86 ff 0c d8 00
. 1 U . . x . . ` . g ` d $ . .     00 31 55 01 f5 78 da 93 60 e0 67 60 64 24 05 87
2 0 2 0 6 . . q   . c . ? . 7 A     32 30 32 30 36 fb 03 71 20 03 63 83 3f 04 37 41
q . < . . . . . . . . . " . . .     71 c3 3c a8 1c b2 18 08 fb 01 c5 16 22 b1 d1 d5
, . # 7 . L . . 1 . . . T % |       2c c0 23 37 8f 4c fb e6 31 00 00 d3 54 25 7c
```

The first 64 bytes of a TabIt file is the header:
```
T B T o x . . 1 . 6 . . . . . .     54 42 54 6f 78 01 03 31 2e 36 00 0b 00 00 00 00
. . . . . . . . . . . . . . . .     00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
. . . . . . . . . . . . . . x .     00 00 00 00 00 00 00 00 00 00 c0 00 b8 00 78 00
. . . . . z y . . . . . . p . .     15 00 00 00 e0 7a 79 15 8f 00 00 00 a2 70 b6 18
```

Then the metadata, which is a zlib stream:
```
x . c . . I ` . . . . . . . . .     78 da 63 93 96 49 60 00 02 07 09 86 ff 0c d8 00
. 1 U . .                           00 31 55 01 f5
```

And finally the body, which is also a zlib stream:
```
x . . ` . g ` d $ . . 2 0 2 0 6     78 da 93 60 e0 67 60 64 24 05 87 32 30 32 30 36
. . q   . c . ? . 7 A q . < . .     fb 03 71 20 03 63 83 3f 04 37 41 71 c3 3c a8 1c  
. . . . . . . " . . . , . # 7 .     b2 18 08 fb 01 c5 16 22 b1 d1 d5 2c c0 23 37 8f
L . . 1 . . . T % |                 4c fb e6 31 00 00 d3 54 25 7c
```

After inflating, the uncompressed metadata looks like this:
```
. . . ` . . . . @ . . . . . . .     06  1b  1c  60  00  00  00  00  40  18  00  ff  00  00  00  00
. . . . . . . . . . . . . . . .     00  00  00  00  00  00  00  00  00  00  00  00  00  00  00  00
.                                   00
```

And after inflating, the uncompressed body looks like this:
```
. . . . . . . . . . . . . . . .     18  00  0f  00  01  01  0f  00  01  01  0f  00  01  01  0f  00
. . . . . . . . . . . . . . . .     01  01  0f  00  01  01  0f  00  01  01  0f  00  01  01  0f  00
. . . . . . . . . . . . . . . .     01  01  0f  00  01  01  0f  00  01  01  0f  00  01  01  0f  00
. . U . . . . . O . . . Q . . .     01  01  55  00  01  00  01  83  4f  00  01  83  51  00  01  80
O . . . O . . . O . . . O . . .     4f  00  01  80  4f  00  01  82  4f  00  01  82  4f  00  01  80
. . . . O . . . O . . . O . . .     9e  00  01  83  4f  00  01  83  4f  00  01  82  4f  00  01  82
O . . . O . . . N . . . . . . .     4f  00  01  80  4f  00  01  80  4e  00  01  83  a1  00  01  80
O . . . N . . . O . . . O . . .     4f  00  01  80  4e  00  01  83  4f  00  01  83  4f  00  01  82
O . . . O . . . . . . . O . . .     4f  00  01  82  4f  00  01  80  a0  00  01  80  4f  00  01  80
N . . . O . . . O . . . O . . .     4e  00  01  83  4f  00  01  83  4f  00  01  82  4f  00  01  82
O . . . . . . . O . . . Q . . .     4f  00  01  80  9e  00  01  83  4f  00  01  83  51  00  01  80
O . . . O . . . O . . . O . . .     4f  00  01  80  4f  00  01  82  4f  00  01  82  4f  00  01  80
. . . . O . . . O . . . O . . .     9e  00  01  83  4f  00  01  83  4f  00  01  82  4f  00  01  82
O . . . O . . . N . . . . .         4f  00  01  80  4f  00  01  80  4e  00  01  83  9e  00
```

The uncompressed body has 2 sections: bars and notes.

This is the bars section of the body:
```
. . . . . . . . . . . . . . . .     18  00  0f  00  01  01  0f  00  01  01  0f  00  01  01  0f  00
. . . . . . . . . . . . . . . .     01  01  0f  00  01  01  0f  00  01  01  0f  00  01  01  0f  00
. . . . . . . . . . . . . . . .     01  01  0f  00  01  01  0f  00  01  01  0f  00  01  01  0f  00
. .                                 01  01
```

And this is the notes section of the body:
```
U . . . . . O . . . Q . . . O .     55  00  01  00  01  83  4f  00  01  83  51  00  01  80  4f  00
. . O . . . O . . . O . . . . .     01  80  4f  00  01  82  4f  00  01  82  4f  00  01  80  9e  00
. . O . . . O . . . O . . . O .     01  83  4f  00  01  83  4f  00  01  82  4f  00  01  82  4f  00
. . O . . . N . . . . . . . O .     01  80  4f  00  01  80  4e  00  01  83  a1  00  01  80  4f  00
. . N . . . O . . . O . . . O .     01  80  4e  00  01  83  4f  00  01  83  4f  00  01  82  4f  00
. . O . . . . . . . O . . . N .     01  82  4f  00  01  80  a0  00  01  80  4f  00  01  80  4e  00
. . O . . . O . . . O . . . O .     01  83  4f  00  01  83  4f  00  01  82  4f  00  01  82  4f  00
. . . . . . O . . . Q . . . O .     01  80  9e  00  01  83  4f  00  01  83  51  00  01  80  4f  00
. . O . . . O . . . O . . . . .     01  80  4f  00  01  82  4f  00  01  82  4f  00  01  80  9e  00
. . O . . . O . . . O . . . O .     01  83  4f  00  01  83  4f  00  01  82  4f  00  01  82  4f  00
. . O . . . N . . . . .             01  80  4f  00  01  80  4e  00  01  83  9e  00
```



## Terminology

A space is a slice of notes at one instant of time.

![Highlighting a single space in TabIt](single-space.png)

A space is typically one 1/16th note in TabIt. A 1/16th note is sometimes called a "semi-quaver".

A space may have different notes and also different effects such as a hammer-on, tap, harmonic, etc.

In order to store these in a single space, it is necessary to sub-divide a space into 20 separate "slots" where notes and effects may be stored.

Incrementing through slots is measured in "vsqs" which is short for "viginti-semi-quaver" which means 1/20 of 1/16th note.

For example, the A string and D string are next to each other and when incrementing from a note on the A string to a note on the D string, the increment is 1 vsq.

In other situations, it is necessary to sub-divide a space into only 2 parts, and these parts are called "dsqs", which is short for "demi-semi-quaver" which means = 1/2 of 1/16th notes.



## Sizes of things

TabIt supports up to 15 tracks.

Each track may have up to 32000 spaces.

Each track may have up to 8 strings.

The highest note on each string may be 99.

Tempo must be between 30 BPM and 500 BPM.

Pitch bends can be between -2400 and 2400 cents (-24 and 24 semitones).



## Data structures and endianness

The integers stored in .tbt files are stored little-endian.

A 1-byte integer will be referred to as a "byte".

A 2-byte integer will be referred to as a "short".

A 4-byte integer will be referred to as an "int".

Strings in .tbt files are stored as Pascal strings.

Pascal strings store their length first.

There are Pascal1 strings and Pascal2 strings.

Pascal1 strings store their length as a byte.

Pascal2 strings store their length as a short.

A chunk is a blob of binary data that stores its length first.

There are DeltaListChunks and Chunk4s.

DeltaListChunks store their length as a short and it signifies how many PAIRS of bytes to read.

This is important: the number of bytes to read in a DeltaListChunk is TWO TIMES the length stored at the beginning.

Chunk4s store their length as an int and it signifies how many bytes to read.

Zlib streams are blobs of binary data that must be inflated with zlib. All zlib streams in .tbt files begin with the bytes `0x78 0xda`, which come from zlib and mean that the best compression was used.

An ArrayList is a stream of structured data that can be iterated through and may also be indexed.

A DeltaList uses a kind of delta encoding and is iterated through, but cannot be meaningfully indexed.



## A note on iterating through DeltaLists

Iterating through DeltaLists happens a few times in TabIt files.

DeltaLists use an increment that is delta encoded and a payload.

DeltaLists use a simple scheme for encoding variable-length increments.

If the first byte read is anything other than `00` then, then that byte is the increment.

If the first byte read is `00`, then this means to read the next 2 bytes as a short, and that is the increment.

For example, the bytes `01 83` mean to increment `01` byte and fill-in the skipped bytes with value `83`.

And the bytes `00 21 01 02` mean to increment 289 (which is the value of `21 01` as a short) and fill-in with the value `02`.

The bytes `4f 00` mean to increment `4f` bytes and fill-in with value `00`.

Here is the DeltaList for the notes section of the Twinkle example:
```
. . . . O . . . Q . . . O . . .     01  00  01  83  4f  00  01  83  51  00  01  80  4f  00  01  80
O . . . O . . . O . . . . . . .     4f  00  01  82  4f  00  01  82  4f  00  01  80  9e  00  01  83
O . . . O . . . O . . . O . . .     4f  00  01  83  4f  00  01  82  4f  00  01  82  4f  00  01  80
O . . . N . . . . . . . O . . .     4f  00  01  80  4e  00  01  83  a1  00  01  80  4f  00  01  80
N . . . O . . . O . . . O . . .     4e  00  01  83  4f  00  01  83  4f  00  01  82  4f  00  01  82
O . . . . . . . O . . . N . . .     4f  00  01  80  a0  00  01  80  4f  00  01  80  4e  00  01  83
O . . . O . . . O . . . O . . .     4f  00  01  83  4f  00  01  82  4f  00  01  82  4f  00  01  80
. . . . O . . . Q . . . O . . .     9e  00  01  83  4f  00  01  83  51  00  01  80  4f  00  01  80
O . . . O . . . O . . . . . . .     4f  00  01  82  4f  00  01  82  4f  00  01  80  9e  00  01  83
O . . . O . . . O . . . O . . .     4f  00  01  83  4f  00  01  82  4f  00  01  82  4f  00  01  80
O . . . N . . . . .                 4f  00  01  80  4e  00  01  83  9e  00
```

Here is a better visualization of the same bytes:
```
. .         01  00
. . O .     01  83  4f  00
. . Q .     01  83  51  00
. . O .     01  80  4f  00
. . O .     01  80  4f  00
. . O .     01  82  4f  00
. . O .     01  82  4f  00
. . . .     01  80  9e  00
. . O .     01  83  4f  00
. . O .     01  83  4f  00
. . O .     01  82  4f  00
. . O .     01  82  4f  00
. . O .     01  80  4f  00
. . N .     01  80  4e  00
. . . .     01  83  a1  00
. . O .     01  80  4f  00
. . N .     01  80  4e  00
. . O .     01  83  4f  00
. . O .     01  83  4f  00
. . O .     01  82  4f  00
. . O .     01  82  4f  00
. . . .     01  80  a0  00
. . O .     01  80  4f  00
. . N .     01  80  4e  00
. . O .     01  83  4f  00
. . O .     01  83  4f  00
. . O .     01  82  4f  00
. . O .     01  82  4f  00
. . . .     01  80  9e  00
. . O .     01  83  4f  00
. . Q .     01  83  51  00
. . O .     01  80  4f  00
. . O .     01  80  4f  00
. . O .     01  82  4f  00
. . O .     01  82  4f  00
. . . .     01  80  9e  00
. . O .     01  83  4f  00
. . O .     01  83  4f  00
. . O .     01  82  4f  00
. . O .     01  82  4f  00
. . O .     01  80  4f  00
. . N .     01  80  4e  00
. . . .     01  83  9e  00
```

We can step through the process of iterating through this DeltaList.

To start, `vsqCount = 0`.

Read `01 00`, so `notes[0] = 0x00` and `vsqCount += 0x01 (vsqCount == 1)`.

Read `01 83`, so `notes[1] = 0x83` and `vsqCount += 0x01 (vsqCount == 2)`.

Read `4f 00`, so `notes[2...80] = 0x00` and `vsqCount += 0x4f (vsqCount == 81)`.

Read `01 83`, so `notes[81] = 0x83` and `vsqCount += 0x01 (vsqCount == 82)`.

Read `51 00`, so `notes[82...162] = 0x00` and `vsqCount += 0x51 (vsqCount == 163)`.

And so on.

Delta encoding allows for good compression because of repeated structure in the data.



## Structure

The structure of all TabIt files follows this sequence of parts:

1. Header
1. Metadata
1. Body



### Header

The first 64 bytes of a .tbt file is the header.

```
0x00: magic (3 bytes)
0x03: versionNumber: byte
0x04: tempo1: byte
0x05: trackCount: byte
0x06: versionString (Pascal1 string)
0x0b: featureBitfield: byte
0x0c: unused (28 bytes)
0x28: barCount: short
0x2a: spaceCount: short
0x2c: lastNonEmptySpace: short
0x2e: tempo2: short
0x30: compressedMetadataLen: int
0x34: crc32Body: int
0x38: totalByteCount: int
0x3c: crc32Header: int
```

The `magic` bytes for .tbt files are `0x54 0x42 0x54` which are ASCII values for `TBT`.

The `versionNumber` byte is a value such as `0x6f` or `0x72`.

TabIt 2.03 may save files as different versions depending on the features that the file uses.

* No special features are used: saved as version `0x6f`

* Uses Alternate Time Regions: saved as version `0x70`

* Uses modulation or pitch bending: saved as version `0x72`

`tempo1` is the tempo of the song, but only stored in a byte. For the actual tempo, see `tempo2`.

The `trackCount` is the number of tracks in the song.

`versionString` is a string with a value such as `1.55` or `2.0`.

`featureBitfield` sets individual bits according to certain features.
```
76543210
   ^^^^^
       1: unknown; always set; possibly related to having string metadata
      2: unknown; never set earlier than 0x68, sometimes set in 0x68, always set later than 0x68
     4: unknown; seems to only be present in 0x6f files; does not survive being resaved
    8: unknown; always set in 0x6e and later; possibly related to zlib compression for Metadata and Body
   10: has Alternate Time Regions; only set in 0x70 and newer
  20: unused
 40: unused
80: unused
```


If `versionNumber >= 0x70`, `barCount` is the number of bars in the song.

If `versionNumber == 0x6f`, `spaceCount` is the number of spaces in the song.

If `versionNumber == 0x6f`, `lastNonEmptySpace` is the last non-empty space in the song.

`tempo2` is the actual tempo of the song.

`compressedMetadataLen` is the length of the compressed metadata.

`crc32Body` is the CRC-32 of the body.

`totalByteCount` is the total number of bytes in the file.

`crc32Header` is the CRC-32 of the header (first 60 bytes).



### Metadata

Metadata is a zlib stream that must be inflated.

Number of bytes in the metadata stream is specified with `compressedMetadataLen` in the header.

After inflating, read the bytes according to this pseudo-code:
```
if 0x70 <= versionNumber:
  spaceCountBlock = read(4 * trackCount)

stringCountBlock = read(1 * trackCount)
cleanGuitarBlock = read(1 * trackCount)
mutedGuitarBlock = read(1 * trackCount)
volumeBlock = read(1 * trackCount)

if 0x71 <= versionNumber:
  modulationBlock = read(1 * trackCount)
  pitchBendBlock = read(2 * trackCount)

transposeHalfStepsBlock = read(1 * trackCount)
midiBankBlock = read(1 * trackCount)

reverbBlock = read(1 * trackCount)
chorusBlock = read(1 * trackCount)

panBlock = read(1 * trackCount)
highestNoteBlock = read(1 * trackCount)

displayMIDINoteNumbersBlock = read(1 * trackCount)
midiChannelBlock = read(1 * trackCount)

topLineTextBlock = read(1 * trackCount)
bottomLineTextBlock = read(1 * trackCount)

tuningBlock = read(8 * trackCount)

drumBlock = read(1 * trackCount)

title = read(Pascal2 string)
artist = read(Pascal2 string)
album = read(Pascal2 string)
transcribedBy = read(Pascal2 string)
comment = read(Pascal2 string)
```

`spaceCountBlock` is the number of spaces for each track, stored as an int.

`stringCountBlock` is the number of strings for each track, stored as a byte.

`cleanGuitarBlock` is the combination of both MIDI program number and Dont Let Notes Ring flag for clean guitar for each track, stored as a byte.

Use bit mask `0b10000000` to determine the Dont Let Notes Ring flag.
Use bit mask `0b01111111` to determine the MIDI program number.

If Dont Let Notes Ring flag is `1`, then each string rings until the next event on ANY string.

If Dont Let Notes Ring flag is `0`, then each string rings independently until the next event on THAT string, like a real guitar.

The MIDI program number is something like 27 for Electric Guitar (clean).

`mutedGuitarBlock` is the MIDI program number for muted guitar for each track, stored as a byte.

`mutedGuitarBlock` seems to be unused. Older files can have non-default values for muted guitar, but there is no way to edit with the latest version of TabIt.

`volumeBlock` is the volume for each track, stored as a byte. A typical value is 96 (0x60).

`modulationBlock` is the modulation effect for each track, stored as a byte.

`pitchBendBlock` is the pitch bend effect for each track, stored as a short.

Pitch bend values may be positive or negative.

`transposeHalfStepsBlock` is the number of half-steps to transpose for each track, stored as a byte.

Transpose Half Steps values may be positive or negative.

`midiBankBlock` is the MIDI bank number to use for each track, stored as a byte.

MIDI Bank values can range from 0 to 127.

`reverbBlock` is the reverb effect for each track, stored as a byte.

`chorusBlock` is the chorus effect for each track, stored as a byte.

`panBlock` is the pan effect for each track, stored as a byte. A typical value is 64 (0x40).

`highestNoteBlock` is the highest allowed note for each track, stored as a byte. Typical values are 24 (0x18) or 99 (0x63).

`displayMIDINoteNumbersBlock` indicates whether to display MIDI note numbers for each track, stored as a byte.

`midiChannelBlock` is the MIDI channel for each track, stored as a byte.

MIDI channel can be -1 (0xff), which means "Automatically assign", or can be: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 (Drums), 10, 11, 12, 13, 14, 15.

`topLineTextBlock` indicates whether there is text at the top of each track, stored as a byte.

`bottomLineTextBlock` indicates whether there is text at the bottom of each track, stored as a byte.

`tuningBlock` is the difference in standard tuning for each string for each track, stored as a byte.

Tuning values may be negative or positive.

`drumBlock` indicates whether each track is a drum track, stored as a byte.

`title` is the title of the song, stored as a Pascal2 string.

`artist` is who wrote or created the song, stored as a Pascal2 string.

`album` is the album that the song was on, stored as a Pascal2 string.

`transcribedBy` is who transcribed the song into TabIt, stored as a Pascal2 string.

`comment` is a text field for comments such as lyrics, stored as a Pascal2 string.



### Body

Body is a zlib stream that must be inflated.

Number of bytes in the body stream is the number of remaining bytes in the file, which can be computed from `totalByteCount - 64 - compressedMetadataLen`.

The body has this sequence of parts:

1. Bars
1. Notes
1. Alternate Time Regions (optional)
1. Track Effect Changes (optional)


### Bars

Bars act as if they are between spaces.

Bars are stored differently depending on the version:

* For version `0x70` and newer, Bars are an ArrayList of 6 byte records.

* For version `0x6f` and earlier, Bars are stored in a sequence of DeltaListChunks.

The spaces being processed by bars do not have any knowledge of Alternate Time Regions.

The spaces in bars are as if there are NO Alternate Time Regions.


Alternate Time Regions are specified per-track and are made to match the spaces in Bars.


#### 0x70 and newer

For version `0x70` and newer, Bars are an ArrayList of 6 byte records, and can be read with this pseudo-code:
```
bars = read(barCount * 6)
```

Each record has this structure:

`s3 s2 s1 s0 c v`

The bytes `s3 s2 s1 s0` are an int that specifies how many spaces to increment after this bar.

`c` is a byte that is bit-masked with these values do determine which bar lines to make.

Bit-masking `c` with `0x00000001` determines single or double bar line:
```
0b00000000 = insert single bar line between PREVIOUS and CURRENT spaces
0b00000001 = insert double bar line between PREVIOUS and CURRENT spaces
```

Bit-masking `c` with `0x00000010` determines open repeat:
```
0b00000010 = insert open repeat between PREVIOUS and CURRENT spaces
```

Bit-masking `c` with `0x00000100` determines close repeat:
```
0b00000100 = insert close repeat at NEXT bar line
```

`c` may have multiple bits set. For example, if `c` is `0b00000110`, then that means insert an open repeat AND insert a close repeat.

If `c` is a close repeat, then `v` specifies the number of repeats.

The number of spaces in `barsStruct` can be used as the "plain" number of spaces for the song, with no Alternate Time Regions.



#### 0x6f and older

For version `0x6f` and older, Bars are stored in a sequence of DeltaListChunks, and can be read with this pseudo-code:
```
barList = new list
while True:
  chunk = read(deltaListChunk)
  barList.append(chunk)
  sqCount = countSQ(barList)
  if sqCount == spaceCount:
    break
```

After a complete Bars list is created, then this is a DeltaList that is iterated through.

Each byte in the expanded DeltaList corresponds to a space and is bit-masked with these values to determine which bar lines to make:
```
0x00001111 = specifies which change to make
0x11110000 = specifies how many repeats
```

After bitmasking with `0x00001111`, the value determines which bar lines to make:
```
0 = skip
1 = insert single bar line between CURRENT and NEXT spaces
2 = insert close repeat between CURRENT and NEXT spaces
3 = insert open repeat between PREVIOUS and CURRENT spaces
4 = insert double bar line between CURRENT and NEXT spaces
```

When inserting a close repeat, use `0x11110000` to determine how many repeats.


### Notes

For each track, Notes are stored in a sequence of DeltaListChunks, and can be read with this pseudo-code:
```
noteList = new list
while True:
  chunk = read(deltaListChunk)
  noteList.append(chunk)
  vsqCount = countVSQ(noteList)
  if vsqCount == 20 * spaceCount:
    break
```

After a complete Notes list is created, then this is a DeltaList that is iterated through.

Each byte in the expanded DeltaList corresponds to a value for the current `vsq`.

The current slot can be computed with `vsq % 20`.

#### Slots 0 to 7

Note values for strings in this space.

For example, value `0x80` at slot 0 means a 0 note on the low E string. A value of `0x85` at slot 1 means a 5 note on the A string.

Drums may have higher numbers than the usual number of frets on guitar strings. The max note is 99, so the highest note value is `0x80` + 99 == `0xe3`.

Besides note values, `0x11` is used for mute string (shown as `x` in TabIt) and `0x12` for stop string (shown as `*` in TabIt).

A muted string plays for a 1/64 of a second using the current instrument, or until the next event on that string.



#### Slots 8 to 15

Effects for each string. Slot 8 is the effect for string 0 (E), Slot 9 is the effect for string 1 (A), etc.

```
0x00: Skip (no string effect)
0x28 ('('): Soft
0x2f ('/'): Slide up
0x3c ('<'): Harmonic
0x5c ('\'): Slide down
0x5e ('^'): Bend up
0x62 ('b'): Bend
0x68 ('h'): Hammer on
0x70 ('p'): Pull off
0x72 ('r'): Release bend
0x73 ('s'): Slap
0x74 ('t'): Tap
0x77 ('w'): Whammy bar bend
0x7b ('{'): Tremolo
0x7e ('~'): Vibrato
```

#### Slot 16

Effects for the entire track.

These are only set when `versionNumber <= 0x70`.

```
0x00: Skip (no track effect)
0x43 ('C'): Chorus change
0x44 ('D'): Stroke down
0x49 ('I'): Instrument change
0x50 ('P'): Pan change
0x52 ('R'): Reverb change
0x54 ('T'): Tempo change
0x55 ('U'): Stroke up
0x56 ('V'): Volume change
0x74 ('t'): Tempo change + 250
```


#### Slot 17

Single ASCII character for top line text


#### Slot 18

Single ASCII character for bottom line text


#### Slot 19

The change value for track effects.

For Instrument changes, use bit mask `0b10000000` to determine the new Dont Let Notes Ring flag and use bit mask `0b01111111` to determine the new MIDI program number.



### Alternate Time Regions

`featureBitfield` from the header should be bit-masked with `0b00010000` to determine if there are Alternate Time Regions.

If not, then skip this section.

For each track, Alternate Time Regions are stored in a sequence of DeltaListChunks, and can be read with this pseudo-code:
```
alternateTimeRegionList = new list
while True:
  chunk = read(deltaListChunk)
  noteList.append(chunk)
  dsqCount = countDSQ(noteList)
  if dsqCount == 2 * spaceCount:
    break
```

After a complete Alternate Time Region list is created, then this is a DeltaList that is iterated through.

Each byte in the expanded DeltaList corresponds to a value for the current `dsq`.

The current slot can be computed with `dsq % 2`.

#### Slot 0

The denominator of the Alternate Time Region for this space. For example, for triplets, this is 2.


#### Slot 1

The numerator of the Alternate Time Region for this space. For example, for triplets, this is 3.



### Track Effect Changes

If `versionNumber` is `0x70` or below, then skip this section.

For each track, Track Effect Changes are stored as a Chunk4.

After reading the Chunk4, there is an ArrayList that is iterated through.

Each entry in the list is an 8 byte structure:
`s1 s0 e1 e0 r1 r0 v1 v0`

`s1 s0` is a short that specifies how many spaces to increment before this change.

`e1 e0` is a short that specifies the effect to change.

`r1 r0` is a short and reserved and is always `0x02`.

`v1 v0` is a short that is the value of the change.


Track Effects are numbered:
```
1 = Stroke down
2 = Stroke up
3 = Tempo
4 = Instrument
5 = Volume
6 = Pan
7 = Chorus
8 = Reverb
9 = Modulation
10 = Pitch bend
```

For Instrument changes, `v1` is the new MIDI bank and `v0` is the combination of Dont Let Notes Ring flag and new MIDI program number.

Use bit mask `0b10000000` to determine the Dont Let Notes Ring flag and use bit mask `0b01111111` to determine the new MIDI program number.


<!--
## describe the clever bits
-->


## How did I do it?

Since I have a copy of TabIt and I can run it, then an easy approach is to save different files while changing only 1 thing and see what the difference is.

For example, putting the notes `012345` on the low E string, then putting the notes `012345` on the A string, and then seeing how the files differ.

Change the tempo, then resave, and see how the files differ.

Change the tuning, then resave, and see how the files differ.

Add a track, then resave, and see how the files differ.

Add bar lines, then resave, and see how the files differ.

etc.

Zlib are annoying to try to recognize, but luckily, TabIt always uses Best Compression and that means `0x78 0xda` starts every zlib stream.

Slowly but surely, knowledge will be built about the structure and layout of the file format.

It took a LOT of work and I learned a lot about reverse engineering in the process.



## Special Thanks

Thank you to @foone for the Twitter thread on reverse-engineering SkiFree:
[https://twitter.com/Foone/status/1536053690368348160](https://twitter.com/Foone/status/1536053690368348160)

Thank you to rattle for writing about reverse-engineering Delphi binaries:
[https://blag.nullteilerfrei.de/2019/12/23/reverse-engineering-delphi-binaries-in-ghidra-with-dhrake/](https://blag.nullteilerfrei.de/2019/12/23/reverse-engineering-delphi-binaries-in-ghidra-with-dhrake/)


<!--
that link talking about magic bytes and 78 DA
https://tstillz.medium.com/basic-static-analysis-part-1-9c24497790b6
-->



 <p xmlns:cc="http://creativecommons.org/ns#" xmlns:dct="http://purl.org/dc/terms/"><a property="dct:title" rel="cc:attributionURL" href="https://bostick.github.io/tabit-file-format/description/tabit-file-format-description.html">Description of the .tbt TabIt file format</a> by <a rel="cc:attributionURL dct:creator" property="cc:attributionName" href="https://bostick.github.io">Brenton Bostick</a> is licensed under <a href="http://creativecommons.org/licenses/by-sa/4.0/?ref=chooser-v1" target="_blank" rel="license noopener noreferrer" style="display:inline-block;">CC BY-SA 4.0<img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/cc.svg?ref=chooser-v1"><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/by.svg?ref=chooser-v1"><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/sa.svg?ref=chooser-v1"></a></p> 








