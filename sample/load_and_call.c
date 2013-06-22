#include <stdio.h>
#include <mruby.h>
#include <mruby/string.h>

int main()
{
    mrb_state* mrb = mrb_open();

    // *.rbを直接ロードする
    FILE *fd = fopen("load_and_call.rb", "r");
    mrb_load_file(mrb, fd);

    // setupを呼び出す
    mrb_funcall(mrb, mrb_obj_value(mrb->kernel_module), "setup", 0);

    int i;
    for (i = 0; i < 10; i++) {
        mrb_funcall(mrb, mrb_obj_value(mrb->kernel_module), "update", 0);
        mrb_funcall(mrb, mrb_obj_value(mrb->kernel_module), "draw", 0);
        if (mrb->exc) {
            mrb_p(mrb, mrb_obj_value(mrb->exc));
        }
    }

    mrb_close(mrb);
    return 0;
}
