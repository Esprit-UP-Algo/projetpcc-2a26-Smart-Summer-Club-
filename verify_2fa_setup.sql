-- Verification and setup script for TOTP functionality
-- Run this script to ensure your database is properly configured for 2FA

-- Check if the EMPLOYEE_TOTP table exists
SELECT 'EMPLOYEE_TOTP table status:' as info, 
       CASE WHEN COUNT(*) > 0 THEN 'EXISTS' ELSE 'MISSING' END as status
FROM user_tables 
WHERE table_name = 'EMPLOYEE_TOTP';

-- If the table doesn't exist, create it
BEGIN
   -- Check if table exists
   DECLARE
      table_count NUMBER := 0;
   BEGIN
      SELECT COUNT(*)
      INTO table_count
      FROM user_tables
      WHERE table_name = 'EMPLOYEE_TOTP';
      
      -- Create table if it doesn't exist
      IF table_count = 0 THEN
         EXECUTE IMMEDIATE '
            CREATE TABLE employee_totp (
                employee_cin VARCHAR2(8) PRIMARY KEY,
                secret_key CLOB NOT NULL,
                is_enabled NUMBER(1) DEFAULT 0 CHECK (is_enabled IN (0, 1)),
                backup_codes CLOB,
                setup_date DATE DEFAULT SYSDATE,
                last_used DATE,
                CONSTRAINT fk_employee_totp_cin FOREIGN KEY (employee_cin) 
                    REFERENCES EMPLOYEES(CIN) ON DELETE CASCADE
            )';
         
         -- Add comments
         EXECUTE IMMEDIATE 'COMMENT ON TABLE employee_totp IS ''Stores Two-Factor Authentication settings for employees''';
         
         -- Create index
         EXECUTE IMMEDIATE 'CREATE INDEX idx_employee_totp_enabled ON employee_totp(is_enabled)';
         
         DBMS_OUTPUT.PUT_LINE('✅ EMPLOYEE_TOTP table created successfully');
      ELSE
         DBMS_OUTPUT.PUT_LINE('✅ EMPLOYEE_TOTP table already exists');
      END IF;
   END;
END;
/

-- Check if EMPLOYEES table has the two_factor_enabled column
DECLARE
   column_count NUMBER := 0;
BEGIN
   SELECT COUNT(*)
   INTO column_count
   FROM user_tab_columns
   WHERE table_name = 'EMPLOYEES' AND column_name = 'TWO_FACTOR_ENABLED';
   
   IF column_count = 0 THEN
      EXECUTE IMMEDIATE 'ALTER TABLE EMPLOYEES ADD two_factor_enabled NUMBER(1) DEFAULT 0 CHECK (two_factor_enabled IN (0, 1))';
      EXECUTE IMMEDIATE 'COMMENT ON COLUMN EMPLOYEES.two_factor_enabled IS ''Indicates if employee has 2FA enabled''';
      DBMS_OUTPUT.PUT_LINE('✅ Added two_factor_enabled column to EMPLOYEES table');
   ELSE
      DBMS_OUTPUT.PUT_LINE('✅ two_factor_enabled column already exists in EMPLOYEES table');
   END IF;
END;
/

-- Create or replace trigger to sync 2FA status
CREATE OR REPLACE TRIGGER trg_employee_totp_sync
    AFTER INSERT OR UPDATE OR DELETE ON employee_totp
    FOR EACH ROW
BEGIN
    -- Handle INSERT and UPDATE
    IF INSERTING OR UPDATING THEN
        UPDATE EMPLOYEES 
        SET two_factor_enabled = :NEW.is_enabled 
        WHERE CIN = :NEW.employee_cin;
    END IF;
    
    -- Handle DELETE
    IF DELETING THEN
        UPDATE EMPLOYEES 
        SET two_factor_enabled = 0 
        WHERE CIN = :OLD.employee_cin;
    END IF;
END;
/

-- Show current 2FA status for all employees
SELECT 
    e.CIN,
    e.FIRST_NAME || ' ' || e.LAST_NAME as EMPLOYEE_NAME,
    e.EMAIL,
    NVL(e.two_factor_enabled, 0) as TWO_FACTOR_ENABLED,
    CASE 
        WHEN et.employee_cin IS NOT NULL THEN 'CONFIGURED'
        ELSE 'NOT_CONFIGURED'
    END as TOTP_STATUS,
    et.setup_date,
    et.last_used
FROM EMPLOYEES e
LEFT JOIN employee_totp et ON e.CIN = et.employee_cin
ORDER BY e.FIRST_NAME, e.LAST_NAME;

-- Commit all changes
COMMIT;

-- Display success message
SELECT '🔐 Database is now ready for Two-Factor Authentication!' as message FROM dual;
SELECT '📱 Users can now set up 2FA in the application settings.' as instruction FROM dual;