pg\_filedump for the Greenplum Database
=======================================

This is the enhanced version of `pg_filedump` with the support for Greenplum
Database.

Build
-----

This package only supports building in pgxs mode, which means an installed copy
of gpdb binaries is needed, you can use an official released one, which is
available on http://network.pivotal.io, or a customized one build from source
code manually.

You can typically build like this:

    # make sure we can find the gpdb package
    source /path/to/greenplum_path.sh

    # download needed gpdb source files according to the gpdb version
    make -f Makefile.gpdb download

    # build the pg_filedump
    make -f Makefile.gpdb

The build result is a binary file named `pg_filedump`, you could copy it to
your target machines and run it without the gpdb binaries.

Gpdb versions
-------------

This package supports building with gpdb 5, 6, 7 installations.

Compiling with gpdb 4 is not supported, but you could compile with gpdb 6 and
use the resulting `pg_filedump` binary on gpdb 4 data files, however note that
the `pg_control` file format is specific to each gpdb version, so a
`pg_filedump` compiled with gpdb 6 cannot parse `pg_control` of gpdb 4.3, 5 or
7, etc..

Configuration
-------------

There are several configurable options:

- `ENABLE_ZLIB`: To use `pg_filedump` on zlib compressed data files, we need to
  enable the zlib support.  It is automatically enabled if the zlib headers and
  libraries are detected with `pkg-config`, but you could force it to be
  enabled by `make -f Makefile.gpdb ENABLE_ZLIB=y`, make sure the zlib headers
  and libraries are available, you may also need to set `CFLAGS` and `LDFLAGS`
  accordingly.  It is also possible to force building without zlib by setting
  this variable to `n`.

- `ENABLE_ZSTD`: A similar setting for the zstd compression method.  The zstd
  compression is supported since gpdb 6.

- `ENABLE_QUICKLZ`: A similar setting for the quicklz compression method.
  Unlike zlib or zstd, the quicklz package is not available on most of the
  linux distributions, so usually it is not possible to enable quicklz support
  in `pg_filedump`.

- `DOWNLOADER`: The program to download the gpdb source files.  It is `curl` by
  default, but you could specify a different one like this: `make -f
  Makefile.gpdb DOWNLOADER='wget -O'`.  A downloader must accepts two
  arguments, the first is the local path, including the filename, to save the
  file, the second is the url.  Note that github does not allow ranged
  downloading, so do not specify the options to resume an incomplete download.

 vi:sw=2 et autoindent:
