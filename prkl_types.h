#ifndef PRKL_TYPES_H
#define PRKL_TYPES_H

#include <stdint.h>

#define DB_XA_CREATE 2

struct _PRKL_DATA;
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

typedef struct {
    void *data;
    uint32_t size;
    uint32_t ulen;
    uint32_t dlen;
    uint32_t doffset;
    uint32_t flags;
} DBT;

#define DB_CREATE 1

struct _DB {
    int (*open)(DB *db, DB_TXN *txnid, const char *file, const char *database, DBTYPE type, uint32_t flags, int mode);
    int (*close)(DB *db, uint32_t flags);
    void (*err)(DB *db, int error, const char *fmt, ...);

    int (*get)(DB *db, DB_TXN *txnid, DBT *key, DBT *data, uint32_t flags);
    int (*put)(DB *db, DB_TXN *txnid, DBT *key, DBT *data, uint32_t flags);
    int (*del)(DB *db, DB_TXN *txnid, DBT *key, uint32_t flags);

    struct _PRKL_DATA *_internal;
};

struct _DB_ENV {
    int (*txn_begin)(DB_ENV *env, DB_TXN *parent, DB_TXN **tid, uint32_t flags);

    struct _PRKL_DATA *_internal;
};

struct _DB_TXN {
    struct _PRKL_DATA *_internal;
};

#endif
