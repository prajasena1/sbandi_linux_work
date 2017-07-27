rem -----------------------------------------------------------------------
rem Filename:   ver.sql
rem Purpose:    Show database version with options intalled
rem             (handy for your HELP/ABOUT menu)
rem Date:       12-Nov-1999
rem Author:     Frank Naude, Oracle FAQ
rem -----------------------------------------------------------------------

set head off feed off pages 0 serveroutput on

col banner format a72 wrap

select banner
from   sys.v_$version;

set head on feed on

