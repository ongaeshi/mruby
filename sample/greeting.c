// greeting.c

#include <stdio.h>
#include <mruby.h>
#include <mruby/string.h>

int main()
{
    mrb_state* mrb = mrb_open();

    // mrubyファイルをロードする
    FILE *fd = fopen("person.mrb", "r");
    mrb_load_irep_file(mrb, fd);

    // *.rbを直接ロードする
    // FILE *fd = fopen("person.rb", "r");
    // mrb_load_file(mrb, fd);

    // クラスオブジェクトを取得する
    struct RClass *person = mrb_class_get(mrb, "Person");

    // 引数をmrb_valueに変換する
    mrb_value person_value = mrb_obj_value(person);
    mrb_value name_value = mrb_str_new(mrb, "naoty", 5);
    mrb_value age_value = mrb_fixnum_value(25);

    // Person#newを呼び出す
    mrb_value naoty = mrb_funcall(mrb, person_value, "new", 2, name_value, age_value);

    // Person#greetingを呼び出す
    mrb_value greeting_value = mrb_funcall(mrb, naoty, "greeting", 0);

    // 返り値をchar*に変換して出力する
    char *greeting = mrb_string_value_ptr(mrb, greeting_value);
    printf("%s\n", greeting);

    mrb_close(mrb);
    return 0;
}
