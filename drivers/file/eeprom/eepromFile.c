#include "eepromFile.h"

// Implementation of FAT Management for Eeprom with FATFS

#include "../../../common/eeprom/eeprom.h"
#include "../../../common/error/error.h"

#include "../../../common/io/outputStream.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../external/fatfs/ff.h"
#include "../../../external/fatfs/diskio.h"

static Eeprom* eeprom_;

/**
 * Returns a DWORD value with all information from the Clock.
 * @return 
 * - bit31:25  Year origin from the 1980 (0..127)
 * - bit24:21  Month (1..12)
 * - bit20:16  Day of the month(1..31)
 * - bit15:11  Hour (0..23)
 * - bit10:5   Minute (0..59)
 * - bit4:0    Second / 2 (0..29)
 */
DWORD get_fattime (void) {
    // TODO : Implementation. Convert from Clock structure to do.
    return 0;
}

/**
 * @private 
 * Get the status of the drive.
 * @param physicalDriveNumber Physical drive number to identify the drive
 * @return 
 * - STA_NOINIT Indicates that the device is not initialized. This flag is set on system reset, 
 * media removal or failure of disk_initialize function. It is cleared on disk_initialize function succeeded. Media change that occurs asynchronously must be captured and reflect it to the status flags, or auto-mount feature will not work correctly. If the system does not support media change detect feature, application program needs to force de-initialize the file system object with f_mount function after the media change.
 * - STA_NODISK Indicates that no medium in the drive. This is always cleared on fixed disk drive. Note that FatFs does not refer this flag.
 * - STA_PROTECT Indicates that the medium is write protected. This is always cleared on the drives without write protect feature. Not valid if no medium in the drive.
 */
DSTATUS disk_status (BYTE physicalDriveNumber) {
    DSTATUS result;

    if (physicalDriveNumber == EEPROM_DRIVE_NUMBER) {
        result = 0; // TODO ATA_disk_status();

        return result;
    }   
    return STA_NOINIT;
}

/**
* @private
* Initialize a drive.
* @param physicalDriveNumber Physical drive number to identify the drive
* @return 
* - STA_NOINIT Indicates that the device is not initialized. This flag is set on system reset, 
* media removal or failure of disk_initialize function. It is cleared on disk_initialize function succeeded. Media change that occurs asynchronously must be captured and reflect it to the status flags, or auto-mount feature will not work correctly. If the system does not support media change detect feature, application program needs to force de-initialize the file system object with f_mount function after the media change.
* - STA_NODISK Indicates that no medium in the drive. This is always cleared on fixed disk drive. Note that FatFs does not refer this flag.
* - STA_PROTECT Indicates that the medium is write protected. This is always cleared on the drives without write protect feature. Not valid if no medium in the drive.
*/
DSTATUS disk_initialize (BYTE physicalDriveNumber) {
    DSTATUS result;

    if (physicalDriveNumber == EEPROM_DRIVE_NUMBER) {
        result = 0; // ATA_disk_initialize();

        return result;
    }   
    return STA_NOINIT;
}


/**
 * @private
 * Read Sector(s).
 * @param physicalDriveNumber Physical drive number to identify the drive
 * @param buffer Data buffer to store read data
 * @param sector Sector address in LBA
 * @param count Number of sectors to read
 * @return 
 * - RES_OK (0) The function succeeded.
 * - RES_ERROR An error occured.
 * - RES_PARERR The command code or parameter is invalid.
 * - RES_NOTRDY The device has not been initialized.
 */ 
DRESULT disk_read (BYTE physicalDriveNumber, BYTE *buffer, DWORD sector, UINT count) {
    appendString(getErrorOutputStreamLogger(), "disk_read\r\n");
    if (physicalDriveNumber == EEPROM_DRIVE_NUMBER) {
        long base_index = sector * EEPROM_SECTOR_SIZE;
        long i;
        long bytesToRead = count * EEPROM_SECTOR_SIZE;
        for (i = 0; i < bytesToRead; i++) {
            // TODO : Improve by using call to eepromWriteBlock instead of using WriteRead !
            char value = eeprom_->eepromReadChar(eeprom_, base_index + i);
            *buffer = value;
            buffer++;
        }
        return RES_OK;
    }

    return RES_PARERR;
}

