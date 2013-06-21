#include <mruby.h>
#include <mruby/compile.h>
#include <mruby/string.h>

static mrb_value myabs(mrb_state *mrb, mrb_value self) {
  mrb_value value;
  mrb_get_args(mrb, "o", &value);
  mrb_int x = mrb_fixnum(value);
  // printf("myabs %d\n", x);

  if (x > 0)
      return mrb_fixnum_value(x);
  else
      return mrb_fixnum_value(-x);
}

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
  mrb_define_method(mrb, mrb->kernel_module, "myabs", myabs, MRB_ARGS_REQ(1));

  mrb_load_string(mrb,
                  "puts plus(1, 2);"
                  "puts plus('foo', 'bar');"
                  "puts myabs(-11);"
                  "puts myabs(332311);"
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
