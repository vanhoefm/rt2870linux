/*
 *************************************************************************
 * Ralink Tech Inc.
 * 5F., No.36, Taiyuan St., Jhubei City,
 * Hsinchu County 302,
 * Taiwan, R.O.C.
 *
 * (c) Copyright 2002-2007, Ralink Technology, Inc.
 *
 * This program is free software; you can redistribute it and/or modify  * 
 * it under the terms of the GNU General Public License as published by  * 
 * the Free Software Foundation; either version 2 of the License, or     * 
 * (at your option) any later version.                                   * 
 *                                                                       * 
 * This program is distributed in the hope that it will be useful,       * 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        * 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         * 
 * GNU General Public License for more details.                          * 
 *                                                                       * 
 * You should have received a copy of the GNU General Public License     * 
 * along with this program; if not, write to the                         * 
 * Free Software Foundation, Inc.,                                       * 
 * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             * 
 *                                                                       * 
 *************************************************************************
*/


#ifndef __RTUSB_IO_H__
#define __RTUSB_IO_H__

#include "wpa_cmm.h"
#include "rtmp_type.h"

// New for MeetingHouse Api support
#define CMDTHREAD_VENDOR_RESET                      0x0D730101	// cmd
#define CMDTHREAD_VENDOR_UNPLUG                     0x0D730102	// cmd
#define CMDTHREAD_VENDOR_SWITCH_FUNCTION            0x0D730103	// cmd
#define CMDTHREAD_MULTI_WRITE_MAC                   0x0D730107	// cmd
#define CMDTHREAD_MULTI_READ_MAC                    0x0D730108	// cmd
#define CMDTHREAD_VENDOR_EEPROM_WRITE               0x0D73010A	// cmd
#define CMDTHREAD_VENDOR_EEPROM_READ                0x0D73010B	// cmd
#define CMDTHREAD_VENDOR_ENTER_TESTMODE             0x0D73010C	// cmd
#define CMDTHREAD_VENDOR_EXIT_TESTMODE              0x0D73010D	// cmd
#define CMDTHREAD_VENDOR_WRITE_BBP                  0x0D730119	// cmd
#define CMDTHREAD_VENDOR_READ_BBP                   0x0D730118	// cmd
#define CMDTHREAD_VENDOR_WRITE_RF                   0x0D73011A	// cmd
#define CMDTHREAD_VENDOR_FLIP_IQ                    0x0D73011D	// cmd
#define CMDTHREAD_RESET_BULK_OUT                    0x0D730210	// cmd
#define CMDTHREAD_RESET_BULK_IN                     0x0D730211	// cmd
#define CMDTHREAD_SET_PSM_BIT                  		0x0D730212	// cmd
#define CMDTHREAD_SET_RADIO                         0x0D730214	// cmd
#define CMDTHREAD_UPDATE_TX_RATE                    0x0D730216	// cmd
#define CMDTHREAD_RESET_FROM_ERROR                  0x0D73021A	// cmd
#define CMDTHREAD_LINK_DOWN                         0x0D73021B	// cmd
#define CMDTHREAD_RESET_FROM_NDIS                   0x0D73021C	// cmd
#define CMDTHREAD_CHECK_GPIO                        0x0D730215	// cmd
#define CMDTHREAD_FORCE_WAKE_UP                     0x0D730222	// cmd
#define CMDTHREAD_FORCE_SLEEP_AUTO_WAKEUP			0x0D730223	// cmd
#define CMDTHREAD_SET_BW                            0x0D730225	// cmd
#define CMDTHREAD_SET_ASIC_WCID                     0x0D730226	// cmd
#define CMDTHREAD_QKERIODIC_EXECUT                  0x0D73023D	// cmd
#define CMDTHREAD_SET_CLIENT_MAC_ENTRY              0x0D73023E	// cmd


/* Security related */
#define CMDTHREAD_SET_WCID_SEC_INFO					0x0D730260	// cmd
#define CMDTHREAD_SET_ASIC_WCID_IVEIV              	0x0D730261	// cmd
#define CMDTHREAD_SET_ASIC_WCID_ATTR              	0x0D730262	// cmd
#define CMDTHREAD_SET_ASIC_SHARED_KEY				0x0D730263	// cmd
#define CMDTHREAD_SET_ASIC_PAIRWISE_KEY				0x0D730264	// cmd 
#define CMDTHREAD_SET_PORT_SECURED					0x0D730265	// cmd 
#define CMDTHREAD_REMOVE_PAIRWISE_KEY				0x0D730266	// cmd 

#define CMDTHREAD_802_11_QUERY_HARDWARE_REGISTER    0x0D710105	// cmd
#define CMDTHREAD_802_11_SET_PHY_MODE               0x0D79010C	// cmd
#define CMDTHREAD_802_11_SET_STA_CONFIG             0x0D790111	// cmd
#define CMDTHREAD_802_11_SET_PREAMBLE               0x0D790101	// cmd
#define CMDTHREAD_802_11_COUNTER_MEASURE			0x0D790102	// cmd
// add by johnli, fix "in_interrupt" error when call "MacTableDeleteEntry" in Rx tasklet
#define CMDTHREAD_UPDATE_PROTECT					0x0D790103	// cmd

// end johnli

