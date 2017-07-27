set pages 999
col sname format a15 heading 'Tablespace' justify c
col ssize format 99,999.99 heading 'Mb|Total' justify c
col extents format 9,999   heading 'Free|Extents' justify c
col mbytes format 99,999.99 heading 'Largest|Free Extent' justify c 
col tbytes format 99,999.99 heading 'Mb|Available' justify c 
col ubytes format 99,999.99 heading 'Mb|Used' justify c 
col pct format 990 heading 'Percent|Free' justify c 
break on report
compute sum of ssize on report
compute sum of tbytes on report
compute sum of ubytes on report
--spool free_spc
select
 total.tablespace_name sname,
 total.bytes/1048576 ssize,
count(free.bytes) extents,
max(free.bytes)/1048576 mbytes,
sum (free.bytes)/1048576 tbytes,
(total.bytes - sum (free.bytes))/1048576 ubytes, 
round(sum(free.bytes)/total.bytes * 100) pct from sys.DBA_DATA_FILES total,
sys.dba_free_space free
where total.tablespace_name = free.tablespace_name
--and total.tablespace_name = 'DATA'
group by total.tablespace_name, total.bytes
/
