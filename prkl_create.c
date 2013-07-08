#include "prkl_create.h"
#include <stdlib.h>
#include <errno.h>

struct _PRKL_DATA {

};

int _db_open(DB *db, DB_TXN *txnid, const char *file, const char *database, DBTYPE type, u_int32_t flags, int mode)
{
}

int create_db(DB **database, DB_ENV *database_env, uint32_t flags)
{
    if (database == NULL) return EINVAL;

    DB *db = calloc(1, sizeof(DB));
    *database = db;
    db->open = _db_open;
}
