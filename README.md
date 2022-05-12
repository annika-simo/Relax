# Relax
CS1021 Lab 8

## Introduction
In 2021, researcher Sandvine said that more than [10% of the internet's "downstream" traffic was dedicated to Netflix](https://www.sandvine.com/hubfs/Sandvine_Redesign_2019/Downloads/2022/Phenomena%20Reports/GIPR%202022/Sandvine%20GIPR%20January%202022.pdf?hsCtaTracking=18fff708-438e-4e16-809d-34c3c89f4957%7C067d9d28-ef90-4645-9d46-c70d10279247) and [video, generally, took more than 50% of the bandwidth on the internet](https://www.sandvine.com/hubfs/Sandvine_Redesign_2019/Downloads/2022/Phenomena%20Reports/GIPR%202022/Sandvine%20GIPR%20January%202022.pdf?hsCtaTracking=18fff708-438e-4e16-809d-34c3c89f4957%7C067d9d28-ef90-4645-9d46-c70d10279247). For a single hour of HD video, [Netflix must transfer 3GB of data to a viewer's computer](https://help.netflix.com/en/node/87) -- that's 6 times as much data as I could store on the entire hard drive of my [first computer](http://www.computer-specifications.com/specifications/Sharp-PC3050-Specs.html). According to [Dodo/Statista](https://www.domo.com/learn/infographic/data-never-sleeps-9), in 2021, we humans consumed 79 *zettabytes* of data or 79,000,000,000,000,000,000,000 bytes. Wow.

[Not everyone in America is lucky enough to have access to a broadband Internet connection](https://www.bloomberg.com/news/features/2021-09-22/microsoft-google-part-of-plan-to-get-rural-america-high-speed-internet). "[[D]ifferent types of [medical] images such as Magnetic Resonance Imaging (MRI), Computed Tomography (CT), and ultrasounds can be larger than 100 MB](https://www.sciencedirect.com/science/article/pii/S1386505621002252)". The combination of those big files and slow internet connections hampers the promise of telemedicine!

And then there's software updates! Microsoft and Apple both deliver updates to their operating systems over the Internet. Throughout the life of Windows 10, the updates have averaged about [4.8GB](https://www.zdnet.com/article/windows-10-were-cutting-download-sizes-with-smaller-x64-option-says-microsoft/). That's lots of data to download every time that a hacker finds a vulnerability in Windows that Microsoft needs to patch.

Scientists have engaged in a battle with the ever-increasing size of files by devising compression formats. A compression format is an algorithm designed to squeeze more *information*, a term coined by the influential computer scientist [Claude Shannon](https://en.wikipedia.org/wiki/Claude_Shannon), out of fewer bytes. We do this regularly in our everyday speech and don't even realize it! When we text "sup" instead of "Hello, friend. How are you doing this afternoon?" we are compressing the longer question into something that is easier to type. Our friend mentally decompresses those three letters into the longer question.

There are two different types of compression, lossless and lossy. Computer images are a two dimensional array of picture elements (pixels). Each pixel represents a single dot (of a particular color) in the image. Let's say that each pixel of our professional headshot can be one of 4,294,967,295 different colors. That means that each pixel must have enough space to store all those numbers! On the other hand, if our professional headshot is in black/white, each pixel needs to be only big enough to store a 1 (to represent black) or a 0 (to represent white)! Compressing an image by converting it to black and white saves a tremendous amount of space, but information is lost: the compressed image looks different than the original!

Any compression algorithm that *cannot* recreate *exactly* the original data from its compressed version is lossy (e.g., jpeg, mp3); any compression algorithm that *ca* recreate *exactly* the original data from its compressed version is lossless (e.g., gif, png).

Each execution of a compression algorithm on a particular set of data can be characterized by its compression ratio. The compression ratio is a function of the compression algorithm and the data to be compressed and is the, uhm, ratio of the size of the data after it is compressed by that scheme to the size of the data before it is compressed by that scheme. Let's say that I can use compression algorithm Alpha to compress a song file that is 3MB into a file that is 1.5MB. The compression ratio for the Alpha scheme on that particular file is: 3MB / 1.5MB = 2

In the division, the units cancel -- the compression ratio is a unitless value. The higher the compression ratio, the better the compression scheme. [The most basic version of the compression scheme used by Netflix, Amazon Prime, etc. has a compression ratio of 1000](https://www.rgb.com/) -- wow! Just remember that the compression ratio depends on both the compression algorithm and the data to be compressed. The same compression algorithm can have a high and low compression ratio depending on the data to be compressed (see the Critical Thinking Task for more).

Let's revisit our discussion about storing images in the computer. We will attempt to store a black/white image. In our file format, every pixel that is black is stored as `B` and every pixel that is white is stored as `W`. An image of the letter i would be encoded like this:

```
W  W  W  W  W  W  W  W  W
W  W  W  W  B  W  W  W  W
W  W  W  W  W  W  W  W  W
W  W  W  W  B  W  W  W  W
W  W  W  W  B  W  W  W  W
W  W  W  W  B  W  W  W  W
W  W  W  W  B  W  W  W  W
W  W  W  W  B  W  W  W  W
W  W  W  W  B  W  W  W  W
```

Do you see what I see? I thought you would. Look at all those `W`s in a row! What if, instead of writing each `W` in a sequence of `W`s, we just said, for example, "Hey, the next 11 pixels are `W`s". Brilliant idea!

Uncompressed:	`WWWWWWWWWWW`
Compressed:	`11W`
For the example above, this compression scheme results in a compression ratio of \frac{len\left(WWWWWWWWWWW\right)}{len\left(11W\right)}=\frac{11}{3}=\text{3.66666666667}. len(WWWWWWWWWWW) / len(11W) = 11 / 3 = 3.66666666667,

This idea for compression is so good that computer scientists have given it a name: [Run-length encoding](https://en.wikipedia.org/wiki/Run-length_encoding). Run-length encoding has been used productively for over 50 years! In this lab you are going to write code that
1. decompresses a file that is run-length encoded,
2. prints the decompressed contents, and
3. calculates and displays the compression ratio.

The run-length encoded file you decompress (always named `input.rle`) will contain a series of encoded entries on a single line. In the simple case, an encoded entry consists of a number and a character. For example, `3n`. When decompressed, that would be `nnn`. To encode a sequence of digits, the format is slightly more complicated: an encoded entry consists of a number, a dash, and a digit. For example, `4-2`. When decompressed, that would be `2222`. The string `bookkeeper99` (my Internet handle), would be encoded as: `1b2o2k2e1p1e1r2-9` with a compression ratio of 0.71 (not very good!).

Good luck!

## Program Design Task
As my dad always said, “Hold on, loosely.” Before you start writing code, please write the pseudocode or draw a flow chart for your implementation of the Relax data decompression application.

## Program Design Requirements
Your pseudocode (or flow chart) must describe the entirety of the process you plan to use to

1. Open the encoded file,
2. Read each encoded entry from the file,
3. Decompress each encoded entry from the file,
4. Display the decompressed data on the screen,
5. Calculate the compression ratio, and
6. Display the compression ratio on the screen.

## Programming Task
Your programming task is to implement the *Relax* application. Your application will *always* decompress data stored in a file named `input.rle`. If *Relax* cannot open the file to decompress (again, named `input.rle`), it must output

```
Could not open the file containing the compressed data!
```

and exit.

The data in the `input.rle` will contain a series of encoded entries on a single line. Encoded entries come in two flavors:

1. a number, n, and a character, c. For example, `3n`. Such an entry decompressed is n cs. For example, `nnn`.
2. a number, n, a dash, and a digit, d. For example, `4-2`. Such an entry decompressed is n ds. For example, `2222`.

If Relax encounters data in the encoded file that do not match the file specifications, it must output

```
Compressed data format error!
```

and exit.

Once the data in `input.rle` is decoded, *Relax* will print the decompressed result to the screen on a single line. On the next line, *Relax* will print the compression ratio after rounding to the second decimal point. *Relax* will always

1. display two numbers after the `.` in the compression ratio, even if they are both 0, and
2. display 0 before the `.` if the compression ratio is less than 1.

If `input.rle` contains

```
1b2o2k2e1p1e1r
```

Relax will print

```
bookkeeper
0.71
```

You may use the following given function(s):

| Name	| Parameters	| Return Type |	Semantics |
| --- | --- | --- | --- |
| `format_compression_ratio`	| A double named `compression_ratio`. | `std::string` |	`format_compression_ratio` will return a properly formatted version of `compression_ratio` (according to the specifications in this lab document).
| `data_available`	| A `std::ifstream` (by reference) named `file`. | `bool`	| `data_available` will return `true` if there is more data to be read from `file`. It will return `false` otherwise. |

Although you are not required to write any particular function to complete this lab, you are required to write modular code. In other words, you *will* write functions as you implement the *Relax* application [(click)](https://en.wikipedia.org/wiki/Spaghetti_code). Any function that you write must contain comments formatted according to the following specification:

```cpp
/*
 * <function name>
 *
 * <short description of what the function does>
 *
 * input: <short description of all input parameters>
 * output: <short description of all output parameters
 *          and the return value>
 */
 ```
 
## Programming Requirements
If you are a Windows user, start with the skeleton .zip in this repository. This skeleton provides the starting point for a successful implementation of the *Relax* decompression application. In addition to workspaces that will make compiling easier, the skeleton contains two (2) compressed files that you can use to check your implementation.

When your `input.rle` file contains

```
1b2o2k2e1p1e1r
```

the proper output is

```
bookkeeper
0.71
```

When your `input.rle` file contains

```
1m1i2si2s1i2p1i
```

the proper output is
```
Compressed data format error!
```

All requirements/assumptions for this application are given in the section above, Programming Task.

## Critical Thinking Task
Developers of compression algorithms often have domain-specific knowledge of the data they are compressing. The developers use this information to customize the compression schemes to leverage existing patterns in the data to increase the performance of their algorithms. For example, a developer of a scheme to encode speech might take advantage of the fact that there are (relatively) long pauses in a person's enunciation. Or, a developer of a scheme to encode the moves of a player in a video game can take advantage of knowing the rules of the game and come up with an algorithm optimized to compress the representation of only valid moves.

Your job in this critical thinking task is to

1. Describe the type of data for which run-length encoding is well suited -- in other words, describe the patterns of data that a run-length encoding scheme will compress well.
2. Find a real-world example of data that run-length encoding would be highly effective at compressing.

## Critical Thinking Requirement
In 500 words or less, describe the type of data for which run-length encoding is well suited and give a real-world example of data where run-length encoding would be highly effective. All references to external resources must be properly documented and formatted. The choice of formatting for external references is up to you, but you may find it helpful to consult the Purdue OWL for [information](https://owl.purdue.edu/owl/research_and_citation/apa_style/apa_style_introduction.html). The Purdue OWL also has extensive information on ways to [avoid plagiarism](https://owl.purdue.edu/owl/avoiding_plagiarism/index.html).

## Deliverables
1. The pseudocode describing the algorithms you used to implement the Relax decompression application in PDF format (named `design.pdf`).
2. The C++ source code for the Relax application (named `relax.cpp`).
3. The response to the Critical Thinking prompts in PDF format (named `domain.pdf`)

## Related Learning Objectives
1. Writing boolean expressions using relational and logical operators
2. Using if-statements to implement selective program execution
3. Using algorithmic thinking to design programs
4. Writing a complete program from scratch
5. Writing syntactically correct for/while loops
Using methods on objects
