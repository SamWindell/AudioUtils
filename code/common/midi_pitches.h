#pragma once

#include <array>
#include <string>

struct MIDIPitch {
    std::string ToString() const {
        std::array<char, 32> buf {};
        std::snprintf(buf.data(), buf.size(), "%.2f", pitch);
        return std::string(buf.data()) + "Hz (" + name + ": MIDI " + std::to_string(midi_note) + ")";
    }

    int midi_note;
    const char *name;
    double pitch;
};

static constexpr MIDIPitch g_midi_pitches[] = {
    {0, "", 8.18},
    {1, "", 8.66},
    {2, "", 9.18},
    {3, "", 9.72},
    {4, "", 10.3},
    {5, "", 10.91},
    {6, "", 11.56},
    {7, "", 12.25},
    {8, "", 12.98},
    {9, "", 13.75},
    {10, "", 14.57},
    {11, "", 15.43},
    {12, "", 16.35},
    {13, "", 17.32},
    {14, "", 18.35},
    {15, "", 19.45},
    {16, "", 20.6},
    {17, "", 21.83},
    {18, "", 23.12},
    {19, "", 24.5},
    {20, "", 25.96},
    {21, "A0", 27.5},
    {22, "A#0/Bb0", 29.14},
    {23, "B0", 30.87},
    {24, "C1", 32.7},
    {25, "C#1/Db1", 34.65},
    {26, "D1", 36.71},
    {27, "D#1/Eb1", 38.89},
    {28, "E1", 41.2},
    {29, "F1", 43.65},
    {30, "F#1/Gb1", 46.25},
    {31, "G1", 49},
    {32, "G#1/Ab1", 51.91},
    {33, "A1", 55},
    {34, "A#1/Bb1", 58.27},
    {35, "B1", 61.74},
    {36, "C2", 65.41},
    {37, "C#2/Db2", 69.3},
    {38, "D2", 73.42},
    {39, "D#2/Eb2", 77.78},
    {40, "E2", 82.41},
    {41, "F2", 87.31},
    {42, "F#2/Gb2", 92.5},
    {43, "G2", 98},
    {44, "G#2/Ab2", 103.83},
    {45, "A2", 110},
    {46, "A#2/Bb2", 116.54},
    {47, "B2", 123.47},
    {48, "C3", 130.81},
    {49, "C#3/Db3", 138.59},
    {50, "D3", 146.83},
    {51, "D#3/Eb3", 155.56},
    {52, "E3", 164.81},
    {53, "F3", 174.61},
    {54, "F#3/Gb3", 185},
    {55, "G3", 196},
    {56, "G#3/Ab3", 207.65},
    {57, "A3", 220},
    {58, "A#3/Bb3", 233.08},
    {59, "B3", 246.94},
    {60, "C4 (middle C)", 261.63},
    {61, "C#4/Db4", 277.18},
    {62, "D4", 293.66},
    {63, "D#4/Eb4", 311.13},
    {64, "E4", 329.63},
    {65, "F4", 349.23},
    {66, "F#4/Gb4", 369.99},
    {67, "G4", 392},
    {68, "G#4/Ab4", 415.3},
    {69, "A4 (concert pitch)", 440},
    {70, "A#4/Bb4", 466.16},
    {71, "B4", 493.88},
    {72, "C5", 523.25},
    {73, "C#5/Db5", 554.37},
    {74, "D5", 587.33},
    {75, "D#5/Eb5", 622.25},
    {76, "E5", 659.26},
    {77, "F5", 698.46},
    {78, "F#5/Gb5", 739.99},
    {79, "G5", 783.99},
    {80, "G#5/Ab5", 830.61},
    {81, "A5", 880},
    {82, "A#5/Bb5", 932.33},
    {83, "B5", 987.77},
    {84, "C6", 1046.5},
    {85, "C#6/Db6", 1108.73},
    {86, "D6", 1174.66},
    {87, "D#6/Eb6", 1244.51},
    {88, "E6", 1318.51},
    {89, "F6", 1396.91},
    {90, "F#6/Gb6", 1479.98},
    {91, "G6", 1567.98},
    {92, "G#6/Ab6", 1661.22},
    {93, "A6", 1760},
    {94, "A#6/Bb6", 1864.66},
    {95, "B6", 1975.53},
    {96, "C7", 2093},
    {97, "C#7/Db7", 2217.46},
    {98, "D7", 2349.32},
    {99, "D#7/Eb7", 2489.02},
    {100, "E7", 2637.02},
    {101, "F7", 2793.83},
    {102, "F#7/Gb7", 2959.96},
    {103, "G7", 3135.96},
    {104, "G#7/Ab7", 3322.44},
    {105, "A7", 3520},
    {106, "A#7/Bb7", 3729.31},
    {107, "B7", 3951.07},
    {108, "C8", 4186.01},
    {109, "C#8/Db8", 4434.92},
    {110, "D8", 4698.64},
    {111, "D#8/Eb8", 4978.03},
    {112, "E8", 5274.04},
    {113, "F8", 5587.65},
    {114, "F#8/Gb8", 5919.91},
    {115, "G8", 6271.93},
    {116, "G#8/Ab8", 6644.88},
    {117, "A8", 7040},
    {118, "A#8/Bb8", 7458.62},
    {119, "B8", 7902.13},
    {120, "C9", 8372.02},
    {121, "C#9/Db9", 8869.84},
    {122, "D9", 9397.27},
    {123, "D#9/Eb9", 9956.06},
    {124, "E9", 10548.08},
    {125, "F9", 11175.3},
    {126, "F#9/Gb9", 11839.82},
    {127, "G9", 12543.85},
};

MIDIPitch FindClosestMidiPitch(const double freq);
