#ifndef MCP9804_H
#define MCP9804_H

#define MCP9804                 0x30    //

#define CONF_REG_MCP9804        1
#define TEMP_UPPER_REG_MCP9804  2
#define TEMP_LOWER_REG_MCP9804  3
#define TEMP_CRITIC_REG_MCP9804 4
#define TEMP_AMB_REG_MCP9804    5


void setRegMCP9804 ( UINT8 reg, UINT8 MSB , UINT8 LSB );

void setConfRegMCP9804 ( UINT8 MSB , UINT8 LSB );

void setTempUpperRegMCP9804 ( UINT8 MSB , UINT8 LSB );

void setTempLowerRegMCP9804 ( UINT8 MSB , UINT8 LSB);

void setTempCriticRegMCP9804 ( UINT8 MSB , UINT8 LSB);

void initRegMCP9804 ( UINT8 CONFMSB , UINT8 CONFLSB , UINT8 TUPMSB , UINT8 TUPLSB,UINT8 TLOWMSB , UINT8 TLOWLSB,
                     UINT8 TCRITMSB , UINT8 TCRITLSB);

#endif