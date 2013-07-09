#include "prkl_create.h"
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>

#include <lmdb.h>

struct _PRKL_DATA {
    MDB_dbi dbi;
    MDB_env *env;
    MDB_txn *txn;
};

int _db_open(DB *db, DB_TXN *txnid, const char *file, const char *database, DBTYPE type, uint32_t flags, int mode)
{
    printf("%s\n", __FUNCTION__);
    if (db == NULL) return EINVAL;

    mdb_env_open(db->_internal->env, "./", /*MDB_FIXEDMAP*/0, mode);

    if (txnid == NULL) {
        if (mdb_txn_begin(db->_internal->env, NULL, 0, &db->_internal->txn) != 0) return EINVAL;
    } else {
        if (mdb_txn_begin(db->_internal->env, txnid->_internal->txn, 0, &db->_internal->txn) != 0) return EINVAL;
    }

    uint32_t _flags = 0;
    if (flags & DB_CREATE) _flags |= MDB_CREATE;

    if (mdb_dbi_open(db->_internal->txn, database, _flags, &db->_internal->dbi) !=0 ) {
        mdb_txn_abort(db->_internal->txn);
        return EINVAL;
    }
    mdb_txn_commit(db->_internal->txn);

    return 0;
}

void _db_err(DB *db, int error, const char *fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    fprintf(stderr, "ERROR %d: ", error);
    vfprintf(stderr, fmt, vl);
    fprintf(stderr, "\n");
    va_end(vl);
}

int _db_close(DB *db, uint32_t flags)
{
    if (db == NULL) return EINVAL;

    mdb_dbi_close(db->_internal->env, db->_internal->dbi);
    free(db->_internal);

    free(db);

    return 0;
}

int _db_get(DB *db, DB_TXN *txnid, DBT *key, DBT *data, uint32_t flags)
{
    //FIXME
    printf("%s\n", __FUNCTION__);

    MDB_val _key;
    MDB_val _data;

    _key.mv_size = key->size;
    _key.mv_data = key->data;

    if (mdb_txn_begin(db->_internal->env, NULL, 0, &db->_internal->txn) != 0) return EINVAL;

    mdb_get(db->_internal->txn, db->_internal->dbi, &_key, &_data);
    mdb_txn_commit(db->_internal->txn);

    data->size  = _data.mv_size;
    data->data = _data.mv_data;

    return 0;
}

int _db_put(DB *db, DB_TXN *txnid, DBT *key, DBT *data, uint32_t flags)
{
    //FIXME
    printf("%s\n", __FUNCTION__);

    MDB_val _key;
    MDB_val _data;

    _key.mv_size = key->size;
    _key.mv_data = key->data;
    _data.mv_size = data->size;
    _data.mv_data = data->data;

    uint32_t _flags = 0;

    if (mdb_txn_begin(db->_internal->env, NULL, 0, &db->_internal->txn) != 0) return EINVAL;
    mdb_put(db->_internal->txn, db->_internal->dbi, &_key, &_data, _flags);
    mdb_txn_commit(db->_internal->txn);

    return 0;
}

int _db_del(DB *db, DB_TXN *txnid, DBT *key, uint32_t flags)
{
    //FIXME
    printf("%s\n", __FUNCTION__);


    MDB_val _key;

    _key.mv_size = key->size;
    _key.mv_data = key->data;

    uint32_t _flags = 0;

    if (mdb_txn_begin(db->_internal->env, NULL, 0, &db->_internal->txn) != 0) return EINVAL;
    mdb_del(db->_internal->txn, db->_internal->dbi, &_key, NULL);
    mdb_txn_commit(db->_internal->txn);

    return 0;
}

int db_create(DB **database, DB_ENV *database_env, uint32_t flags)
{
    printf("%s\n", __FUNCTION__);
    if (database == NULL) return EINVAL;

    DB *db = calloc(1, sizeof(DB));
    *database = db;

    db->_internal = calloc(1, sizeof(struct _PRKL_DATA));
    mdb_env_create(&(db->_internal->env));
    mdb_env_set_mapsize(db->_internal->env, 10485760);

    db->open = _db_open;
    db->close = _db_close;
    db->err = _db_err;
    db->put = _db_put;
    db->get = _db_get;
    db->del = _db_del;

    return 0;
}
