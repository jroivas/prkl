#ifndef PRKL_CREATE_H
#define PRKL_CREATE_H

#include "prkl_types.h"

int db_create(DB **database, DB_ENV *database_env, uint32_t flags);
char *db_strerror(int error);

#endif
