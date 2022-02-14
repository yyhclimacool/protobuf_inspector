#include <iostream>

#include <google/protobuf/arena.h>

#include "sample.pb.h"

size_t iter_count = 0;
int current_size = 0;

void static_message_clear_and_op(const std::string docid) {
  google::protobuf::ArenaOptions opt;
  opt.start_block_size = 128 * (1 << 10);
  opt.max_block_size = 128 * (1 << 10);
  //opt.block_alloc = predictor_arena_malloc;
  //opt.block_dealloc = predictor_arena_free;
  void *_initial_block = malloc(102400);
  opt.initial_block = static_cast<char*>(_initial_block);
  opt.initial_block_size = 102400;
  auto *_arena = new google::protobuf::Arena(opt);

  inspector::Sample *sample = google::protobuf::Arena::CreateMessage<inspector::Sample>(_arena);
  sample->add_docids(docid);

  for (int i = 0; i != 10; ++i) {
    auto *uf = sample->add_user_feature();
    uf->set_uid(docid);
    for (size_t start = 0; start != 100; ++start) {
      uf->add_short_interest("test_interest");
    }
  }

  if (iter_count % 10000 == 0) {
    if (sample->ByteSize() != current_size) {
      std::cout << "iter_count: " << iter_count << ", sample size: " << sample->ByteSize() << std::endl;
      current_size = sample->ByteSize();
    }
  }
  // no need to delete sample, delete arena is sufficient.
  delete _arena;
}

int main() {
  const size_t max_iter = 1ul << 20;
  char         buff[512]{0};
  for (size_t i = 0; i < max_iter; ++i) {
    ++iter_count;
    snprintf(buff, sizeof(buff), "iter-%zu", i);
    static_message_clear_and_op(buff);
  }
  return 0;
}
