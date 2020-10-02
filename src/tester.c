#include "client.h"

void tester_json2(){
  /* ini bagian tester json part 2*/

  struct json_object *jobj;
  const char *qontol = "Em, sebuah kontol yang besar?";
  const double panjang = 123.123;

  jobj=json_object_new_object();
  json_object_object_add(jobj, "deskripsi", json_object_new_string(qontol));
  json_object_object_add(jobj, "panjang", json_object_new_double(panjang));
  printf("=====JSON=======\n%s\nendSjon\n", json_object_to_json_string_ext(jobj, JSON_C_TO_STRING_PRETTY));
  
  json_object_put(jobj);

}
