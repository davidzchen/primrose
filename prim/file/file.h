#ifndef PRIM_FILE_FILE_H_
#define PRIM_FILE_FILE_H_

#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>

#include "absl/base/nullability.h"
#include "absl/status/status.h"
#include "absl/strings/string_view.h"

namespace prim {

class File {
 public:
  File(absl::string_view path, absl::Nonnull<FILE*> stream);

  // Closes the file and destructs the file object.
  auto Close() -> absl::Status;

  // Reads n bytes from the file into the buffer.
  auto Read(absl::Nonnull<std::vector<uint8_t>*> buffer, size_t size)
      -> absl::Status;

  // Writes the contents of the buffer into the file. The number of bytes
  // written is returned in the bytes_written output parameter.
  auto Write(const std::vector<uint8_t>& buffer,
             absl::Nonnull<size_t*> bytes_written) -> absl::Status;

  // Flushes the file, syncing its contents to disk.
  auto Flush() -> absl::Status;

  // Returns whether the file position indicator is at the end of the file.
  auto eof() -> bool;

  // Seeks to the specified position in bytes relative to the beginning of the
  // file.
  auto Seek(size_t position) -> absl::Status;

  // Retrieves the current position in the file.
  auto Tell(absl::Nonnull<size_t*> position) -> absl::Status;

  // Moves the file position indicator back to the beginning of the file.
  auto Rewind() -> absl::Status;

  // Gets the size of the file in bytes.
  auto Size(absl::Nonnull<size_t*> size) -> absl::Status;

 private:
  std::string path_;
  FILE* stream_;
};

// Factory function to open the file at the given path with the specified mode.
auto Open(absl::string_view path, absl::string_view mode,
          absl::Nonnull<File**> f) -> absl::Status;

// Reads the contents of the file into the buffer.
auto ReadFileToBuffer(absl::Nonnull<File*> f,
                      absl::Nonnull<std::vector<uint8_t>*> contents)
    -> absl::Status;

// Opens the file at the specified path and reads the contents of the file into
// the buffer.
auto GetContents(absl::string_view path,
                 absl::Nonnull<std::vector<uint8_t>*> contents) -> absl::Status;

// Overwrites the contents of the file with the provided contents.
auto SetContents(absl::string_view path, const std::vector<uint8_t>& contents)
    -> absl::Status;

// Writes the contents of the buffer into the file. This overwrites any content
// the file previously contained.
auto WriteBuffer(absl::Nonnull<File*> f, const std::vector<uint8_t>& contents)
    -> absl::Status;

}  // namespace prim

#endif  // PRIM_FILE_FILE_H_
