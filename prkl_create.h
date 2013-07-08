#ifndef PRKL_CREATE_H
#define PRKL_CREATE_H

#include "prkl_types.h"

int create_db(DB **database, DB_ENV *database_env, uint32_t flags);

#endif
