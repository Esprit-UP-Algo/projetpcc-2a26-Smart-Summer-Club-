-- ============================================================================
-- EQUIPMENT RESERVATIONS SYSTEM - DATABASE MIGRATION SCRIPT
-- ============================================================================
-- Created for: Advanced_Arduino Project (Summer Club Equipment Management)
-- Purpose: Add equipment reservation tracking to the database
-- Database: Oracle SQL
-- NOTE: Table name EQUIPEMENTS has double E (critical for queries)
-- ============================================================================

-- ============================================================================
-- STEP 1: Create Sequence for Auto-Incrementing Reservation IDs
-- ============================================================================
CREATE SEQUENCE SEQ_RESERVATIONS
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO CYCLE
    CACHE 20
;

-- ============================================================================
-- STEP 2: Create Equipment Reservations Bridge Table
-- ============================================================================
-- This table tracks which equipment is reserved for which activities
-- It creates a many-to-many relationship between ACTIVITIES and EQUIPEMENTS
-- with date-based availability tracking to prevent overbooking
-- ============================================================================
CREATE TABLE EQUIPMENT_RESERVATIONS (
    -- Primary Key
    ID_RESERVATION      NUMBER(10)          NOT NULL,
    
    -- Foreign Keys
    ID_ACTIVITY         NUMBER(10)          NOT NULL,  -- References ACTIVITIES.ID_A
    ID_EQUIPMENT        NUMBER(10)          NOT NULL,  -- References EQUIPEMENTS.ID_EQ (Note: Double E in table name)
    
    -- Reservation Details
    QUANTITY_RESERVED   NUMBER(5)           DEFAULT 1 NOT NULL,
    RESERVATION_DATE    DATE                DEFAULT SYSDATE NOT NULL,
    RETURN_DATE         DATE,
    
    -- Status Tracking
    STATUS              VARCHAR2(20)        DEFAULT 'Reserved',  -- 'Reserved', 'Returned', 'Cancelled'
    
    -- Audit Columns
    CREATED_DATE        DATE                DEFAULT SYSDATE,
    CREATED_BY          VARCHAR2(50),
    LAST_MODIFIED_DATE  DATE                DEFAULT SYSDATE,
    LAST_MODIFIED_BY    VARCHAR2(50),
    
    -- Primary Key Constraint
    CONSTRAINT PK_EQUIPMENT_RESERVATIONS 
        PRIMARY KEY (ID_RESERVATION),
    
    -- Foreign Key to Activities Table
    CONSTRAINT FK_EQUIPMENT_RESERVATIONS_ACTIVITY
        FOREIGN KEY (ID_ACTIVITY)
        REFERENCES ACTIVITIES(ID_A)
        ON DELETE CASCADE,  -- Delete reservations when activity is deleted
    
    -- Foreign Key to Equipment Table (Note: EQUIPEMENTS with double E)
    CONSTRAINT FK_EQUIPMENT_RESERVATIONS_EQUIPMENT
        FOREIGN KEY (ID_EQUIPMENT)
        REFERENCES EQUIPEMENTS(ID_EQ)
        ON DELETE CASCADE,  -- Delete reservations when equipment is deleted
    
    -- Check Constraints
    CONSTRAINT CHK_QUANTITY_RESERVED
        CHECK (QUANTITY_RESERVED > 0),
    
    CONSTRAINT CHK_STATUS
        CHECK (STATUS IN ('Reserved', 'Returned', 'Cancelled', 'Partial Return')),
    
    CONSTRAINT CHK_DATES
        CHECK (RETURN_DATE IS NULL OR RETURN_DATE >= RESERVATION_DATE)
)
TABLESPACE USERS;

-- ============================================================================
-- STEP 3: Create Indexes for Performance
-- ============================================================================
-- Index on Activity for quick lookup of all reservations for an activity
CREATE INDEX IDX_EQUIPMENT_RESERVATIONS_ACTIVITY 
    ON EQUIPMENT_RESERVATIONS(ID_ACTIVITY);

-- Index on Equipment for availability queries
CREATE INDEX IDX_EQUIPMENT_RESERVATIONS_EQUIPMENT 
    ON EQUIPMENT_RESERVATIONS(ID_EQUIPMENT);

-- Index on Reservation Date for date-range queries
CREATE INDEX IDX_EQUIPMENT_RESERVATIONS_DATE 
    ON EQUIPMENT_RESERVATIONS(RESERVATION_DATE);