#ifdef LINUX
#ifdef RT_CFG80211_SUPPORT
#define CMDTHREAD_REG_HINT							0x0D79010a
#define CMDTHREAD_REG_HINT_11D						0x0D79010b
#define CMDTHREAD_SCAN_END							0x0D79010c
#endif // RT_CFG80211_SUPPORT //
#endif // LINUX //


//CMDTHREAD_MULTI_READ_MAC
//CMDTHREAD_MULTI_WRITE_MAC
//CMDTHREAD_VENDOR_EEPROM_READ
//CMDTHREAD_VENDOR_EEPROM_WRITE
typedef	struct	_CMDHandler_TLV	{
	USHORT		Offset;
	USHORT		Length;
	UCHAR		DataFirst;
}	CMDHandler_TLV, *PCMDHandler_TLV;



typedef struct   _RT_SET_ASIC_WCID {
	ULONG WCID;          // mechanism for rekeying: 0:disable, 1: time-based, 2: packet-based
	ULONG SetTid;        // time-based: seconds, packet-based: kilo-packets
	ULONG DeleteTid;        // time-based: seconds, packet-based: kilo-packets
	UCHAR Addr[MAC_ADDR_LEN];	// avoid in interrupt when write key
} RT_SET_ASIC_WCID,*PRT_SET_ASIC_WCID;

typedef struct   _RT_ASIC_WCID_SEC_INFO {
	UCHAR		BssIdx;
	UCHAR		KeyIdx;
	UCHAR		CipherAlg;
	UINT8		Wcid;
	UINT8		KeyTabFlag;
} RT_ASIC_WCID_SEC_INFO,*PRT_ASIC_WCID_SEC_INFO;

typedef struct   _RT_ASIC_WCID_IVEIV_ENTRY {
	UINT8		Wcid;
	UINT32		Iv;
	UINT32		Eiv;
} RT_ASIC_WCID_IVEIV_ENTRY,*PRT_ASIC_WCID_IVEIV_ENTRY;

typedef struct   _RT_ASIC_WCID_ATTR_ENTRY {
	UCHAR		BssIdx;
	UCHAR		KeyIdx;
	UCHAR		CipherAlg;
	UINT8		Wcid;
	UINT8		KeyTabFlag;
} RT_ASIC_WCID_ATTR_ENTRY,*PRT_ASIC_WCID_ATTR_ENTRY;

typedef struct  _RT_ASIC_PAIRWISE_KEY {
	UINT8		WCID;
	CIPHER_KEY	CipherKey;
} RT_ASIC_PAIRWISE_KEY, *PRT_ASIC_PAIRWISE_KEY;

typedef struct  _RT_ASIC_SHARED_KEY {
	UCHAR		BssIndex;
	UCHAR		KeyIdx;
	CIPHER_KEY 	CipherKey;
} RT_ASIC_SHARED_KEY, *PRT_ASIC_SHARED_KEY;

/******************************************************************************

  	USB Cmd to ASIC Related MACRO
  	
******************************************************************************/
// reset MAC of a station entry to 0xFFFFFFFFFFFF
#define RTMP_STA_ENTRY_MAC_RESET(pAd, Wcid)					\
	{	RT_SET_ASIC_WCID	SetAsicWcid;						\
		SetAsicWcid.WCID = Wcid;								\
		SetAsicWcid.SetTid = 0xffffffff;						\
		SetAsicWcid.DeleteTid = 0xffffffff;						\
		RTEnqueueInternalCmd(pAd, CMDTHREAD_SET_ASIC_WCID, 	\
				&SetAsicWcid, sizeof(RT_SET_ASIC_WCID));	}

// add by johnli, fix "in_interrupt" error when call "MacTableDeleteEntry" in Rx tasklet
// Set MAC register value according operation mode
#define RTMP_UPDATE_PROTECT(pAd)	\
 	RTEnqueueInternalCmd(pAd, CMDTHREAD_UPDATE_PROTECT, NULL, 0);
// end johnli

// Insert the BA bitmap to ASIC for the Wcid entry
#define RTMP_ADD_BA_SESSION_TO_ASIC(_pAd, _Aid, _TID)					\
		do{																\
			RT_SET_ASIC_WCID	SetAsicWcid;							\
			SetAsicWcid.WCID = (_Aid);									\
			SetAsicWcid.SetTid = (0x10000<<(_TID));						\
			SetAsicWcid.DeleteTid = 0xffffffff;							\
			RTEnqueueInternalCmd((_pAd), CMDTHREAD_SET_ASIC_WCID, &SetAsicWcid, sizeof(RT_SET_ASIC_WCID));	\
		}while(0)

// Remove the BA bitmap from ASIC for the Wcid entry
#define RTMP_DEL_BA_SESSION_FROM_ASIC(_pAd, _Wcid, _TID)				\
		do{																\
			RT_SET_ASIC_WCID	SetAsicWcid;							\
			SetAsicWcid.WCID = (_Wcid);									\
			SetAsicWcid.SetTid = (0xffffffff);							\
			SetAsicWcid.DeleteTid = (0x10000<<(_TID) );					\
			RTEnqueueInternalCmd((_pAd), CMDTHREAD_SET_ASIC_WCID, &SetAsicWcid, sizeof(RT_SET_ASIC_WCID));	\
		}while(0)


#endif // __RTUSB_IO_H__ //
