-- create table <name> (c1 int, c2 text)
--   with (appendonly=true, compresstype=zlib)
\! pg_filedump -z -M -k -T zlib test/ao.zlib.gp4

-- create table <name> (c1 int, c2 text)
--   with (appendonly=true, orientation=column, compresstype=zlib)
\! pg_filedump -z -M -k -O column -T zlib test/co.zlib.gp4
