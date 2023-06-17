
# The .tbt TabIt file format


## Overview

This document describes the format for .tbt files that are opened and saved by TabIt, a Windows application described in its website [^1] as

> a full-featured program for creating, playing, and printing guitar, bass, or banjo tablature.

The format description was reverse-engineered and this document is not an official specification.

The latest version of TabIt, version 2.03, was released in 2006 and was used as a reference for the reverse-engineering work.

Any deviations in this document from how TabIt actually works are errors in this document and should be brought to the attention of the author.


I am not affiliated with TabIt and I do not own trademark associated with TabIt.

I am simply a fan who wants to see TabIt live.

Thank you JR.



## Terminology

A "space" is a slice of notes at one instant of time.

![Highlighting a single space in TabIt](single-space.png)

A space is typically one 1/16th note in TabIt. A 1/16th note is sometimes called a "semi-quaver".

A space may have different notes and also different effects such as a hammer-on, tap, harmonic, etc.

In order to store these in a single space, it is necessary to sub-divide a space into 20 separate "slots" where notes and effects may be stored.

Incrementing through slots is measured in "vsqs" which is short for "viginti-semi-quaver" which means 1/20 of 1/16th note.

E.g., the A string and D string are next to each other and when incrementing from a note on the A string to a note on the D string, the increment is 1 vsq.

In other situations, it is necessary to sub-divide a space into only 2 parts, and these parts are called "dsqs", which is short for "demi-semi-quaver" which means = 1/2 of 1/16th notes.


## Versions

Different versions of TabIt may save to the same file format version.

This document deals with version numbers encoded in .tbt files and doesn't talk about versions of the TabIt product itself.

Relatedly, TabIt files store both a version number and a version string.

The version string may be the same for different version numbers.

To be completely accurate, this document will refer to version numbers only.

Files stored with version number `0x68` store version string "1.22".

Files stored with version number `0x6e` store version string "1.55".

Files stored with version number `0x6f` store version string "1.6".

Files stored with version number `0x70` store version string "2.0".

Files stored with version number `0x71` store version string "2.0".

Files stored with version number `0x72` store version string "2.0".

The version strings correspond roughly to released versions of TabIt.


Version `0x6a` added "display MIDI note numbers" and MIDI channel.

Version `0x6b` increased the number of allowed strings to 8, and added pan and highest note.

Version `0x6c` added reverb and chorus.

Version `0x6d` added "transpose half steps" and MIDI bank, and album and transcribedBy.

Version `0x6f` increased the number of allowed spaces from 4000 to 32000.

Version `0x70` added alternate time regions.

Version `0x71` added added modulation, pitch bend, multiple changes at same time.

Note that `0x71` is "unstable" meaning that resaving `0x71` files saves them as `0x72` files.



## Sizes of things

TabIt supports up to 15 tracks.

Each track may have up to 32000 spaces.

Each track may have 8 strings in a track.

The highest note on each string may be 99.



## Data structures and endianness

The integers stored in .tbt files are stored little-endian.

A 1-byte integer will be referred to as a "byte".

A 2-byte integer will be referred to as a "short".

A 4-byte integer will be referred to as an "int".

Strings in .tbt files are stored as Pascal strings.

Pascal strings store their length first and lengths will be a byte or a short, depending on use.

A "chunk" is a stream of bytes with its length provided at the beginning.

"chunks" are blobs of binary data that store their length first and lengths will be a short or an int, depending on use.

There are chunk2s and chunk4s.

chunk2s have 2 bytes at the beginning that signify how many shorts to read.

chunk4s have 4 bytes at the beginning that signify how many bytes to read.

zlib streams are blobs of binary data that must be inflated with zlib. All zlib streams in .tbt files begin with the bytes `0x78 0xda`, which come from zlib and mean that best compression was used.

A plain "list" is a stream of structured data that can be iterated through and may also be indexed.

A "delta list" uses a kind of delta encoding and is iterated through, but cannot be meaningfully indexed.



## A note on iterating through delta lists

Iterating through delta lists happens a few times in TabIt files.

There are 2 states associated with iterating through delta lists: quiescent and jumping.

The iteration starts in the quiescent state.

The length os the list must be even and each pair of bytes is read together.

Each word in the delta list has this structure:

`s c`

`s` is a byte that specifies how many units to increment after this word, where the specific unit depends on context.

`c` is a byte that specifies what to do at this step, and depends on context.

The special value of 0 for `s` means to save the current `c` and transition to the jumping state.

If in the jumping state, then treat `savedC s` as a short for how many units to increment and treat current `c` as a "default" value for all slots being jumped. Then transition back to quiescent.



## Structure

The structure of all TabIt files follows this sequence of parts:

1. header
1. metadata
1. body


And the body has this sequence of parts:

1. bars
1. notes
1. alternate time regions (optional)
1. effect changes (optional)



### Header

