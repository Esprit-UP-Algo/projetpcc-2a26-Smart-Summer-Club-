-- Create table for storing TOTP (Two-Factor Authentication) secrets
-- This table stores the 2FA configuration for each employee

CREATE TABLE employee_totp (
    employee_cin VARCHAR2(8) PRIMARY KEY,
    secret_key CLOB NOT NULL,
    is_enabled NUMBER(1) DEFAULT 0 CHECK (is_enabled IN (0, 1)),
    backup_codes CLOB, -- JSON array of one-time backup codes
    setup_date DATE DEFAULT SYSDATE,
    last_used DATE,
    CONSTRAINT fk_employee_totp_cin FOREIGN KEY (employee_cin) REFERENCES EMPLOYEES(CIN) ON DELETE CASCADE
);

-- Add comments to describe the table and columns
COMMENT ON TABLE employee_totp IS 'Stores Two-Factor Authentication settings for employees';
COMMENT ON COLUMN employee_totp.employee_cin IS 'Employee CIN (Foreign Key from EMPLOYEES table)';
COMMENT ON COLUMN employee_totp.secret_key IS 'Base32-encoded secret key for TOTP generation';
COMMENT ON COLUMN employee_totp.is_enabled IS 'Flag indicating if 2FA is enabled (1) or disabled (0)';
COMMENT ON COLUMN employee_totp.backup_codes IS 'JSON array of backup codes for account recovery';
COMMENT ON COLUMN employee_totp.setup_date IS 'Date when 2FA was first set up';
COMMENT ON COLUMN employee_totp.last_used IS 'Date when 2FA was last used for authentication';

-- Create index for faster lookups
CREATE INDEX idx_employee_totp_enabled ON employee_totp(is_enabled);

-- Optional: Add a column to track 2FA preference in the main EMPLOYEES table
-- (This can be used for quick checks without joining tables)
ALTER TABLE EMPLOYEES ADD two_factor_enabled NUMBER(1) DEFAULT 0 CHECK (two_factor_enabled IN (0, 1));
COMMENT ON COLUMN EMPLOYEES.two_factor_enabled IS 'Indicates if employee has 2FA enabled (cached value)';

-- Create a trigger to keep the EMPLOYEES.two_factor_enabled in sync
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

COMMIT;