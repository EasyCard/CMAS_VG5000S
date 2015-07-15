/* 
 * File:   myxml.h
 * Author: T420s
 *
 * Created on 2015年3月1日, 上午 9:28
 */

#ifndef MYXML_H
#define	MYXML_H

#ifdef	__cplusplus
extern "C" {
#endif
typedef struct myxml *myxml_t;
typedef struct  {
    char *name;      // tag name
    char **attr;     // tag attributes { name, value, name, value, ... NULL }
    char *txt;       // tag character content, empty string if none
    int txt_len;
    int  off;      // tag offset from start of parent tag character content
    int len;      // tag offset from start of parent tag character content    
}myxml;
#define myxml_ERR_NOTFINDHEAD 0xff00
#define myxml_ERR_NOTFINDEND  0xff01



USHORT myxml_GetXMLTag(STR * FILE, STR * NodeName,STR *ItemName, STR * TEXT);
int myxml_GetTag(BYTE * xmlbody,BYTE * tagname,BYTE * TagData);
USHORT myxml_ADDXMLNODE(BYTE *Node,BYTE * TAG,BYTE * NAME, BYTE * Data);
USHORT myxml_ADDXMLNODE2(BYTE *Node,BYTE * TAG, BYTE * Data,BYTE* attr1Name,BYTE * attr1Text,BYTE* attr2Name,BYTE* attr2Text);
int myxml_GetFirstTag(BYTE * xmlbody,int bodylen,BYTE * tagname,BYTE * TagData);
#ifdef	__cplusplus
}
#endif

#endif	/* MYXML_H */