The first 64 bytes of a .tbt file is the header.

```
0x00: magic (3 bytes)
0x03: versionNumber
0x04: tempo1
0x05: trackCount
0x06: versionString (5 bytes Pascal string)
0x0b: featureBitfield
0x0c: unused (28 bytes)
0x28: barCountGE70: short
0x2a: spaceCount6f: short
0x2c: lastNonEmptySpaceLE6f: short
0x2e: tempo2: short
0x30: metadataLen: int
0x34: crc32Body: int
0x38: totalByteCount: int
0x3c: crc32Header: int
```

The `magic` bytes for .tbt files are `0x54 0x42 0x54` which are ASCII values for `TBT`.

The `versionNumber` byte is a value such as `0x6f` or `0x72`.

If the tempo of the song is less than `250`, then `tempo1` is set to that value.

The `trackCount` is the number of tracks in the song.

`versionString` is a string with a value such as `1.55` or `2.0`.

`featureBitfield` sets individual bits according to certain features.
```
76543210
       ^
       1: always set, possibly related to having string metadata
      2: always set, purpose unknown
     4: seems to only be present in 0x6f files, does not survive being resaved
    8: always set, possibly related to having metadata
   10: has alternate time regions
  20: unused
 40: unused
80: unused
```

`featureBitfield` is usually `0b00001011`, but may be `0b00011011`, depending on whether there are alternate time regions.


If `versionNumber <= 0x70`, `barCountGE70` is the number of bars in the song.

If `versionNumber == 0x6f`, `spaceCount6f` is the number of spaces in the song.

If `versionNumber <= 0x6f`, `lastNonEmptySpaceLE6f` is the last non-empty space in the song.

`tempo2` is the tempo of the song.

`metadataLen` is the length of the metadata.

`crc32Body` is the CRC-32 of the body.

`totalByteCount` is the total number of bytes in the file.

`crc32Header` is the CRC-32 of the header (first 63 bytes).



### Metadata

Metadata is a zlib stream that must be inflated.

Number of bytes in the metadata stream is specified with `metadataLen` in the header.

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

if 0x6d <= versionNumber:
  transposeHalfStepsBlock = read(1 * trackCount)
  midiBankBlock = read(1 * trackCount)

if 0x6c <= versionNumber:
  reverbBlock = read(1 * trackCount)
  chorusBlock = read(1 * trackCount)

if 0x6b <= versionNumber:
  panBlock = read(1 * trackCount)
  highestNoteBlock = read(1 * trackCount)

if 0x6a <= versionNumber:
  displayMIDINoteNumbersBlock = read(1 * trackCount)
  midiChannelBlock = read(1 * trackCount)

topLineTextBlock = read(1 * trackCount)
bottomLineTextBlock = read(1 * trackCount)

if 0x6b <= versionNumber:
  tuningBlock = read(8 * trackCount)
else:
  tuningBlock = read(6 * trackCount)

drumBlock = read(1 * trackCount)

if 0x6d <= versionNumber:
  title = read(Pascal string)
  artist = read(Pascal string)
  album = read(Pascal string)
  transcribedBy = read(Pascal string)
  comment = read(Pascal string)
else:
  title = read(Pascal string)
  artist = read(Pascal string)
  comment = read(Pascal string)
```

`spaceCountBlock` is the number of spaces for each track, stored as an int.

`stringCountBlock` is the number of strings for each track, stored as a byte.

`cleanGuitarBlock` is the MIDI program number for clean guitar for each track, stored as a byte.
For cleanGuitarBlock:
Use bit mask `0b10000000` to determine dontLetNotesRing.
Use bit mask `0b01111111` to determine the actual MIDI program number.

`mutedGuitarBlock` is the MIDI program number for muted guitar for each track, stored as a byte.

`volumeBlock` is the volume for each track, stored as a byte.

`modulationBlock` is the modulation effect for each track, stored as a byte.

`pitchBendBlock` is the pitch bend effect for each track, stored as a short.

`transposeHalfStepsBlock` is the number of half-steps to transpose for each track, stored as a byte.

`midiBankBlock` is the MIDI bank number to use for each track, stored as a byte.

`reverbBlock` is the reverb effect for each track, stored as a byte.

`chorusBlock` is the chorus effect for each track, stored as a byte.

`panBlock` is the pan effect for each track, stored as a byte.

`highestNoteBlock` is the highest allowed note for each track, stored as a byte.

`displayMIDINoteNumbersBlock` controls whether to display MIDI note numbers for each track, stored as a byte.

`midiChannelBlock` is the MIDI channel for each track, stored as a byte.

`topLineTextBlock` controls whether there is text at the top of each track, stored as a byte.

`bottomLineTextBlock` controls whether there is text at the bottom of each track, stored as a byte.

`tuningBlock` is the difference in standard tuning for each string for each track, stored as a byte.

`drumBlock` controls whether the track is a drum track for each track, stored as a byte.

`title` is the title of the song.

`artist` is who wrote or created the song.

`album` is the album that the song was on.

`transcribedBy` is who transcribed the song into TabIt.

`comment` is a text field for comments such as lyrics.



### Body

Body is a zlib stream that must be inflated.

Number of bytes in the body stream is the number of remaining bytes in the file.


### Bars

Bars are stored differently depending on the version:
```
if 0x70 <= versionNumber:
  bars = read(barCountGE70 * 6)
