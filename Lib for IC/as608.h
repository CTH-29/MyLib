/*******************************************************************************
 * @file     as608.h
 * @brief
 * @version  V1.0
 * @date     2022.2.20
 * @author   RainingCats 1466586342@qq.com
 * @code     UTF-8
*******************************************************************************/
/*******************************************************************************
TIPS:
    
EXAMPLE CODE:
    AS608_SysPara para;
    
    if( AS608_ReadSysPara(&para) == 0x00)
    {
        myprintf("\r\nOK\r\n");
        myprintf("StateReg     : %X\r\n", para.StateReg );
        myprintf("SensorType   : %d\r\n", para.SensorType );
        myprintf("DatabaseMax  : %d\r\n", para.DatabaseMax );
        myprintf("SecurityLevel: %d\r\n", para.SecurityLevel );
        myprintf("DeviceAddr   : %X\r\n", para.DeviceAddr );
        myprintf("PacketSize   : %d\r\n", para.PacketSize );
        myprintf("N_bps        : %d\r\n", para.N_bps);
        
    }
    else
    {
        myprintf("\r\nfail\r\n");
        return ;
    }
    
    HAL_Delay(1000);
    
    if( AS608_InputFingerprint(0) == 0x00 )
    {
        myprintf("\r\nInputFingerprint OK\r\n");
    }
    else
    {
        return ;
    }
    HAL_Delay(1000);
    
    if( AS608_InputFingerprint(1) == 0x00 )
    {
        myprintf("\r\nInputFingerprint OK\r\n");
    }
    else
    {
        return ;
    }
    HAL_Delay(1000);
    
    uint16_t ID;
    while( 1 )
    {
        if( AS608_CheckFingerprint( &ID ) == 0x00 )
        {
            myprintf("\r\nCheckFingerprint OK : %d\r\n", ID);
        }
        else
        {
            myprintf("\r\nCheckFingerprint fail\r\n");
        }
    }

*******************************************************************************/

#ifndef __AS608_H
#define __AS608_H

#include "stdint.h"

/***************** Basic Interface *************************/

//#define     AS608_PinState              HAL_GPIO_ReadPin (GPIOB,GPIO_PIN_10)

void        AS608_LowLevelSend          ( uint8_t * dat, uint16_t len );
uint8_t     AS608_LowLevelRecv          ( uint8_t * dat, uint16_t len, uint16_t timeout );

/***************** Parameters Definition *******************/

#define     u8_u16( u8_high , u8_low )  ( (( u8_high ) << 8 ) | ( u8_low ))
#define     u8_u32( u8_4 , u8_3 , u8_2 , u8_1 )\
                                        ( (( u8_4 ) << 24 ) | (( u8_3 ) << 16 ) | (( u8_2 ) << 8 ) | ( u8_1 ) ) 
#define     u16_u8h( u16 )              ( ( uint8_t )( ( u16 ) >> 8 ))
#define     u16_u8l( u16 )              ( ( uint8_t )  ( u16 )       )
#define     u32_u8_4( u32 )             ( ( uint8_t )( ( u32 ) >> 24 ))
#define     u32_u8_3( u32 )             ( ( uint8_t )( ( u32 ) >> 16 ))
#define     u32_u8_2( u32 )             ( ( uint8_t )( ( u32 ) >> 8  ))
#define     u32_u8_1( u32 )             ( ( uint8_t )  ( u32 )        )

#define     AS608_CHARBUFFER1   0x01
#define     AS608_CHARBUFFER2   0x02

#define     AS608_PKT_CMD       0x01
#define     AS608_PKT_DAT       0x02
#define     AS608_PKT_END       0x08
#define     AS608_PKT_RPY       0x07

static uint16_t AS608_DEDAULT_HEADER = 0xEF01;
static uint32_t AS608_DEDAULT_ADDR   = 0XFFFFFFFF;


