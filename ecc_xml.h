/* 
 * File:   ecc_xml.h
 * Author: bruce-lin
 *
 * Created on 2013年7月9日, 上午 11:15
 */

#ifndef ECC_XML_H
#define	ECC_XML_H

#ifdef	__cplusplus
extern "C" {
#endif
 #include "ECCAPP.h"   
USHORT ECC_CheckXML(STR * File);
USHORT ECC_SetXMLTag(STR * FILE, STR * NodeName,STR *ItemName, STR * TEXT);
USHORT ECC_SetXMLTag2(STR * FILE, STR * Node1Name, STR * Node2Name,STR *ItemName, STR * TEXT);
USHORT ECC_SetXMLTag3(STR * FILE, STR * Node1Name, STR * Node2Name,STR * Node3Name,STR *ItemName, STR * TEXT);
USHORT ECC_ADDXMLNODE(ezxml_t  DestXml,BYTE * TAG,BYTE * NAME, BYTE * Data);
ezxml_t eECC_GetXMLTag(STR * FILE, STR * NodeName,STR *ItemName, STR * TEXT);
ezxml_t eECC_GetXMLTag3(STR * FILE, STR * NodeName,STR *ItemNameL1,STR * ItemNameL2,STR * ItemNameL3, STR * TEXT);
ezxml_t eECC_GetXMLTag2(STR * FILE, STR * NodeName,STR *ItemNameL1,STR * ItemNameL2, STR * TEXT);
USHORT ECC_GetXMLTag3(STR * FILE, STR * Node1Name, STR * Node2Name,STR * Node3Name,STR *ItemName, STR * TEXT);
USHORT ECC_GetXMLTag2(STR * FILE, STR * NodeName,STR *ItemNameL1,STR * ItemNameL2, STR * TEXT);
USHORT ECC_GetXMLTag(STR * FILE, STR * NodeName,STR *ItemName, STR * TEXT);
//USHORT ECC_GetXMLNODE(STR * FILE, STR * NodeName,ezxml_t *Node);
USHORT ECC_WriteXMLFILE2(STR * FileName,ezxml_t xml,STR *TagName);
USHORT ECC_WriteXMLFILE(STR * FILEName,ezxml_t xml );
//ezxml_t LoadXMLFile(STR * filename);
ezxml_t LoadXMLFile(STR * filename);
//USHORT LoadXMLFile2(ezxml_t *xml, STR * filename);
USHORT ECC_WriteXmlHeader(STR * TagName,STR * filename);
USHORT ECC_WriteXmlEND(STR * TagName,STR * filename);
USHORT ECC_RemoveXmlEND(STR * TagName,STR * filename);

#ifdef	__cplusplus
}
#endif

#endif	/* ECC_XML_H */

