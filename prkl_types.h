#ifndef PRKL_TYPES_H
#define PRKL_TYPES_H

#include <stdint.h>

#define DB_XA_CREATE 2

struct _PRKL_DATA;
struct _PRKL_DATA_ENV;
struct _PRKL_DATA_TXN;
struct _DB;
struct _DB_TXN;

typedef struct _DB DB;
typedef struct _DB_ENV DB_ENV;
typedef struct _DB_TXN DB_TXN;

typedef enum {
    DB_BTREE = 1,
    DB_HASH,
    DB_RECNO,
    DB_QUEUE,
    DB_UNKNOWN
} DBTYPE;

struct _DB {
    int (*open)(DB *db, DB_TXN *txnid, const char *file, const char *database, DBTYPE type, uint32_t flags, int mode);

    struct _PRKL_DATA *_internal;
};

struct _DB_ENV {
    int (*txn_begin)(DB_ENV *env, DB_TXN *parent, DB_TXN **tid, u_int32_t flags);

    struct _PRKL_DATA_ENV *_internal;
};

struct _DB_TXN {
};

#endif
