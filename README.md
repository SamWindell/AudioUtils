# Signet
## Command-line program for editing audio files, and assisting sample library development (still a work-in-progress)

![Build Status](https://github.com/SamWindell/Signet/workflows/Build%20and%20Test/badge.svg)

## Table of Contents

- [Signet](#signet)
  - [Command-line program for editing audio files, and assisting sample library development (still a work-in-progress)](#command-line-program-for-editing-audio-files-and-assisting-sample-library-development-still-a-work-in-progress)
  - [Table of Contents](#table-of-contents)
  - [Overview](#overview)
  - [Limitations](#limitations)
  - [Building](#building)
  - [Examples](#examples)
  - [Key Features](#key-features)
    - [Process files, whole folders or pattern-matching filenames](#process-files-whole-folders-or-pattern-matching-filenames)
    - [Comprehensive help text](#comprehensive-help-text)
    - [Undo](#undo)
    - [Commands](#commands)
  - [Documentation](#documentation)

## Overview
Signet makes sample library development (multi-sampling) easier and more effective by offering a suite of tools covering these areas:
- Bulk editing audio files
- Bulk renaming audio files
- Bulk organising files (moving them into folders)
- Generating files based off of existing files

Signet is not exclusively useful for sample library development though. The editing features in particular could be useful to anyone working with large sets of audio files.

## Limitations
Currently only supports reading and writing WAV and FLAC files.

## Building
To get Signet, you currently have to build it from the source code. However, this process is designed to be simple for those familiar with building C++ programs. There are no library dependencies external to this repo. Just run CMake to generate a configuration for your preferred build tool (Visual Studio Solution, makefile, etc.), and then build using that.

A C++17 compiler is required. Tested with MSVC 16.5.1 and Apple Clang 11.0.0.

## Examples
The general pattern is `signet <input-files> <command>`. You can have one or more commands, in which case they will process the input-files one after each other in the order that you specify them.

Adds a fade-in of 1 second to filename.wav

```signet filename.wav fade in 1s```

Auto-tunes all the audio files in the directory 'untuned-files' to their nearest musical pitch

```signet untuned-files auto-tune```

Normalises (to a common gain) all .wav files in the current directory to -3dB

```signet *.wav norm -3```

Normalises (to a common gain) filename1.wav and filename2.flac to -1dB

```signet filename1.wav filename2.flac norm -1```

Offsets the start of each file to the nearest zero-crossing within the first 100 milliseconds. Performs this for all .wav files in any subfolder (recursively) of sampler that starts with "session", excluding files in "session 2" that end with "-unprocessed.wav".

```signet "sampler/session*/**.wav" "-sampler/session 2/*-unprocessed.wav" zcross-offset 100ms```

Rename any file in any of the folders of "one-shots" that match the regex "(.\*)-a". They shall renamed to the whatever group index 1 of the match was, with a -b suffix.

```signet "one-shots/**/.*" rename (.*)-a <1>-b```

Convert all audio files in the folder "my_folder" (not recursively) to a sample rate of 44100Hz and a bit-depth of 24.

```signet my_folder convert sample-rate 44100 bit-depth 24```

## Key Features
### Process files, whole folders or pattern-matching filenames
Signet is flexible in terms of what files to process. You can specify one or more of any of the following input options: 
- A single file such as `file.wav`.
- A directory such as `sounds/unprocessed`. In this case Signet will search for all audio files in that directory and process them all. You can specify the option `--recursive` to make this also search subfolders.
- A glob-style filename pattern. You can use `*` to match any non-slash character and use `**` to match any character. So essentially use `**` to signify recursively searching folders. For example `*.wav` will match any file that has a `.wav` extension in the current folder. `unprocessed/**/*.wav` will match any file with the `.wav` extension in the `unprocessed` folder and any subfolder of it.

You can exclude certain files from being processed by prefixing them with a dash. For example `"file.*" "-*.wav"` will match all files in the current directory that start with `file`, except those with the `.wav` extension.

Input files are processed and then saved back to file (overwritten). Signet features a simple undo option that will restore any files that you overwrote in the last call.

### Comprehensive help text
Care has been taken to ensure the help text is comprehensive and understandable. Run signet with the option `--help` to see information about the available options. Run with `--help-all` to see all the available commands. You can also add `--help` after a command to see the options of that command specifically. For example:

```signet --help```

```signet --help-all```

```signet auto-tune --help```

```signet fade --help-all```

```signet convert file-format --help```

### Undo
Signet overwrites the files that it processes. It is therefore advisable to make a copy your audio files before processing them with Signet.

However, Signet can help with safety too. It features a simple undo system. You can undo any changes made in the previous run of Signet by running it again with the `--undo` option. For example `signet --undo`.

Files that were overwritten are restored, new files that were created are destroyed, and files that were renamed are un-renamed. You can only undo once - you cannot keep going back in history.

### Commands
There are lots of ways to process audio files using Signet. See the [documentation](docs/usage.md) for the full list. Here some of them:
- Detect the pitch of the files and print it out
- Auto-tune files to their nearest musical pitch
- Convert sample-rate, bit-depth and file-format
- Embed sampler metadata to the wav/flac file - the root note can be auto detected
- Rename files - including auto-mapping MIDI regions
- Change pitch
- Filter
- Normalise
- Remove silence from start/end
- Make into seamless loops
- Fade in/out

## Documentation
[See the documentation page.](docs/usage.md)


