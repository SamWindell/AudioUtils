#include "pitch_detector.h"

#include "dywapitchtrack/dywapitchtrack.h"

#include "audio_file.h"
#include "common.h"
#include "midi_pitches.h"

CLI::App *PitchDetector::CreateSubcommandCLI(CLI::App &app) {
    auto pitch_detector = app.add_subcommand("pitch-detect", "Prints out the detected pitch of the file");
    return pitch_detector;
}

std::optional<double> PitchDetector::DetectPitch(const AudioFile &input) {
    std::vector<double> channel_pitches;
    ForEachDeinterleavedChannel(
        input.interleaved_samples, input.num_channels, [&](const auto &channel_buffer, auto channel) {
            dywapitchtracker pitch_tracker;
            dywapitch_inittracking(&pitch_tracker);

            auto detected_pitch = dywapitch_computepitch(
                &pitch_tracker, const_cast<double *>(channel_buffer.data()), 0, (int)channel_buffer.size());
            if (input.sample_rate != 44100) {
                detected_pitch *= static_cast<double>(input.sample_rate) / 44100.0;
            }
            channel_pitches.push_back(detected_pitch);
        });

    double average_pitch = 0;
    for (const auto detected_pitch : channel_pitches) {
        if (detected_pitch == 0) {
            average_pitch = 0;
            break;
        }
        average_pitch += detected_pitch;
    }
    average_pitch /= channel_pitches.size();

    return average_pitch;
}

bool PitchDetector::Process(AudioFile &input) {
    if (!input.interleaved_samples.size()) return false;

    const auto pitch = DetectPitch(input);

    if (pitch) {
        const auto closest_musical_note = FindClosestMidiPitch(*pitch);
        MessageWithNewLine("Pitch-Dectector", "Detected a pitch of ", *pitch, "Hz, the closest note is ",
                           closest_musical_note.ToString());
    } else {
        MessageWithNewLine("Pitch-Dectector", "No pitch could be found");
    }
    return false;
}