else:
  bars = read(chunk2)
```

#### 0x70 and newer

For version `0x70` and newer, `bars` is a list of 6 byte records with this structure:

`s3 s2 s1 s0 c v`

The bytes `s3 s2 s1 s0` are an int that specifies how many spaces to increment after this bar.

`c` is a byte that is bit-masked with these values do determine which bar lines to make.
```
0b00000000 = single bar line at beginning of bar
0b00000001 = double bar line at beginning of bar
0b00000010 = open repeat at beginning of bar
0b00000100 = close repeat at end of bar
```

And if there is a close repeat at end of bar, then `v` specifies the number of repeats.


### 0x6f and older

For version `0x6f` and older, `bars` is a chunk2.

After reading the chunk2, there is a delta list that is iterated through.

Each word in the delta list has this structure:

`s c`

`s` is a byte that specifies how many spaces to increment after this word.

`c` is a byte that is bit-masked with these values do determine which bar lines to make.
```
0x00001111 = determines which change to make
0x11110000 = when inserting end repeat, specifies how many repeats
```

After bitmasking with `0x00001111`, the value determines which bar lines to make.
```
0 = skip
1 = insert bar line
2 = insert end repeat
3 = insert start repeat
4 = insert double bar line
```

It is as if each space has only 1 slot, so no need to compute it.



### Notes

For each track, notes are stored in a sequence of chunk2s, and can be read with this pseudo-code:
```
noteList = new list
while True:
  chunk = read(chunk2)
  noteList.append(chunk)
  vsqCount = countVSQ(noteList)
  if vsqCount == 20 * spaceCount:
    break
```

After a complete note list is created, then this is a delta list that is iterated through.

Each word in the delta list has this structure:

`s c`

`s` is a byte that specifies how many vsqs to increment after this word.

`c` is a byte that specifies what value to set for the current slot.

The current slot is computed by `vsqCount % 20`.

For slots 0 to 7:
These are the note values on strings.
Note values can be between `0x80` and `0xe3` (frets and higher numbers for drums, max value is 99, `0x80` + 99 == `0xe3`)
And also: `0x11` for mute string and `0x12` for stop string.

For slots 8 to 15:
These are effects for each string.
```
0: skip
'(': soft
'/': slide up
'<': harmonic
'\\': slide down
'^': bend up
'b': bend
'h': hammer on
'p': pull off
'r': release bend
's': slap
't': tap
'w': whammy bar bend
'{': tremolo
'~': vibrato
```

For slot 16:
These are track effects.
```
0: skip
'C': chorus change
'D': stroke down
'I': instrument change
'P': pan change
'R': reverb change
'T': tempo change
'U': stroke up
'V': volume change
't': tempo change + 250
```

For slot 17:
Single ASCII character for top line text

For slot 18:
Single ASCII character for bottom line text

For slot 19:
The change value for effects or track effects




### Alternate Time Regions

`featureBitfield` from header should be bit-masked with `0b00010000` to determine if there are alternate time regions.

If not, then skip this section.

For each track, Alternate Time Regions are stored in a sequence of chunk2s, and can be read with this pseudo-code:
```
alternateTimeRegionList = new list
while True:
  chunk = read(chunk2)
  noteList.append(chunk)
  dsqCount = countDSQ(noteList)
  if dsqCount == 2 * spaceCount:
    break
```

After a complete alternate time region list is created, then this is a delta list that is iterated through.

Each word in the delta list has this structure:

`s c`

`s` is a byte that specifies how many vsqs to increment after this word.

`c` is a byte that specifies what value to set for the current slot.

The current slot is computed by `vsqCount % 2`.

For slot 0:
This is the denominator. For triplets, this is 2.

For slot 1:
This is the numerator. For triplets, this is 3.


### Effect Changes

If `versionNumber` is `0x70` or below, then skip this section.

For each track, Effect Changes are stored as a chunk4.

After reading the chunk4, there is a list that is iterated through.

Each entry in the list is an 8 byte structure:
`{s1, s0, e1, e0, r1, r0, v1, v0}`

`s1 s0` is a short that specifies how many spaced to increment after this word.

`e1 e0` is a short that specifies the effect to change.

`r1 r0` is a short and reserved and always 0.

`v1 v0` is a short that is the value of the effect change.


Effects are numbered:
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


## References

[^1]: [http://www.tabit.net/](http://www.tabit.net/)