typedef struct
{
    uint16_t header;
    uint32_t addr;
    uint8_t  index;
    uint16_t len;
    uint8_t payload[257];
    uint16_t payload_len;
    uint16_t sum;
} AS608_Packet;

typedef struct
{
    uint16_t pageID;
    uint16_t score;
} AS608_SearchResult;

typedef struct
{
    uint16_t StateReg;
    uint16_t SensorType;
    uint16_t DatabaseMax;
    uint16_t SecurityLevel;
    uint32_t DeviceAddr;
    uint16_t PacketSize;
    uint16_t N_bps;
} AS608_SysPara;


/****************** Main Functions *************************/

void        AS608_SendPacket        ( uint8_t index, uint8_t * payload, uint16_t payload_len ); 
uint8_t     AS608_RecvPacket        ( AS608_Packet * pack, uint16_t payload_len, uint16_t timeout );

uint8_t     AS608_GetImage          ( void );
uint8_t     AS608_GenChar           ( uint8_t BufferID );
uint8_t     AS608_Match             ( uint16_t * Socre );
uint8_t     AS608_Search            ( uint8_t BufferID, uint16_t StartPage, uint16_t PageNum, AS608_SearchResult * p );
uint8_t     AS608_RegModel          ( void );
uint8_t     AS608_StoreChar         ( uint8_t BufferID, uint16_t PageID );
uint8_t     AS608_DeletChar         ( uint16_t PageID, uint16_t N );
uint8_t     AS608_Empty             ( void ); 
uint8_t     AS608_WriteReg          ( uint8_t RegNum, uint8_t RegData);
uint8_t     AS608_ReadSysPara       ( AS608_SysPara * p );
uint8_t     AS608_SetChipAddr       ( uint32_t addr);
uint8_t     AS608_WriteNotepad      ( uint8_t NotePageNum,uint8_t * content );
uint8_t     AS608_ReadNotepad       ( uint8_t NotePageNum,uint8_t * note );
uint8_t     AS608_HighSpeedSearch   ( uint8_t BufferID, uint16_t StartPage, uint16_t PageNum, AS608_SearchResult * p );
uint8_t     AS608_ValidTempleteNum  ( uint16_t * ValidN );

uint8_t     AS608_ValidTempleteNum  ( uint16_t * ValidN );


uint8_t     AS608_InputFingerprint  ( uint16_t ID );
uint8_t     AS608_CheckFingerprint  ( uint16_t * ID  );

/****************** Error Code *************************/

//const static char AS608_STR0x00[] = "OK";
//const static char AS608_STR0x01[] = "????????????????????? ";
//const static char AS608_STR0x02[] = "????????????????????????";
//const static char AS608_STR0x03[] = "????????????????????????";
//const static char AS608_STR0x04[] = "?????????????????????????????????????????????";
//const static char AS608_STR0x05[] = "?????????????????????????????????????????????";
//const static char AS608_STR0x06[] = "????????????????????????????????????";
//const static char AS608_STR0x07[] = "??????????????????????????????????????????????????????????????????????????????";
//const static char AS608_STR0x08[] = "???????????????";
//const static char AS608_STR0x09[] = "??????????????????";
//const static char AS608_STR0x0A[] = "??????????????????";
//const static char AS608_STR0x0B[] = "???????????????????????????????????????????????????";
//const static char AS608_STR0x10[] = "??????????????????";
//const static char AS608_STR0x11[] = "?????????????????????";
//const static char AS608_STR0x15[] = "???????????????????????????????????????????????????";
//const static char AS608_STR0x18[] = "??????FLASH??????";
//const static char AS608_STR0x19[] = "???????????????";
//const static char AS608_STR0x1A[] = "??????????????????";
//const static char AS608_STR0x1B[] = "???????????????????????????";
//const static char AS608_STR0x1C[] = "???????????????????????????";
//const static char AS608_STR0x1F[] = "????????????";
//const static char AS608_STR0x20[] = "????????????";


#endif
