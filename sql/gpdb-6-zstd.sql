-- create table <name> (c1 int, c2 text)
--   with (appendonly=true, compresstype=zstd)
\! pg_filedump -z -M -k -T zstd test/ao.zstd.gp6

-- create table <name> (c1 int, c2 text)
--   with (appendonly=true, orientation=column, compresstype=zstd)
\! pg_filedump -z -M -k -O column -T zstd test/co.zstd.gp6
