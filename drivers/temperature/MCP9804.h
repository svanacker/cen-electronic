#ifndef MCP_9804_H
#define MCP_9804_H

// void setRegMCP9804 ( UINT8 reg, UINT8 MSB , UINT8 LSB );

/********************************************************
 * setConfRegMCP980                                     *
 * Envoie la valeur "MSB" et "LSB" au registre de       *
 * configuration                                        *
 * @param : MSB : Poid fort transfere dans le registre  *
 *          LSB : Poid faible transfere dans le registre*
 * @return : none                     *
 ********************************************************/
void setConfRegMCP9804 ( unsigned char MSB , unsigned char LSB );

/********************************************************
 * setTempUpperRegMCP9804                               *
 * Envoie la valeur "MSB" et "LSB" au registre de       *
 * Temperature haute                                    *
 * @param : MSB : Poid fort transfere dans le registre  *
 *          LSB : Poid faible transfere dans le registre*
 * @return : none                     *
 ********************************************************/
void setTempUpperRegMCP9804 ( unsigned char MSB , unsigned char LSB );

/********************************************************
 * setTempLowerRegMCP9804                               *
 * Envoie la valeur "MSB" et "LSB" au registre de       *
 * Temperature basse                                    *
 * @param : MSB : Poid fort transfere dans le registre  *
 *          LSB : Poid faible transfere dans le registre*
 * @return : none                     *
 ********************************************************/
void setTempLowerRegMCP9804 ( unsigned char MSB, unsigned char LSB);

/********************************************************
 * setTempCriticRegMCP9804                              *
 * Envoie la valeur "MSB" et "LSB" au registre de       *
 * Temperature critique                                 *
 * @param : MSB : Poid fort transfere dans le registre  *
 *          LSB : Poid faible transfere dans le registre*
 * @return : none                     *
 ********************************************************/
void setTempCriticRegMCP9804 ( unsigned char MSB , unsigned char LSB);

/****************************************************************
 * initRegMCP9804                                               *
 * Envoie parametre de reglage du capteur                       *
 * Temperature critique                                         *
 * @param : CONFMSB,CONFLSB : registre config                   *
 *          TUPMSB , TUPLSB : registre temperature haute        *
 *          TLOWMSB , TLOWLSB : registre temperature basse      *
 *          TCRITMSB , TCRITLSB :registre temperature critique  *
 * @return : none                                               *
 ***************************************************************/
void initRegMCP9804 ( unsigned char CONFMSB,
                      unsigned char CONFLSB,
                      unsigned char TUPMSB,
                      unsigned char TUPLSB,
                      unsigned char TLOWMSB,
                      unsigned char TLOWLSB,
                      unsigned char TCRITMSB,
                      unsigned char TCRITLSB);

/****************************************************************
 * ReadTempAmbMCP9804                                           *
 * Lit la temperature du capteur                                *
 * @param :                                                     *
 * @return : int temperature                                    *
 ***************************************************************/
int ReadTempAmbMCP9804 (void);

#endif
