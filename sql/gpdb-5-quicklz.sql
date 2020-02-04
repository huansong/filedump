-- create table <name> (c1 int, c2 text)
--   with (appendonly=true, compresstype=quicklz)
\! pg_filedump -z -M -k -T quicklz -L 1 test/ao.quicklz.gp5

-- create table <name> (c1 int, c2 text)
--   with (appendonly=true, orientation=column, compresstype=quicklz)
\! pg_filedump -z -M -k -O column -T quicklz -L 1 test/co.quicklz.gp5
