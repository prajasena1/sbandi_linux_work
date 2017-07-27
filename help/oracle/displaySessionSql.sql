set lines 200
column username format a15
column osuser format a10
column sid format a6
column serial# format 99999
column program format a25
column machine format a25
column "Command" format a15
column pid format 99999
column "LOGIN" format a18
column "PROCESS" heading "Parent|UNIX|PID"
column "IDLE_FOR" format a12
break on "UNIX PID" skip 1
set wrap off
 SELECT  SUBSTR(NVL(DECODE(sess.username, null, SUBSTR(proc.program,INSTR(proc.program, '(',1)), sess.username), '**Kill?**'),
 1, 14) "USERNAME",
         NVL(TO_CHAR(sess.sid), '*Kill?*') "SID", sess.serial#,
         proc.spid "UNIX PID",
         sess.process "PROCESS",
         proc.pid,
         sess.osuser,
    sess.terminal,
         INITCAP(comm.name) "Command",
         sess.program,
         sess.status,
         TO_CHAR(sess.logon_time, 'DD MON [HH24:MI:SS]') "LOGIN",
         TRUNC(last_call_et/(60*60*24)) || ':' ||
                 LPAD(MOD(TRUNC(last_call_et/(60*60)), 24), 2, 0) || ':' ||
                 LPAD(MOD(TRUNC(last_call_et/60), 60), 2, 0) || ':' ||
                 LPAD(MOD(last_call_et, 60), 2, 0) "IDLE_FOR",
         sess.machine,
    c.sql_text "SQL"
 FROM    v$session sess, v$process proc, audit_actions comm, v$sql c
 WHERE   sess.paddr(+) = proc.addr
 AND     NVL(sess.command, 0) = comm.action
 AND        sess.sql_address=c.address
ORDER   BY sess.logon_time, sess.username

