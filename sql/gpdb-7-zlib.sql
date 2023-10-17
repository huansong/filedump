-- 1. Tests for pre-generated relation files

-- create table <name> (c1 int, c2 text)
--   with (appendonly=true, compresstype=zlib)
\! pg_filedump -z -M -k -T zlib test/ao.zlib.gp7

-- create table <name> (c1 int, c2 text)
--   with (appendonly=true, orientation=column, compresstype=zlib)
\! pg_filedump -z -M -k -O column -T zlib test/co.zlib.gp7

-- 2. Tests for new relations files generated by the running GPDB server

create table ao_zlib(c1 int, c2 text) with (appendonly=true, compresstype=zlib) distributed replicated;
create table co_zlib(c1 int, c2 text) with (appendonly=true, orientation=column, compresstype=zlib) distributed replicated;
insert into ao_zlib select i,'abc' from generate_series(1,10)i;
insert into co_zlib select i,'abc' from generate_series(1,10)i;
\set relname ao_zlib
\set ext '.1'
\setenv opt '-z -M -k -T zlib'
\ir run_test.sql
\set relname co_zlib
\set ext '.1'
\setenv opt '-z -M -k -O column -T zlib'
\ir run_test.sql

