-- =========================================================
-- EQUIPMENT RESERVATION SYSTEM SETUP
-- Based on actual database structure in DBEARt.sql
-- =========================================================

-- NOTE: The EQUIPEMENTS table already has these columns:
--   QUANTITY_AVAILABLE, QUANTITY_RESERVED, QUANTITY_MAINTENANCE, QUANTITY_OUT_OF_ORDER
-- So we don't need to add them again.

-- NOTE: EQUIPMENT_RESERVATIONS table already exists but may need additional columns
-- Current structure: ID_RESERVATION, ID_ACTIVITY, ID_EQUIPMENT, QUANTITY_RESERVED, 
--                    RESERVATION_DATE, RETURN_DATE, STATUS

-- Step 1: Add missing columns to EQUIPMENT_RESERVATIONS if needed
-- (These columns may not exist in the current table)

-- Add RESERVED_BY column if it doesn't exist
BEGIN
    EXECUTE IMMEDIATE 'ALTER TABLE SUMMERCLUB.EQUIPMENT_RESERVATIONS ADD RESERVED_BY VARCHAR2(100 BYTE)';
EXCEPTION
    WHEN OTHERS THEN
        IF SQLCODE = -1430 THEN -- Column already exists
            NULL;
        ELSE
            RAISE;
        END IF;
END;
/

-- Add RESERVATION_TIME column if it doesn't exist
BEGIN
    EXECUTE IMMEDIATE 'ALTER TABLE SUMMERCLUB.EQUIPMENT_RESERVATIONS ADD RESERVATION_TIME TIMESTAMP(6)';
EXCEPTION
    WHEN OTHERS THEN
        IF SQLCODE = -1430 THEN -- Column already exists
            NULL;
        ELSE
            RAISE;
        END IF;
END;
/

-- Add NOTES column if it doesn't exist
BEGIN
    EXECUTE IMMEDIATE 'ALTER TABLE SUMMERCLUB.EQUIPMENT_RESERVATIONS ADD NOTES CLOB';
EXCEPTION
    WHEN OTHERS THEN
        IF SQLCODE = -1430 THEN -- Column already exists
            NULL;
        ELSE
            RAISE;
        END IF;
END;
/

-- Add CREATED_DATE column if it doesn't exist
BEGIN
    EXECUTE IMMEDIATE 'ALTER TABLE SUMMERCLUB.EQUIPMENT_RESERVATIONS ADD CREATED_DATE TIMESTAMP(6) DEFAULT CURRENT_TIMESTAMP';
EXCEPTION
    WHEN OTHERS THEN
        IF SQLCODE = -1430 THEN -- Column already exists
            NULL;
        ELSE
            RAISE;
        END IF;
END;
/

-- Add UPDATED_DATE column if it doesn't exist
BEGIN
    EXECUTE IMMEDIATE 'ALTER TABLE SUMMERCLUB.EQUIPMENT_RESERVATIONS ADD UPDATED_DATE TIMESTAMP(6) DEFAULT CURRENT_TIMESTAMP';
EXCEPTION
    WHEN OTHERS THEN
        IF SQLCODE = -1430 THEN -- Column already exists
            NULL;
        ELSE
            RAISE;
        END IF;
END;
/

-- Step 2: Ensure QUANTITY columns in EQUIPEMENTS are populated from old columns
-- (Only update if new columns are NULL or 0 and old columns have values)
UPDATE SUMMERCLUB.EQUIPEMENTS 
SET QUANTITY_AVAILABLE = NVL(QUANTITY_AVAILABLE, NVL(AVAILABLE, 0)),
    QUANTITY_RESERVED = NVL(QUANTITY_RESERVED, NVL(IN_USE, 0)),
    QUANTITY_MAINTENANCE = NVL(QUANTITY_MAINTENANCE, NVL(UNDER_MAINTENANCE, 0)),
    QUANTITY_OUT_OF_ORDER = NVL(QUANTITY_OUT_OF_ORDER, 0)
WHERE QUANTITY_AVAILABLE IS NULL 
   OR (QUANTITY_AVAILABLE = 0 AND AVAILABLE > 0);

-- Step 3: Create trigger for reservation ID if it doesn't exist
-- (SEQ_RESERVATIONS already exists, so we just need the trigger)
CREATE OR REPLACE TRIGGER SUMMERCLUB.TRG_RESERVATION_ID
    BEFORE INSERT ON SUMMERCLUB.EQUIPMENT_RESERVATIONS
    FOR EACH ROW
BEGIN
    IF :NEW.ID_RESERVATION IS NULL THEN
        :NEW.ID_RESERVATION := SUMMERCLUB.SEQ_RESERVATIONS.NEXTVAL;
    END IF;
END;
/

-- Step 4: Create indexes for faster lookups (if they don't exist)
BEGIN
    EXECUTE IMMEDIATE 'CREATE INDEX IDX_RESERVATION_ACTIVITY ON SUMMERCLUB.EQUIPMENT_RESERVATIONS(ID_ACTIVITY)';
EXCEPTION
    WHEN OTHERS THEN
        IF SQLCODE = -955 THEN -- Index already exists
            NULL;
        ELSE
            RAISE;
        END IF;
END;
/

BEGIN
    EXECUTE IMMEDIATE 'CREATE INDEX IDX_RESERVATION_EQUIPMENT ON SUMMERCLUB.EQUIPMENT_RESERVATIONS(ID_EQUIPMENT)';
EXCEPTION
    WHEN OTHERS THEN
        IF SQLCODE = -955 THEN -- Index already exists
            NULL;
        ELSE
            RAISE;
        END IF;
END;
/

BEGIN
    EXECUTE IMMEDIATE 'CREATE INDEX IDX_RESERVATION_DATE ON SUMMERCLUB.EQUIPMENT_RESERVATIONS(RESERVATION_DATE)';
EXCEPTION
    WHEN OTHERS THEN
        IF SQLCODE = -955 THEN -- Index already exists
            NULL;
        ELSE
            RAISE;
        END IF;
END;
/

COMMIT;

SELECT 'Equipment reservation system setup completed successfully!' AS message FROM dual;
SELECT 'Note: EQUIPEMENTS table already has QUANTITY_* columns' AS info FROM dual;
SELECT 'Note: EQUIPMENT_RESERVATIONS table structure updated with additional columns' AS info FROM dual;
