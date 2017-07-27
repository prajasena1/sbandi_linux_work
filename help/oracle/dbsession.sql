set linesize 132;77
column started_at      format A21;
select substr(instance_name,01,10) instance
      ,substr(host_name,01,20) hostname
      ,version
      ,substr(to_char(startup_time,'DD-MON-YYYY HH24:MI'),01,17)
startup_time
      ,substr(to_char(sysdate,'DD-MON-YYYY HH24:MI'),01,17) runtime from
v$instance ; 
column sid format 9999 heading 'Sid'; 
column serial# format
9999999 heading 'Serial#';
column  user#  format 99999   heading 'User#';
column  Terminal  format A15  heading 'Terminal'
column  Program   format A20  heading 'Program'
prompt ....................................
prompt .....Order by User..................
prompt ....................................
break on username skip 1
column username format A14 wrap;
column sid format 9999 heading 'Sid';
column serial# format 9999999 heading 'Serial#';
column  user#  format 99999   heading 'User#';
column  osuser format A12     heading 'OS User' print;
column  Terminal  format A10  heading 'Terminal'
column  Program   format A25  heading 'Program'
column  job       format A07  wrap 
select substr(nvl(v.username,'ORACLE'),01,14) username
      ,v.sid
      ,v.serial#
      ,substr(v.osuser,01,12) osuser
      ,p.spid
      ,v.status
      ,v.terminal
      ,v.program
      ,substr(to_char(v.logon_time,'DDMONYY HH24:MM'),01,13) logon_time
      ,upper(decode(nvl(v.command, 0),
                0,      '--',
                1,      'Create Table',
                2,      'Insert ...',
                3,      'Select ...',
                4,      'Create Cluster',
                5,      'Alter Cluster',
                6,      'Update ...',
                7,      'Delete ...',
                8,      'Drop ...',
                9,      'Create Index',
                10,     'Drop Index',
                11,     'Alter Index',
                12,     'Drop Table',
                13,     '--',
                14,     '--',
                15,     'Alter Table',
                16,     '--',
                17,     'Grant',
                18,     'Revoke',
                19,     'Create Synonym',
                20,     'Drop Synonym',
                21,     'Create View',
                22,     'Drop View',
                23,     '--',
                24,     '--',
                25,     '--',
                26,     'Lock Table',
                27,     'No Operation',
                28,     'Rename',
                29,     'Comment',
                30,     'Audit',
                31,     'NoAudit',
                32,     'Create Ext DB',
                33,     'Drop Ext. DB',
                34,     'Create Database',
                35,     'Alter Database',
                36,     'Create RBS',
                37,     'Alter RBS',
                38,     'Drop RBS',
                39,     'Create Tablespace',
                40,     'Alter Tablespace',
                41,     'Drop tablespace',
                42,     'Alter Session',
                43,     'Alter User',
                44,     'Commit',
                45,     'Rollback',
                46,     'Savepoint')) job
FROM  
      v$session v
     ,v$process p
WHERE p.addr = v.paddr
ORDER BY 1,4,6
/
