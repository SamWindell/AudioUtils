#include "input_files.h"

#include "common.h"

InputAudioFiles::InputAudioFiles(const std::string &pathnames_comma_delimed,
                                 const bool recursive_directory_search) {
    std::string parse_error;
    const auto all_matched_filenames =
        FilePathSet::CreateFromPatterns(pathnames_comma_delimed, recursive_directory_search, &parse_error);
    if (!all_matched_filenames) {
        throw CLI::ValidationError("Input files", parse_error);
    }

    if (all_matched_filenames->Size() == 0) {
        throw CLI::ValidationError("Input files",
                                   "there are no files that match the pattern " + pathnames_comma_delimed);
    }

    m_is_single_file = all_matched_filenames->IsSingleFile();
    ReadAllAudioFiles(*all_matched_filenames);
}

void InputAudioFiles::ReadAllAudioFiles(const FilePathSet &paths) {
    for (const auto &path : paths) {
        if (!IsAudioFileReadable(path)) continue;
        m_all_files.push_back({path});
    }
}

bool InputAudioFiles::WouldWritingAllFilesCreateConflicts() {
    std::unordered_set<std::string> files_set;
    bool file_conflicts = false;
    for (const auto &f : GetAllFiles()) {
        const auto generic = f.GetPath().generic_string();
        if (files_set.find(generic) != files_set.end()) {
            ErrorWithNewLine("filepath ", generic, " would have the same filename as another file");
            file_conflicts = true;
        }
        files_set.insert(generic);
    }
    if (file_conflicts) {
        ErrorWithNewLine("files could be unexpectedly overwritten, please review your renaming settings, "
                         "no action will be taken now");
        return true;
    }
    return false;
}

static fs::path PathWithNewExtension(fs::path path, AudioFileFormat format) {
    path.replace_extension(GetLowercaseExtension(format));
    return path;
}

bool InputAudioFiles::WriteAllAudioFiles(SignetBackup &backup) {
    if (WouldWritingAllFilesCreateConflicts()) {
        return false;
    }

    for (auto &file : GetAllFiles()) {
        const bool file_data_changed = file.AudioChanged();
        const bool file_renamed = file.FilepathChanged();
        const bool file_format_changed = file.FormatChanged();

        if (file_renamed) {
            if (!file_data_changed && !file_format_changed) {
                // only renamed
                backup.MoveFile(file.original_path, file.GetPath());
            } else if ((!file_data_changed && file_format_changed) ||
                       (file_data_changed && file_format_changed)) {
                // renamed and new format
                backup.CreateFile(PathWithNewExtension(file.GetPath(), file.GetAudio().format),
                                  file.GetAudio());
                backup.DeleteFile(file.original_path);
            } else if (file_data_changed && !file_format_changed) {
                // renamed and new data
                backup.CreateFile(file.GetPath(), file.GetAudio());
                backup.DeleteFile(file.original_path);
            }
        } else {
            REQUIRE(file.GetPath() == file.original_path);
            if ((file_format_changed && !file_data_changed) || (file_format_changed && file_data_changed)) {
                // only new format
                backup.CreateFile(PathWithNewExtension(file.original_path, file.GetAudio().format),
                                  file.GetAudio());
                backup.DeleteFile(file.original_path);
            } else if (!file_format_changed && file_data_changed) {
                // only new data
                backup.OverwriteFile(file.original_path, file.GetAudio());
            }
        }
    }
    return true;
}
