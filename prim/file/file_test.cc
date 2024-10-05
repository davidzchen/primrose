#include "prim/file/file.h"

#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "abxl/file/path.h"
#include "abxl/status/status_matchers.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::TempDir;
using ::testing::status::IsOk;

namespace prim {
namespace {

TEST(File, Read) {
  File* f;
  EXPECT_THAT(Open("prim/file/testdata/foo", "r", &f), IsOk());

  size_t size;
  EXPECT_THAT(f->Size(&size), IsOk());
  EXPECT_EQ(size, 13);

  std::vector<uint8_t> buffer;
  EXPECT_THAT(f->Read(&buffer, size), IsOk());
  std::string str(buffer.begin(), buffer.end());
  EXPECT_EQ(str, "Sample file.\n");

  EXPECT_THAT(f->Close(), IsOk());
}

TEST(File, SeekTellRewind) {
  File* f;
  EXPECT_THAT(Open("prim/file/testdata/foo", "r", &f), IsOk());

  EXPECT_THAT(f->Seek(10), IsOk());
  size_t position;
  EXPECT_THAT(f->Tell(&position), IsOk());
  EXPECT_EQ(position, 10);

  EXPECT_THAT(f->Rewind(), IsOk());
  EXPECT_THAT(f->Tell(&position), IsOk());
  EXPECT_EQ(position, 0);

  EXPECT_THAT(f->Close(), IsOk());
}

TEST(File, Write) {
  const std::string path = abxl::JoinPath(TempDir(), "foo");

  File* f;
  EXPECT_THAT(Open(path, "w", &f), IsOk());

  const std::string contents = "Sample file.\n";
  const std::vector<uint8_t> write_buffer(contents.begin(), contents.end());
  size_t bytes_written;
  EXPECT_THAT(f->Write(write_buffer, &bytes_written), IsOk());
  EXPECT_EQ(bytes_written, write_buffer.size());
  EXPECT_THAT(f->Close(), IsOk());

  EXPECT_THAT(Open(path, "a", &f), IsOk());
  EXPECT_THAT(f->Write(write_buffer, &bytes_written), IsOk());
  EXPECT_EQ(bytes_written, write_buffer.size());
  EXPECT_THAT(f->Close(), IsOk());

  EXPECT_THAT(Open(path, "r", &f), IsOk());
  size_t size;
  EXPECT_THAT(f->Size(&size), IsOk());
  EXPECT_EQ(size, 26);

  std::vector<uint8_t> read_buffer;
  EXPECT_THAT(f->Read(&read_buffer, size), IsOk());
  std::string got_contents(read_buffer.begin(), read_buffer.end());
  EXPECT_EQ(got_contents, "Sample file.\nSample file.\n");
  EXPECT_THAT(f->Close(), IsOk());
}

TEST(ReadFileToBuffer, Success) {
  File* f;
  EXPECT_THAT(Open("prim/file/testdata/foo", "r", &f), IsOk());

  std::vector<uint8_t> buffer;
  EXPECT_THAT(ReadFileToBuffer(f, &buffer), IsOk());
  std::string str(buffer.begin(), buffer.end());
  EXPECT_EQ(str, "Sample file.\n");

  EXPECT_THAT(f->Close(), IsOk());
}

TEST(GetContents, Success) {
  std::vector<uint8_t> buffer;
  EXPECT_THAT(GetContents("prim/file/testdata/foo", &buffer), IsOk());
  std::string str(buffer.begin(), buffer.end());
  EXPECT_EQ(str, "Sample file.\n");
}

TEST(WriteBuffer, Success) {
  const std::string path = abxl::JoinPath(TempDir(), "foo");

  File* f;
  EXPECT_THAT(Open(path, "w", &f), IsOk());
  const std::string contents = "Sample file.\n";
  const std::vector<uint8_t> write_buffer(contents.begin(), contents.end());
  EXPECT_THAT(WriteBuffer(f, write_buffer), IsOk());
  EXPECT_THAT(f->Close(), IsOk());

  std::vector<uint8_t> read_buffer;
  EXPECT_THAT(GetContents(path, &read_buffer), IsOk());
  std::string got_contents(read_buffer.begin(), read_buffer.end());
  EXPECT_EQ(got_contents, contents);
}

TEST(SetContents, Success) {
  const std::string path = abxl::JoinPath(TempDir(), "foo");

  const std::string contents = "Sample file.\n";
  const std::vector<uint8_t> write_buffer(contents.begin(), contents.end());
  EXPECT_THAT(SetContents(path, write_buffer), IsOk());

  std::vector<uint8_t> read_buffer;
  EXPECT_THAT(GetContents(path, &read_buffer), IsOk());
  std::string got_contents(read_buffer.begin(), read_buffer.end());
  EXPECT_EQ(got_contents, contents);
}

}  // namespace
}  // namespace prim