/**
 * @private
 * Write Sector(s).
 * @param physicalDriveNumber Physical drive number to identify the drive
 * @param buffer Data to be written
 * @param sector Sector address in LBA
 * @param count Number of sectors to write
 * @return 
 * - RES_OK (0) The function succeeded.
 * - RES_ERROR An error occured.
 * - RES_WRPRT The medium is write protected.
 * - RES_PARERR The command code or parameter is invalid.
 * - RES_NOTRDY The device has not been initialized.
 */
DRESULT disk_write (BYTE physicalDriveNumber, const BYTE *buffer, DWORD sector, UINT count) {
    if (physicalDriveNumber == EEPROM_DRIVE_NUMBER) {
        long base_index = sector * EEPROM_SECTOR_SIZE;
        long i;
        long bytesToWrite = count * EEPROM_SECTOR_SIZE;
        for (i = 0; i < bytesToWrite; i++) {
            char value = *buffer;
            buffer++; 
            // TODO : Improve by using call to eepromWriteBlock instead of using WriteInt !
            eeprom_->eepromWriteChar(eeprom_, base_index + i, value);
        }

        return RES_OK;
    }   
    return RES_PARERR;
}

/**
 * @private
 * Miscellaneous Functions
 * @param physicalDriveNumber (IN) Physical drive number (0..)
 * @param cmd (IN) Control code
 * @param buffer (IN/OUT) Parameter and data buffer. 
 * Pointer to the parameter depends on the command code. Do not care if no parameter to be passed.
 * @return 
 * - RES_OK (0) The function succeeded.
 * - RES_ERROR An error occured.
 * - RES_PARERR The command code or parameter is invalid.
 * - RES_NOTRDY The device has not been initialized.
 */
DRESULT disk_ioctl (BYTE physicalDriveNumber, BYTE cmd, void *buffer) {
    if (physicalDriveNumber == EEPROM_DRIVE_NUMBER) {
        // Make sure that the device has finished pending write process. 
        // If the disk I/O module has a write back cache, the dirty buffers must be written back to the media immediately.
        // Nothing to do for this command if each write operation to the media is completed within the disk_write function.
        if (cmd == CTRL_SYNC) {
            // nothing to do because no memory on eeprom.
            return RES_OK;
        }
        // DOCUMENTATION : http://elm-chan.org/fsw/ff/en/dioctl.html
        // Returns number of available sectors on the drive into the DWORD variable pointed by buff.
        // This command is used by only f_mkfs and f_fdisk function to determine the volume/partition size 
        // to be created. Required at _USE_MKFS == 1 or _MULTI_PARTITION == 1.
        else if (cmd == GET_SECTOR_COUNT) {
            DWORD* realBuffer = (DWORD*) buffer;
            *realBuffer = (DWORD) EEPROM_SECTOR_COUNT;
            return RES_OK;
        }
        else if (cmd == GET_SECTOR_SIZE) {
            DWORD* realBuffer = (DWORD*)buffer;
            *realBuffer = (DWORD)EEPROM_SECTOR_SIZE;
            return RES_OK;
        }
        // DOCUMENTATION : http://elm-chan.org/fsw/ff/en/dioctl.html
        // !! Required at _USE_MKFS == 1 !!
        // Returns erase block size of the flash memory media in unit of sector into 
        // the DWORD variable pointed by buff. The allowable value is from 1 to 32768 in power of 2.
        // Return 1 if the erase block size is unknown or non flash memory media.
        // This command is used by only f_mkfs function and it attempts to align data area to the erase block boundary.
        else if (cmd == GET_BLOCK_SIZE) {
            DWORD* realBuffer = (DWORD*)buffer;
            // *realBuffer = (WORD)EEPROM_SECTOR_SIZE;
            *realBuffer = (DWORD) 1;
            return RES_OK; // BLOCK_SIZE is unknown
        }       
        // DOCUMENTATION : http://elm-chan.org/fsw/ff/en/dioctl.html
        // !! Required at _USE_TRIM == 1 !!
        // Informs the device the data on the block of sectors that specified by DWORD array 
        // {<start sector>, <end sector>} pointed by buff is no longer needed and it may be erased. 
        // This is an identical command to Trim of ATA device. When this feature is not supported or not 
        // a flash memory device, nothing to do for this command. The FatFs does not check the result code 
        // and the file function is not affected even if the sector block was not erased well. 
        // This command is called on removing a cluster chain and f_mkfs function. 
        else if (cmd == CTRL_TRIM) {
            writeError(EEPROM_FILE_ILLEGAL_CALL);
            return RES_OK;
        }
    }
    return RES_PARERR;
}

void initEepromFile(Eeprom* eepromParam) {
    eeprom_ = eepromParam;
}