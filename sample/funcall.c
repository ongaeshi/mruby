#include <mruby.h>

int main() {
  mrb_state* mrb = mrb_open();
  mrb_value v = mrb_str_new_cstr(mrb, "Hello, mrb func!");
  mrb_funcall(mrb, mrb_top_self(mrb), "puts", 1, v);
  mrb_close(mrb);
  return 0;
}
