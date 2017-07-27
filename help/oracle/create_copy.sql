-- STEPS:
--
-- Disable constraints
-- Disable triggers
-- Copy
-- Enable constraints
-- Enable triggers

SET SERVEROUTPUT ON
PROMPT Enter the table's name you want to copy
DEFINE tname = &table_name
PROMPT
PROMPT Enter the FROM database id
DEFINE dbname = &database_id
PROMPT
PROMPT Enter the FROM user id
DEFINE uname = &user_id

SPOOL  TAB_COPY.SQL
DECLARE
   v_table_name     VARCHAR2( 30) := '&&tname';
   v_user_name      VARCHAR2( 30) := '&&uname';
   v_db_name        VARCHAR2( 30) := '&&dbname';

BEGIN
   dbms_output.enable( 100000);
   v_table_name := UPPER( v_table_name);
   v_user_name  := UPPER( v_user_name);
   v_db_name    := UPPER( v_db_name);

-- Disable the constraints from other tables
   FOR c1 IN (SELECT con.constraint_name,
                     con.status
              FROM   user_constraints con
              WHERE  con.table_name = v_table_name
              AND    con.constraint_type = 'R'
             )
   LOOP
      IF c1.status = 'ENABLED' THEN
         dbms_output.put_line
         ( 'PROMPT Disable constraint '|| c1.constraint_name||
           ' on table '|| v_table_name
         );
         dbms_output.put_line
         ( 'ALTER TABLE '|| v_table_name|| ' DISABLE CONSTRAINT '||
            c1.constraint_name
         );
         dbms_output.put_line( '/');
      ELSE
         dbms_output.put_line
         ( 'PROMPT Constraint '|| c1.constraint_name||
           ' on table '|| v_table_name||
           ' is already DISABLED.'
         );
         dbms_output.put_line
         ( 'REM ALTER TABLE '|| v_table_name|| ' DISABLE CONSTRAINT '||
            c1.constraint_name
         );

      END IF;
   END LOOP;

-- Disable the constraints to the table on other tables
   FOR c1 IN (SELECT con.table_name,
                     con.constraint_name,
                     con.status
              FROM   user_constraints con
              WHERE  con.r_constraint_name IN
                     (SELECT con1.constraint_name
                      FROM   user_constraints con1
                      WHERE  con1.table_name = v_table_name
                      AND    con1.constraint_type IN ('P', 'U'))
              AND    con.constraint_type = 'R'
             )
   LOOP
      IF c1.status = 'ENABLED' THEN
         dbms_output.put_line
         ( 'PROMPT Disable constraint '|| c1.constraint_name||
           ' on table '|| c1.table_name
         );
         dbms_output.put_line
         ( 'ALTER TABLE '|| c1.table_name|| ' DISABLE CONSTRAINT '||
            c1.constraint_name
         );
         dbms_output.put_line( '/');
      ELSE
         dbms_output.put_line
         ( 'PROMPT Constraint '|| c1.constraint_name||
           ' on table '|| c1.table_name||
           ' is already DISABLED.'
         );
         dbms_output.put_line
         ( 'REM ALTER TABLE '|| c1.table_name|| ' DISABLE CONSTRAINT '||
            c1.constraint_name
         );

      END IF;
   END LOOP;

-- Disable the triggers on the table
   FOR c1 IN (SELECT trg.trigger_name,
                     trg.status
              FROM   user_triggers trg
              WHERE  trg.table_name = v_table_name
             )
   LOOP
      IF c1.status = 'ENABLED' THEN
         dbms_output.put_line
         ( 'PROMPT Disable trigger '|| c1.trigger_name||
           ' on table '|| v_table_name
         );
         dbms_output.put_line
         ( 'ALTER TRIGGER '|| c1.trigger_name|| ' DISABLE'
         );
         dbms_output.put_line( '/');
      ELSE
         dbms_output.put_line( 'PROMPT Trigger '|| c1.trigger_name||
                               ' on table '|| v_table_name||
                               ' is already DISABLED.');
      END IF;
   END LOOP;

   dbms_output.put_line( 'PROMPT Truncate table '|| v_table_name);
   dbms_output.put_line( 'TRUNCATE TABLE '|| v_table_name);
   dbms_output.put_line( '/');

--   dbms_output.put_line( 'PROMPT Delete the table');
--   dbms_output.put_line( 'DELETE '|| v_table_name);
--   dbms_output.put_line( '/');

   dbms_output.put_line( 'PROMPT Copy the table from '|| v_db_name);
   dbms_output.put_line( 'COPY FROM '|| v_user_name|| '@'|| v_db_name|| ' -');
   dbms_output.put_line( 'INSERT '|| v_table_name ||' USING -');
   dbms_output.put_line( 'SELECT * FROM '|| v_table_name);

--   dbms_output.put_line( 'SELECT '|| v_table_name);
--   FOR c1 IN (SELECT utcol.column_name
--              FROM   user_tab_columns utcol
--              WHERE  utcoltable_name = v_table_name)
--   LOOP
--      dbms_output.put_line( utcol.column_name|| ', -');
--   END LOOP
--   dbms_output.put_line( 'FROM '|| v_table_name);

--
-- Enable the constraints from other tables
   FOR c1 IN (SELECT con.constraint_name,
                     con.status,
                     con2.table_name
              FROM   all_constraints con,
                     all_constraints con2
              WHERE  con.table_name = v_table_name
              AND    con.constraint_type = 'R'
              AND    con.r_constraint_name = con2.constraint_name
             )
   LOOP
      dbms_output.put_line
      ( 'PROMPT Enable constraint '|| c1.constraint_name||
        ' to table '|| c1.table_name
      );
      dbms_output.put_line
      ( 'PROMPT on table '|| v_table_name
      );

      dbms_output.put_line
      ( 'ALTER TABLE '|| v_table_name|| ' ENABLE CONSTRAINT '||
         c1.constraint_name
      );
      dbms_output.put_line( '/');
   END LOOP;

-- Enable the constraints to the table on other tables
   FOR c1 IN (SELECT con.table_name,
                     con.constraint_name,
                     con.status
              FROM   user_constraints con
              WHERE  con.r_constraint_name IN
                     (SELECT con1.constraint_name
                      FROM   user_constraints con1
                      WHERE  con1.table_name = v_table_name
                      AND    con1.constraint_type IN ('P', 'U'))
              AND    con.constraint_type = 'R'
             )
   LOOP
      dbms_output.put_line
      ( 'PROMPT Enable constraint '|| c1.constraint_name||
        ' on table '|| c1.table_name
      );

      dbms_output.put_line
      ( 'ALTER TABLE '|| c1.table_name|| ' ENABLE CONSTRAINT '||
         c1.constraint_name
      );
      dbms_output.put_line( '/');
   END LOOP;

-- Enable the triggers on the table
   FOR c1 IN (SELECT trg.trigger_name,
                     trg.status
              FROM   user_triggers trg
              WHERE  trg.table_name = v_table_name
             )
   LOOP
      dbms_output.put_line
      ( 'PROMPT Enable trigger '|| c1.trigger_name||
        ' on table '|| v_table_name
      );
      dbms_output.put_line
      ( 'ALTER TRIGGER '|| c1.trigger_name|| ' ENABLE'
      );
      dbms_output.put_line( '/');
   END LOOP;

END;
/
SPOOL OFF
