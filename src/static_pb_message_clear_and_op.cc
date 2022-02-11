#include <iostream>

#include "sample.pb.h"

size_t iter_count = 0;

void static_message_clear_and_op(const std::string docid) {
  static thread_local sample::Sample sample;
  sample.Clear();
  sample.add_docids(docid);

  if (iter_count % 10000 == 0) {
    std::cout << "iter_count: " << iter_count << ", sample size: " << sample.ByteSize() << std::endl;
  }
}

int main() {
  const size_t max_iter = 1 << 40;
  char         buff[512]{0};
  for (size_t i = 0; i < max_iter; ++i) {
    ++iter_count;
    snprintf(buff, sizeof(buff), "iter-%zu", i);
    static_message_clear_and_op(buff);
  }
  return 0;
}