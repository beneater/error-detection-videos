# Error detection video series

Copyright 2018-2019 Ben Eater

This code is [MIT licensed](http://en.wikipedia.org/wiki/MIT_License).

## What is this?

This repo contains the code to accompany a YouTube mini-series on reliable communication, error detection, and correction. To have any idea what's going on here, you should watch the videos:


## Reliable data transmission

[<img src=https://img.youtube.com/vi/eq5YpKHXJDM/maxresdefault.jpg width=360/>](https://www.youtube.com/watch?v=eq5YpKHXJDM)

This is the first video in the series and covers mostly setup for the future videos. In the video we build a simple transmitter and receiver:

 * [`/transmitter`](/transmitter)
 * [`/receiver`](/receiver)


## Parity checking

[<img src=https://img.youtube.com/vi/MgkhrBSjhag/maxresdefault.jpg width=360/>](https://www.youtube.com/watch?v=MgkhrBSjhag)

Parity checking is a basic technique for detecting errors in data transmission. This video explains how it works and walks through building hardware to compute and check parity. The receiver code is identical to the previous video. The transmitter is only slightly different:

 * [`/transmitter-parity`](/transmitter-parity)
 * [`/receiver`](/receiver)

## Checksums and Hamming distance

[<img src=https://img.youtube.com/vi/ppU41c15Xho/maxresdefault.jpg width=360/>](https://www.youtube.com/watch?v=ppU41c15Xho)

The term "checksum" can refer to all sorts of different error detection codes. This video explains how some are better than others. What types of errors are they good at detecting? And how do you calculate different types of checksums? There's no code for this video.

## How do CRCs work?

[<img src=https://img.youtube.com/vi/izG7qT0EpBw/maxresdefault.jpg width=360/>](https://www.youtube.com/watch?v=izG7qT0EpBw)

CRC (cyclic redundancy check) is one of the most common methods of error detection. It uses some interesting mathematical tricks to guarantee that it can catch certain kinds of errors. How does it work? There's no code for this video.

## Hardware build: CRC calculation

[<img src=https://img.youtube.com/vi/sNkERQlK8j8/maxresdefault.jpg width=360/>](https://www.youtube.com/watch?v=sNkERQlK8j8)

CRC (cyclic redundancy check) involves some intimidating math. But it turns out that it can all be done with some fairly simple hardware. In this video, I build the hardware to compute and verify CRCs. The receiver code is still identical to the first video. The transmitter code includes some additional control signals to push data into the CRC circuit and retrieve the result:

 * [`/transmitter-crc`](/transmitter-crc)
 * [`/receiver`](/receiver)
