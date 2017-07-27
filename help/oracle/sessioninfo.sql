--
-- Author:              Ahbaid Gaffoor

-- Date:                Wednesday 18th December 2002


-- File:                context.sql

--
-- Purpose:             This script uses the SYS_CONTEXT function to retrieve user connection details
--
-- Usage:               @context (at SQL prompt)

--
--


set serveroutput on size 400000
set feedback off
set lines 120

declare


   cursor c_ctx is select
          SYS_CONTEXT('USERENV','TERMINAL') terminal,
          SYS_CONTEXT('USERENV','LANGUAGE') language,
          SYS_CONTEXT('USERENV','SESSIONID') sessionid,
          SYS_CONTEXT('USERENV','INSTANCE') instance,
          SYS_CONTEXT('USERENV','ENTRYID') entryid,
          SYS_CONTEXT('USERENV','ISDBA') isdba,
          SYS_CONTEXT('USERENV','NLS_TERRITORY') nls_territory,

          SYS_CONTEXT('USERENV','NLS_CURRENCY') nls_currency,
          SYS_CONTEXT('USERENV','NLS_CALENDAR') nls_calendar,
          SYS_CONTEXT('USERENV','NLS_DATE_FORMAT') nls_date_format,
          SYS_CONTEXT('USERENV','NLS_DATE_LANGUAGE') nls_date_language,
          SYS_CONTEXT('USERENV','NLS_SORT') nls_sort,
          SYS_CONTEXT('USERENV','CURRENT_USER') current_user,
          SYS_CONTEXT('USERENV','CURRENT_USERID') current_userid,
          SYS_CONTEXT('USERENV','SESSION_USER') session_user,
          SYS_CONTEXT('USERENV','SESSION_USERID') session_userid,
          SYS_CONTEXT('USERENV','PROXY_USER') proxy_user,

          SYS_CONTEXT('USERENV','PROXY_USERID') proxy_userid,
          SYS_CONTEXT('USERENV','DB_DOMAIN') db_domain,
          SYS_CONTEXT('USERENV','DB_NAME') db_name,
          SYS_CONTEXT('USERENV','HOST') host,
          SYS_CONTEXT('USERENV','OS_USER') os_user,
          SYS_CONTEXT('USERENV','EXTERNAL_NAME') external_name,
          SYS_CONTEXT('USERENV','IP_ADDRESS') ip_address,
          SYS_CONTEXT('USERENV','NETWORK_PROTOCOL') network_protocol,
          SYS_CONTEXT('USERENV','BG_JOB_ID') bg_job_id,
          SYS_CONTEXT('USERENV','FG_JOB_ID') fg_job_id,
          SYS_CONTEXT('USERENV','AUTHENTICATION_TYPE')

authentication_type,
          SYS_CONTEXT('USERENV','AUTHENTICATION_DATA')
authentication_data,
          SYS_CONTEXT('USERENV','CURRENT_SQL') current_sql,
          SYS_CONTEXT('USERENV','CLIENT_IDENTIFIER') client_identifier,
          SYS_CONTEXT('USERENV','GLOBAL_CONTEXT_MEMORY')
global_context_memory
   from dual;

   ctx c_ctx%ROWTYPE;

   --

   -- Utility Functions
   --

   function pad (s varchar2, padsize number := 25, padchar varchar2 := '
') return varchar2 is
   begin
     return rpad(s,padsize,padchar);
   end pad;

   procedure print(s varchar2) is
   begin
      dbms_output.put_line(s);
   end print;


   procedure newln is
   begin
      print(chr(10));
   end newln;


begin

   open c_ctx;
   fetch c_ctx into ctx;
   close c_ctx;

   newln;


   print('Connection Context');
   print('==================');
   newln;

   print('User Details');
   print('------------');
   print('Session ID: '||ctx.sessionid);
   print('Session User ID: '||ctx.Session_userid||' / '||ctx.session_user);
   print('Current User ID: '||ctx.current_userid||' / '||ctx.current_user);
   print('Is DBA: '||ctx.isdba);

   newln;


   print('Machine/Network Details');
   print('-----------------------');
   print('Terminal: '||ctx.terminal);
   print('Host: '||ctx.host);
   print('OS User: '||ctx.os_user);
   print('IP Address: '||ctx.ip_address);
   print('Network Protocol: '||ctx.network_protocol);
   print('Authentication Type: '||ctx.authentication_type);

   newln;

   print('NLS Settings');
   print('------------');
   print('NLS Territory: '||ctx.nls_territory);
   print('NLS Currency: '||ctx.nls_currency);

   print('NLS Date Format: '||ltrim(ctx.nls_date_format));
   print('NLS Date Language: '||ctx.nls_date_language);
   print('NLS Sort: '||ctx.nls_sort);

   newln;

   print('Database');
   print('--------');
   print('DB Name: '||ctx.db_name);
   print('DB Domain: '||ctx.db_domain);
   print('Language: '||ctx.language);


   newln;

end;
/


set feedback on
