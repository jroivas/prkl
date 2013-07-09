#!/bin/bash

mydir=$(dirname $0)
pushd $mydir
scriptdir=$(pwd -P)
popd

echo "== Building MDB library ==="

if [ ! -e "./mdb" ] ; then
	echo "Fetching..."
	$scriptdir/fetch_mdb.sh
fi

if [ -e "./mdb" ] ; then
	echo "Building..."
	pushd ./mdb/libraries/liblmdb/ && make
	popd
fi

if [ -e "./mdb/libraries/liblmdb" ] ; then
	echo "Making symbolic link for liblmdb"
	ln -sf ./mdb/libraries/liblmdb liblmdb
fi
if [ -e "./mdb/libraries/liblmdb/liblmdb.so" ] ; then
	echo "Making symbolic link for liblmdb.so"
	ln -sf ./mdb/libraries/liblmdb/liblmdb.so liblmdb.so
fi
