#pragma once

#include <optional>

#include "subcommand.h"

class Folderiser final : public Subcommand {
  public:
    CLI::App *CreateSubcommandCLI(CLI::App &app) override;
    void ProcessFiles(const tcb::span<EditTrackedAudioFile> files) override;
    std::string GetName() override { return "Folderiser"; }

  private:
    std::string m_filename_pattern;
    std::string m_out_folder;
};
