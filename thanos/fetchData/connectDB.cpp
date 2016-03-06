
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <mysql/mysql.h>/*注意要包含这个头文件*/


int main()

{

  const char *host = "localhost";

  const char *user = "siukwan";

  const char *pass = "siukwan";

  const char *db   = "thanos";

  MYSQL mysql;

  mysql_init(&mysql);


  if (!mysql_real_connect(&mysql, host, user, pass, db, 0, NULL, 0)) {

    printf("%s", mysql_error(&mysql));

  }

  else {

    printf("YES, Conected succeed!");

  }

  mysql_close(&mysql);

  return 0;

}
