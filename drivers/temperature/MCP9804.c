// #include <p32xxxx.h>
#include <i2c.h>

#include "MCP9804.h"

#include "../../common/I2C/I2Ccommon.h"

#define CONF_REG_MCP9804        1
#define TEMP_UPPER_REG_MCP9804  2
#define TEMP_LOWER_REG_MCP9804  3
#define TEMP_CRITIC_REG_MCP9804 4
#define TEMP_AMB_REG_MCP9804    5

// Variable Capteur de temperature MCP9804
int BCD1;
int BCD10;

int Temperature;

/********************************************************
 * setRegMCP9804                                        *
 * Envoie la valeur "MSB" et "LSB" au registre "reg"       *
 * @param : reg : adresse du registre           *
 *          MSB : Poid fort transfere dans le registre  *
 *          LSB : Poid faible transfere dans le registre*
 * @return : none                     *
 ********************************************************/
void setRegMCP9804(unsigned char reg, unsigned char MSB, unsigned char LSB) {
    StartI2C();
    MasterWriteI2C(0x30);
    MasterWriteI2C(reg);
    MasterWriteI2C(MSB);
    MasterWriteI2C(LSB);
    CloseI2C();
}

void setConfRegMCP9804(unsigned char MSB, unsigned char LSB) {
    setRegMCP9804(CONF_REG_MCP9804, MSB, LSB);
}

void setTempUpperRegMCP9804(unsigned char MSB, unsigned char LSB) {
    setRegMCP9804(TEMP_UPPER_REG_MCP9804, MSB, LSB);
}

void setTempLowerRegMCP9804(unsigned char MSB, unsigned char LSB) {
    setRegMCP9804(TEMP_LOWER_REG_MCP9804, MSB, LSB);
}

void setTempCriticRegMCP9804(unsigned char MSB, unsigned char LSB) {
    setRegMCP9804(TEMP_CRITIC_REG_MCP9804, MSB, LSB);
}

void initRegMCP9804(unsigned char CONFMSB,
        unsigned char CONFLSB,
        unsigned char TUPMSB,
        unsigned char TUPLSB,
        unsigned char TLOWMSB,
        unsigned char TLOWLSB,
        unsigned char TCRITMSB,
        unsigned char TCRITLSB) {
    setConfRegMCP9804(CONFMSB, CONFLSB);
    setTempUpperRegMCP9804(TUPMSB, TUPLSB);
    setTempLowerRegMCP9804(TLOWMSB, TLOWLSB);
    setTempCriticRegMCP9804(TCRITMSB, TCRITLSB);
}

int ReadTempAmbMCP9804(void) {
    int TempAmbMSB;
    int TempAmbLSB;
    int Temperature;

    StartI2C();
    MasterWriteI2C(0x30);
    MasterWriteI2C(0x05);
    StartI2C();
    MasterWriteI2C(0x31); //AckI2C1();

    TempAmbMSB = MasterReadI2C();
    AckI2C();
    IdleI2C(); //AckI2C1();

    TempAmbLSB = MasterReadI2C();
    NotAckI2C();
    IdleI2C();

    CloseI2C();

    //Convert the temperature data
    //First Check flag bits
    if ((TempAmbMSB & 0x80) == 0x80) {
        //TA ？ TCRIT
    }
    if ((TempAmbMSB & 0x40) == 0x40) {
        //TA > TUPPER
    }
    if ((TempAmbMSB & 0x20) == 0x20) {
        //TA < TLOWER
    }
    TempAmbMSB = TempAmbMSB & 0x1F; //Clear flag bits
    if ((TempAmbMSB & 0x10) == 0x10) { //TA < 0°C
        TempAmbMSB = TempAmbMSB & 0x0F;
        //Clear SIGN
        Temperature = 256 - (TempAmbMSB * 16 + TempAmbLSB / 16);
    } else {
        //TA  ？ 0°C
        Temperature = (TempAmbMSB * 16 + TempAmbLSB / 16);
    }
    //Temperature = Ambient Temperature (°C)
    return (Temperature);
}
