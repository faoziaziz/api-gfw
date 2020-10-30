AC_INIT([api-gfw-client], [0.0.2])

# 'foreign' specifies not to create the default GNU-style project files,
# such as touch, NEWS, README, AUTHORS ...
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

# Defaults make verbosity to V=0, so that make generates a prettier, less
# verbose output. To go back to normal comment out the line, or call make with
# the 'V=1' argument to see a normal output.
AM_SILENT_RULES([yes])

AC_PROG_CC

AC_CONFIG_HEADERS([src/config.h])

AC_CONFIG_FILES([
    Makefile
    src/Makefile
])

AC_SEARCH_LIBS([curl_easy_setopt], [curl], [], [
  AC_MSG_ERROR([libcurlnya belum diinstall])
])

AC_SEARCH_LIBS([pthread_join], [pthread], [], [
  AC_MSG_ERROR([pthread belum diinstall])
])

AC_SEARCH_LIBS([sqlite3_libversion], [sqlite3], [], [
  AC_MSG_ERROR([sqlite3 belum diinstall])
])

AC_SEARCH_LIBS([gps_stream], [gps], [], [
  AC_MSG_ERROR([GPS belum diinstall])
])

AC_SEARCH_LIBS([json_object_object_add], [json-c], [], [
  AC_MSG_ERROR([json-c belum diinstall])
])

AC_SEARCH_LIBS([uuid_parse], [uuid], [], [
AC_MSG_ERROR([perlu install uuid-dev.])

])
AC_OUTPUT
