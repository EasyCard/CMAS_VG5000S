
#include "ECCAPP.h"
#include "myxml.h"
#define XMLBUF_SIZE 1024
#define XML_WS   "\t\r\n "  // whitespace

USHORT myxml_ADDXMLNODE(BYTE *Node,BYTE * TAG,BYTE * NAME, BYTE * Data)
{   
    sprintf(Node,"<%s>%s</%s>",TAG,Data,TAG);
    return d_OK;
}
USHORT myxml_ADDXMLNODE2(BYTE *Node,BYTE * TAG, BYTE * Data,BYTE* attr1Name,BYTE * attr1Text,BYTE *attr2Name,BYTE *attr2Text)
{   
    BYTE attrstr1[128],attrstr2[128];
    sprintf(attrstr1," %s=\"%s\"",attr1Name,attr1Text);
    sprintf(attrstr2," %s=\"%s\"",attr2Name,attr2Text);
    sprintf(Node,"<%s%s%s>%s</%s>",TAG,attrstr1,attrstr2,Data,TAG);
    return d_OK;
}
USHORT myxml_GetXMLTag(STR * FILE, STR * NodeName,STR *ItemName, STR * TEXT)
{
     size_t  Size;
     BYTE  *bData;
     BYTE Tag[XMLBUF_SIZE];
     int TagDatalen,TagLen;
     USHORT ret=d_OK;
     ULONG filelen= File_GetLen(FILE);
     bData=malloc(filelen);
     ret=usReadFileData(FILE,&filelen,bData);
     if(ret!=d_OK) goto exit;
 
     ret= myxml_GetTag(bData,NodeName,(BYTE*)Tag);
     if(ret==0) goto exit;
     ret= myxml_GetTag(Tag,ItemName,(BYTE *)&Tag);
     if(ret==0) goto exit;
     memcpy(TEXT,Tag,TagDatalen);
     sprintf(TEXT,"%s",Tag);
exit:     
     free(bData);
     return ret; 
}

USHORT myxml_GetXMLTag2(STR * FILE, STR * NodeName , STR * TEXT)
{
     size_t  Size;
     BYTE  *bData;
     int offset=0;
     BYTE TagData[1024*30],TagData2[512],ItemName[64];
     int TagDatalen=0,TagLen,DataLen;
     USHORT ret=d_OK;
     ULONG filelen= File_GetLen(FILE);
     bData=malloc(filelen);
     ret=usReadFileData(FILE,&filelen,bData);
     if(ret!=d_OK) goto exit;
     memset(TagData,0x00,sizeof(TagData));
     TagDatalen= myxml_GetTag(bData,NodeName,TagData);
   //  if(ret!=d_OK) goto exit;
    DataLen=TagDatalen;
    offset=0;
     while(1){
        memset(TagData2,0x00,sizeof(TagData2));
        TagLen= myxml_GetFirstTag(&TagData[offset],TagDatalen,ItemName,TagData2);
        if(TagLen==0) goto exit;
        sprintf(TEXT,TagData2);
    
        DataLen-=TagLen;
        offset+=TagLen;
        
      
     }
   //  sprintf(TEXT,"%s",&xml.txt);
exit:     
     free(bData);
     return ret; 
}
int myxml_GetTag(BYTE * xmlbody,BYTE * tagname,BYTE * TagData)
{
   
    char* Tag;
    int offset=0,tagstart_offset,tagend_offset,tagTXTstart_offset,TXT_len,TagLen;
    int datalen;
    char tagheadstr[64+1],tagendstr[64+1];
    sprintf(tagheadstr,"<%s",tagname); 
    sprintf(tagendstr,"</%s>",tagname);        
    
    char * tagstart;
 
    size_t taglen=0;  offset=0;
    //xmlbody[len - 1] = '\0'; // turn end char into null terminator
    do{
       while (*xmlbody && *xmlbody != '<') xmlbody++;
       tagstart= strstr(xmlbody,tagname);
       if(tagstart==NULL){
           return 0;
       }
       xmlbody=tagstart;
       tagstart+=strlen(tagname);
       if((isspace(*tagstart))||(*tagstart=='>')) break;
    }while(1);
    tagstart_offset=(int)tagstart;
  
    while (*tagstart && *tagstart != '>') tagstart++; // find first tag
    char *Data=tagstart+1;
  
    tagTXTstart_offset=(int)tagstart;
    char *tagend;
    offset=0;
    tagend=strstr(xmlbody, tagendstr);
    if(tagend==NULL){
          return 0;
    }

    datalen=tagend-Data;  
    tagend_offset=(int)tagend;
    while (*tagend && *tagend != '>') tagend++;
  
    TagLen=tagend_offset-tagTXTstart_offset;
 
 /*    int i;  for (i=0;i< TagDatalen; i++) {
        if (isalpha(Data[i]) ) { 
           TagDatalen=i;
           break;
        }
     }*/
 //  TagDatalen=datalen;
   
    memcpy(TagData,Data,datalen);
    return datalen;
   
}


int myxml_GetFirstTag(BYTE * xmlbody,int bodylen,BYTE * tagname,BYTE * TagData)
{
   
    BYTE* Tag;
    long offset=0,tagstart_offset,tagend_offset,tagTXTstart_offset,TXT_len;
    long TagHeaderCloseOffset,TagHeaderStartOffset;
    long TagNameStrStartoffset,TagNameStrEndoffset;
    BYTE tagendstr[64+1];
   // sprintf(tagheadstr,"<%s",tagname); 
   // sprintf(tagendstr,"</%s>",tagname);        
    
    BYTE * tagstart;
 
   
    size_t taglen=0;  offset=0;
    //xmlbody[len - 1] = '\0'; // turn end char into null terminator
   
   
    while (*xmlbody && *xmlbody != '<') xmlbody++; // find first tag
    if(xmlbody>=xmlbody+bodylen){
        return 0;
    }
  
   TagHeaderStartOffset=(long)xmlbody+1;
   tagstart=(BYTE*)TagHeaderStartOffset;
    while (isspace(*tagstart)) tagstart++; // null terminate tag name
    TagNameStrStartoffset=(long)tagstart;
    while (*tagstart && *tagstart != '>'&& (!isspace(*tagstart))) tagstart++; // find first tag
    if(*tagstart == '>')             
         TagHeaderCloseOffset=(long)tagstart;
      
    TagNameStrEndoffset=(long)tagstart;
    memcpy(tagname,(char*)TagNameStrStartoffset,TagNameStrEndoffset-TagNameStrStartoffset);       
    tagname[TagNameStrEndoffset-TagNameStrStartoffset]='\0';
    
    BYTE *Data=tagstart+1;
    
    sprintf(tagendstr,"</%s>",tagname);     
    tagTXTstart_offset=(long)tagstart;
    BYTE *tagend;
    offset=0;
    tagend=strstr(xmlbody, tagendstr);
    if(tagend==NULL){
          return 0;
    }
   
   int TagDatalen=tagend-Data;
   
    tagend_offset=(long)tagend;
    while (*tagend && *tagend != '>') tagend++;
    tagend++;
    int TagLen=tagend-xmlbody;
  
    memcpy(TagData,Data,TagDatalen);
   
    return TagLen;
}