-- Composite index for availability checking (equipment + date + status)
CREATE INDEX IDX_EQUIPMENT_RESERVATIONS_AVAILABILITY 
    ON EQUIPMENT_RESERVATIONS(ID_EQUIPMENT, RESERVATION_DATE, STATUS);

-- ============================================================================
-- STEP 4: Add Missing Columns to EQUIPEMENTS Table (if they don't exist)
-- ============================================================================
-- NOTE: If EQUIPEMENTS table already has these columns, these statements 
-- will be skipped during migration. Run with error handling enabled.
-- ============================================================================

-- Add quantity tracking columns (if not present)
BEGIN
    EXECUTE IMMEDIATE 'ALTER TABLE EQUIPEMENTS ADD QUANTITY_AVAILABLE NUMBER(5) DEFAULT 0';
EXCEPTION
    WHEN OTHERS THEN
        IF SQLCODE = -1430 THEN
            DBMS_OUTPUT.PUT_LINE('Column QUANTITY_AVAILABLE already exists');
        ELSE
            RAISE;
        END IF;
END;
/

BEGIN
    EXECUTE IMMEDIATE 'ALTER TABLE EQUIPEMENTS ADD QUANTITY_RESERVED NUMBER(5) DEFAULT 0';
EXCEPTION
    WHEN OTHERS THEN
        IF SQLCODE = -1430 THEN
            DBMS_OUTPUT.PUT_LINE('Column QUANTITY_RESERVED already exists');
        ELSE
            RAISE;
        END IF;
END;
/

BEGIN
    EXECUTE IMMEDIATE 'ALTER TABLE EQUIPEMENTS ADD QUANTITY_MAINTENANCE NUMBER(5) DEFAULT 0';
EXCEPTION
    WHEN OTHERS THEN
        IF SQLCODE = -1430 THEN
            DBMS_OUTPUT.PUT_LINE('Column QUANTITY_MAINTENANCE already exists');
        ELSE
            RAISE;
        END IF;
END;
/

BEGIN
    EXECUTE IMMEDIATE 'ALTER TABLE EQUIPEMENTS ADD QUANTITY_OUT_OF_ORDER NUMBER(5) DEFAULT 0';
EXCEPTION
    WHEN OTHERS THEN
        IF SQLCODE = -1430 THEN
            DBMS_OUTPUT.PUT_LINE('Column QUANTITY_OUT_OF_ORDER already exists');
        ELSE
            RAISE;
        END IF;
END;
/

-- ============================================================================
-- STEP 5: Update Sum-Check Constraint on EQUIPEMENTS (if not present)
-- ============================================================================
-- This ensures data integrity: QUANTITY_AVAILABLE + QUANTITY_RESERVED + 
-- QUANTITY_MAINTENANCE + QUANTITY_OUT_OF_ORDER = TOTAL_QUANTITY
-- ============================================================================

BEGIN
    EXECUTE IMMEDIATE 'ALTER TABLE EQUIPEMENTS DROP CONSTRAINT CHK_QUANTITY_SUM';
EXCEPTION
    WHEN OTHERS THEN
        IF SQLCODE = -2443 THEN
            DBMS_OUTPUT.PUT_LINE('Constraint CHK_QUANTITY_SUM does not exist (will be created)');
        ELSE
            RAISE;
        END IF;
END;
/

ALTER TABLE EQUIPEMENTS 
ADD CONSTRAINT CHK_QUANTITY_SUM 
    CHECK (TOTAL_QUANTITY = 
           NVL(QUANTITY_AVAILABLE, 0) + 
           NVL(QUANTITY_RESERVED, 0) + 
           NVL(QUANTITY_MAINTENANCE, 0) + 
           NVL(QUANTITY_OUT_OF_ORDER, 0))
;

-- ============================================================================
-- STEP 6: Create View for Equipment Availability (Helpful for Reporting)
-- ============================================================================
-- This view shows equipment availability by date, accounting for existing reservations
-- ============================================================================

CREATE OR REPLACE VIEW V_EQUIPMENT_AVAILABILITY AS
SELECT 
    e.ID_EQ,
    e.EQUIP_CODE,
    e.NAME,
    e.CATEGORY,
    e.TOTAL_QUANTITY,
    NVL(e.QUANTITY_AVAILABLE, e.AVAILABLE) AS QUANTITY_AVAILABLE,
    NVL(e.QUANTITY_RESERVED, e.IN_USE) AS QUANTITY_RESERVED,
    NVL(e.QUANTITY_MAINTENANCE, e.UNDER_MAINTENANCE) AS QUANTITY_MAINTENANCE,
    NVL(e.QUANTITY_OUT_OF_ORDER, 0) AS QUANTITY_OUT_OF_ORDER,
    TRUNC(SYSDATE) AS CHECK_DATE,
    GREATEST(
        NVL(e.QUANTITY_AVAILABLE, e.AVAILABLE) - 
        NVL((
            SELECT SUM(er.QUANTITY_RESERVED) 
            FROM EQUIPMENT_RESERVATIONS er
            WHERE er.ID_EQUIPMENT = e.ID_EQ 
              AND er.RESERVATION_DATE = TRUNC(SYSDATE)
              AND er.STATUS IN ('Reserved', 'Partial Return')
        ), 0), 
        0
    ) AS REAL_TIME_AVAILABLE
FROM EQUIPEMENTS e
ORDER BY e.NAME;

-- ============================================================================
-- STEP 7: Create Trigger for Automatic Audit Trail (Optional)
-- ============================================================================
-- This trigger automatically updates LAST_MODIFIED_DATE and LAST_MODIFIED_BY
-- for any changes to the EQUIPMENT_RESERVATIONS table
-- ============================================================================

CREATE OR REPLACE TRIGGER TRG_EQUIPMENT_RESERVATIONS_AUDIT
BEFORE UPDATE ON EQUIPMENT_RESERVATIONS
FOR EACH ROW
BEGIN
    :NEW.LAST_MODIFIED_DATE := SYSDATE;
    -- Optional: Set :NEW.LAST_MODIFIED_BY to current user if needed
END TRG_EQUIPMENT_RESERVATIONS_AUDIT;
/

-- ============================================================================
-- STEP 8: Sample Data Initialization (Optional - Comment out if not needed)
-- ============================================================================
-- Uncomment and modify as needed to test equipment reservation system
-- ============================================================================

/*
-- Example: Reserve 5 units of "Projector" for Activity ID 1
INSERT INTO EQUIPMENT_RESERVATIONS 
(ID_RESERVATION, ID_ACTIVITY, ID_EQUIPMENT, QUANTITY_RESERVED, RESERVATION_DATE, STATUS)
VALUES 
(SEQ_RESERVATIONS.NEXTVAL, 1, 10, 5, SYSDATE, 'Reserved');

COMMIT;
*/

-- ============================================================================
-- FINAL VERIFICATION QUERIES
-- ============================================================================
-- Run these after migration to verify everything is set up correctly
-- ============================================================================

-- Check table structure
DESC EQUIPMENT_RESERVATIONS;

-- Check sequence
SELECT sequence_name, increment_by, last_number FROM user_sequences WHERE sequence_name = 'SEQ_RESERVATIONS';

-- Check indexes
SELECT index_name, table_name FROM user_indexes WHERE table_name = 'EQUIPMENT_RESERVATIONS';

-- Check constraints
SELECT constraint_name, constraint_type, search_condition 
FROM user_constraints 
WHERE table_name = 'EQUIPMENT_RESERVATIONS' 
ORDER BY constraint_type;

-- Check Foreign Keys
SELECT constraint_name, table_name, r_table_name 
FROM user_constraints 
WHERE constraint_type = 'R' AND table_name = 'EQUIPMENT_RESERVATIONS';

-- Count Equipment with new quantity columns
SELECT COUNT(*) as equipment_count FROM EQUIPEMENTS;

-- Sample availability check (adjust date as needed)
SELECT * FROM V_EQUIPMENT_AVAILABILITY WHERE REAL_TIME_AVAILABLE > 0;

-- ============================================================================
-- END OF MIGRATION SCRIPT
-- ============================================================================
-- If you encounter any errors:
-- 1. Check that EQUIPEMENTS table exists and has ID_EQ column (note: double E in table name)
-- 2. Check that ACTIVITIES table exists and has ID_A column
-- 3. For "column already exists" errors, this is OK - table already has these columns
-- 4. For "sequence already exists" errors, drop it first: DROP SEQUENCE SEQ_RESERVATIONS;
-- 5. Contact DevOps team if foreign key errors occur (parent records may be missing)
-- ============================================================================
COMMIT;
