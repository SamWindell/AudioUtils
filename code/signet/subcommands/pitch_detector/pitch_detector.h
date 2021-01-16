#pragma once

#include "subcommand.h"

class PitchDetector final : public Subcommand {
  public:
    CLI::App *CreateSubcommandCLI(CLI::App &app) override;
    void ProcessFiles(AudioFiles &files) override;
    std::string GetName() const override { return "PitchDetector"; }

    static std::optional<double> DetectPitch(const AudioData &audio);
};
