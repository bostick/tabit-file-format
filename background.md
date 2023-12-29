
# TabIt Background

This document describes the background of TabIt, a Windows application that is described in its [website](http://www.tabit.net) as

> a full-featured program for creating, playing, and printing guitar, bass, or banjo tablature.

TabIt is sold by GTAB Software.

The latest version of TabIt, version 2.03, was released in 2006.

TabIt is effectively abandonware.


## Community

There is a semi-active TabIt [subreddit](https://reddit.com/r/tabit/).

[Tablature Area](https://tabarea.net/) is a mirror of the tabs from tabit.net.


## The Crisis

On November 10th, 2019, the [Tablature Area](www.tabit.net/tabs) went down.


From tabit.net:

> Update as of Feb. 26, 2020:

> Sorry for the continued delay, folks. Work has begun on getting the Tablature Area ready, but finding the time to complete the job has proven difficult. Still no ETA yet, I'm afraid. This page will be updated again when there is more progress to report.

> And FYI, this server move was not planned. It had to happen because the previous hosting provider shut down their data center on relatively short notice.


And since at least June 2021:

> Update as of June 29:

> Since most users are mainly interested in just downloading tabs that already existed in the Tablature Area, I've decided for now to focus on trying to bring the Tablature Area up in a "read-only" state — i.e., with no ability to log in, upload tabs, or rate tabs — rather than holding off until the entire site is 100% ready. Will post another update when progress is made on that.

> Tech details for those curious: The Tablature Area was built on PHP 5, which has reached end-of-life and is no longer available on modern servers. Getting it to work on PHP 7+ requires a lot of changes across the code base, mainly because they dropped the "mysql" extension (which was a very unwelcome surprise!). There may be various other PHP 7 or MySQL 8.0 incompatibilities which I haven't uncovered yet; each page will require careful re-testing before being made accessible to the public.



## TabIt version numbers

TabIt files have a version number and a version string.

The version string may be the same for different version numbers.

Files stored with version number `0x65` store version string "1.0".

Files stored with version number `0x66` store version string "1.11".

Files stored with version number `0x67` store version string "1.2".

Files stored with version number `0x68` store version string "1.22".

Files stored with version number `0x69` store version string "1.23".

Files stored with version number `0x6a` store version string "1.3".

Files stored with version number `0x6b` store version string "1.4".

Files stored with version number `0x6e` store version string "1.55".

Files stored with version number `0x6f` store version string "1.6".

Files stored with version number `0x70` store version string "2.0".

Files stored with version number `0x71` store version string "2.0".

Files stored with version number `0x72` store version string "2.0".

The version strings correspond roughly to released versions of TabIt.



## History of TabIt releases

* [1.43](https://web.archive.org/web/20001206181300/http://www.tabit.net/download.htm)

* [1.52](https://web.archive.org/web/20010406041925/http://www.tabit.net/download.htm)

<!-- https://web.archive.org/web/20010609064805/http://members.aol.com/tabitsoftware/WinTabIt152.exe -->

* [1.57](https://web.archive.org/web/20010813114532/http://tabit.net/download.htm)

* [1.58](https://web.archive.org/web/20020408145006/http://tabit.net/download.htm)

* [1.59](https://web.archive.org/web/20021012041140/http://tabit.net/download.htm)

<!-- https://web.archive.org/web/20021010181902/http://www.tabit.net/files/WinTabIt159.exe -->

* [1.61](https://web.archive.org/web/20031002082703/http://www.tabit.net/download.htm)

* [1.62](https://web.archive.org/web/20040209103438/http://tabit.net/download.htm)

* [2.02](https://web.archive.org/web/20060925180247/http://www.tabit.net/download.htm)

* [2.03](https://web.archive.org/web/20070727152913/http://www.tabit.net/download.htm)


Version `0x6a` added "display MIDI note numbers" and MIDI channel.

Version `0x6b` increased the number of allowed strings to 8, and added pan and highest note.

Version `0x6c` added reverb and chorus.

Version `0x6d` added "transpose half steps" and MIDI bank, and album and transcribedBy.

Version `0x6f` increased the number of allowed spaces from 4000 to 32000.

Version `0x70` added Alternate Time Regions.

Version `0x71` added modulation and pitch bend.

Note that `0x71` is "unstable", which means that resaving `0x71` files saves them as `0x72` files.

Version `0x72` added multiple changes at the same time.


TabIt 2.03 may save files as different versions depending on the features that the file uses.

* No special features are used: saved as version `0x6f`

* Uses Alternate Time Regions: saved as version `0x70`

* Uses modulation or pitch bending: saved as version `0x72`




