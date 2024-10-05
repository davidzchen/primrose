#include "prim/file/file.h"

#include <cerrno>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "absl/base/nullability.h"
#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "abxl/status/status_macros.h"

namespace prim {

File::File(absl::string_view path, absl::Nonnull<FILE*> stream)
    : path_(std::string(path)), stream_(stream) {}

auto File::Close() -> absl::Status {
  if (stream_ == nullptr) {
    return absl::FailedPreconditionError(
        absl::StrCat("failed to close file ", path_, ": stream is null"));
  }
  fclose(stream_);
  delete this;
  return absl::OkStatus();
}

auto File::Read(absl::Nonnull<std::vector<uint8_t>*> buffer, size_t size)
    -> absl::Status {
  if (stream_ == nullptr) {
    return absl::FailedPreconditionError(
        absl::StrCat("failed to seek file ", path_, ": stream is null"));
  }
  if (buffer == nullptr) {
    return absl::InvalidArgumentError("buffer cannot be null");
  }

  std::vector<uint8_t> buf(size);
  size_t bytes_read = fread(buf.data(), sizeof(uint8_t), size, stream_);
  if (bytes_read != size) {
    return absl::OutOfRangeError(
        absl::StrCat("read ", bytes_read, " bytes from file ", path_,
                     " but expected to read ", size, " bytes."));
  }
  *buffer = buf;
  return absl::OkStatus();
}

auto File::Write(const std::vector<uint8_t>& buffer,
                 absl::Nonnull<size_t*> bytes_written) -> absl::Status {
  if (stream_ == nullptr) {
    return absl::FailedPreconditionError(
        absl::StrCat("failed to seek file ", path_, ": stream is null"));
  }
  if (bytes_written == nullptr) {
    return absl::InvalidArgumentError("bytes_written cannot be null");
  }

  size_t bytes = fwrite(buffer.data(), sizeof(uint8_t), buffer.size(), stream_);
  if (bytes != buffer.size()) {
    return absl::OutOfRangeError(
        absl::StrCat("Wrote ", bytes, " bytes from file ", path_,
                     " but expected to write ", buffer.size(), " bytes."));
  }
  *bytes_written = bytes;
  return absl::OkStatus();
}

auto File::Flush() -> absl::Status {
  if (stream_ == nullptr) {
    return absl::FailedPreconditionError(
        absl::StrCat("failed to seek file ", path_, ": stream is null"));
  }
  int ret = fflush(stream_);
  if (ret == EOF) {
    return absl::UnknownError(
        absl::StrCat("failed to flush file ", path_, ": ", strerror(errno)));
  }
  return absl::OkStatus();
}

auto File::eof() -> bool {
  if (stream_ == nullptr) {
    return true;
  }
  return feof(stream_);
}

auto File::Seek(size_t position) -> absl::Status {
  if (stream_ == nullptr) {
    return absl::FailedPreconditionError(
        absl::StrCat("failed to seek file ", path_, ": stream is null"));
  }
  int ret = fseek(stream_, position, SEEK_SET);
  if (ret != 0) {
    return absl::UnknownError(
        absl::StrCat("failed to seek file ", path_, ": ", strerror(errno)));
  }
  return absl::OkStatus();
}

auto File::Tell(absl::Nonnull<size_t*> position) -> absl::Status {
  if (stream_ == nullptr) {
    return absl::FailedPreconditionError(
        absl::StrCat("failed to tell file ", path_, ": stream is null"));
  }
  *position = ftell(stream_);
  return absl::OkStatus();
}

auto File::Rewind() -> absl::Status { return Seek(0); }

auto File::Size(absl::Nonnull<size_t*> size) -> absl::Status {
  if (stream_ == nullptr) {
    return absl::FailedPreconditionError(
        absl::StrCat("failed to tell file ", path_, ": stream is null"));
  }
  int ret = fseek(stream_, 0, SEEK_END);
  if (ret != 0) {
    return absl::UnknownError(
        absl::StrCat("failed to seek file ", path_, ": ", strerror(errno)));
  }
  size_t sz = ftell(stream_);
  ret = fseek(stream_, 0, SEEK_SET);
  if (ret != 0) {
    return absl::UnknownError(
        absl::StrCat("failed to rewind file ", path_, ": ", strerror(errno)));
  }
  *size = sz;
  return absl::OkStatus();
}

auto Open(absl::string_view path, absl::string_view mode,
          absl::Nonnull<File**> f) -> absl::Status {
  if (f == nullptr) {
    return absl::InvalidArgumentError("f cannot be null");
  }

  FILE* stream = fopen(std::string(path).c_str(), std::string(mode).c_str());
  if (stream == nullptr) {
    return absl::NotFoundError(
        absl::StrCat("failed to open file ", path, ": ", strerror(errno)));
  }
  *f = new File(path, stream);
  return absl::OkStatus();
}

auto ReadFileToBuffer(absl::Nonnull<File*> f,
                      absl::Nonnull<std::vector<uint8_t>*> contents)
    -> absl::Status {
  if (f == nullptr) {
    return absl::InvalidArgumentError("f cannot be null");
  }
  if (contents == nullptr) {
    return absl::InvalidArgumentError("contents cannot be null");
  }

  size_t size;
  RETURN_IF_ERROR(f->Size(&size));
  std::vector<uint8_t> buf;
  RETURN_IF_ERROR(f->Read(&buf, size));

  *contents = buf;
  return absl::OkStatus();
}

auto WriteBuffer(absl::Nonnull<File*> f, const std::vector<uint8_t>& contents)
    -> absl::Status {
  if (f == nullptr) {
    return absl::InvalidArgumentError("f cannot be null");
  }

  RETURN_IF_ERROR(f->Rewind());
  size_t unused;
  RETURN_IF_ERROR(f->Write(contents, &unused));
  return absl::OkStatus();
}

auto GetContents(absl::string_view path,
                 absl::Nonnull<std::vector<uint8_t>*> contents)
    -> absl::Status {
  if (contents == nullptr) {
    return absl::InvalidArgumentError("contents cannot be null");
  }

  File* f;
  RETURN_IF_ERROR(Open(path, "r", &f));
  RETURN_IF_ERROR(ReadFileToBuffer(f, contents));
  return f->Close();
}

auto SetContents(absl::string_view path, const std::vector<uint8_t>& contents)
    -> absl::Status {
  File* f;
  RETURN_IF_ERROR(Open(path, "w", &f));
  RETURN_IF_ERROR(WriteBuffer(f, contents));
  return f->Close();
}

}  // namespace prim
