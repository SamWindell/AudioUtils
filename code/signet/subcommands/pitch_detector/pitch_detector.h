#pragma once

#include "subcommand.h"

class PitchDetector final : public Subcommand {
  public:
    CLI::App *CreateSubcommandCLI(CLI::App &app) override;
    void ProcessFiles(const tcb::span<InputAudioFile> files) override;

    static std::optional<double> DetectPitch(const AudioFile &audio);
};
