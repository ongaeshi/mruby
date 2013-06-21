#include <mruby.h>
#include <mruby/compile.h>
#include <mruby/string.h>

static mrb_value plus(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;
  mrb_get_args(mrb, "oo", &a, &b);
  if (mrb_fixnum_p(a) && mrb_fixnum_p(b)) {
    mrb_int x = mrb_fixnum(a);
    mrb_int y = mrb_fixnum(b);
    return mrb_fixnum_value(x + y);
  } else if (mrb_string_p(a) && mrb_string_p(b)) {
    mrb_value s = mrb_str_plus(mrb, a, b);
    return s;
  } else {
    return mrb_nil_value();
  }
}

int main() {
  mrb_state* mrb = mrb_open();
  mrb_define_method(mrb, mrb->kernel_module, "plus", plus, MRB_ARGS_REQ(2));

  mrb_load_string(mrb,
                  "puts plus(1, 2);"
                  "puts plus('foo', 'bar');"
                  );
  if (mrb->exc) { // エラー処理
    mrb_p(mrb, mrb_obj_value(mrb->exc));
  }
  mrb_close(mrb);
  return 0;
}
// 実行結果：
// 3
// foobar
